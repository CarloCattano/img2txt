#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "img2txt.h"
#include <getopt.h>
#include <unistd.h>

void print_usage(const char *prog_name) {
  fprintf(stderr, "Usage: %s [-s <size>] [-c <8|256>] <image> or pipe\n",
          prog_name);
}

unsigned char *read_from_pipe(int *width, int *height, int *channels) {

  unsigned char *img = NULL;
  size_t capacity = 1024 * 1024;
  size_t total_read = 0;

  unsigned char *buffer = malloc(capacity);
  if (!buffer) {
    perror("Failed to allocate buffer for stdin");
    exit(1);
  }

  size_t bytes_read;
  while ((bytes_read = read(STDIN_FILENO, buffer + total_read,
                            capacity - total_read)) > 0) {
    total_read += bytes_read;
    if (total_read == capacity) {
      capacity *= 2;
      unsigned char *new_buffer = realloc(buffer, capacity);
      if (!new_buffer) {
        perror("Failed to reallocate buffer for stdin");
        free(buffer);
        exit(1);
      }
      buffer = new_buffer;
    }
  }

  if (total_read == 0) {
    fprintf(stderr, "Error: No data read from stdin\n");
    free(buffer);
    exit(1);
  }

  img = stbi_load_from_memory(buffer, (int)total_read, width, height, channels,
                              0);
  free(buffer);
  return img;
}

int main(int ac, char **av) {
  int color_mode = 256; // Default to 256 colors
  int new_width = 0;
  int opt;
  int width, height, channels;
  unsigned char *img = NULL;
  int clear_screen = 1;

  while ((opt = getopt(ac, av, "s:c:C")) != -1) {
    switch (opt) {
    case 's':
      new_width = atoi(optarg);
      break;
    case 'c':
      color_mode = atoi(optarg);
      if (color_mode != 8 && color_mode != 256) {
        fprintf(stderr, "Invalid color mode. Use 8 or 256\n");
        print_usage(av[0]);
        exit(1);
      }
      break;
    case 'C':
      clear_screen = 0;
      break;
    default:
      print_usage(av[0]);
      exit(1);
    }
  }

  if (optind >= ac) {
    if (isatty(STDIN_FILENO)) {
      fprintf(stderr, "Error: Missing image file or piped data\n");
      print_usage(av[0]);
      exit(1);
    }

    img = read_from_pipe(&width, &height, &channels);

  } else {
    img = stbi_load(av[optind], &width, &height, &channels, 0);
  }

  if (img == NULL) {
    fprintf(stderr, "Error in loading the image\n");
    exit(1);
  }

  if (new_width == 0) {
    if (isatty(STDOUT_FILENO))
      new_width = get_terminal_width();

    else
      new_width = 80; // Default width if not a tty
  }

  if (new_width <= 7 || new_width >= MAX_WIDTH) {
    fprintf(stderr, "Size must be between 8 and %d\n", MAX_WIDTH);
    exit(1);
  }

  if (channels < 3) {
    fprintf(stderr, "Image must be RGB or RGBA.\n");
    stbi_image_free(img);
    exit(1);
  }

  // Preserve aspect ratio, characters are roughly 2x taller than wide
  int new_height =
      (int)((float)new_width * ((float)height / (float)width) / 2.4f);

  unsigned char *new_img = malloc(new_width * new_height * channels);
  if (new_img == NULL) {
    fprintf(stderr, "Error in allocating memory for the new image\n");
    stbi_image_free(img);
    exit(1);
  }

  if (stbir_resize_uint8_linear(img, width, height, 0, new_img, new_width,
                                new_height, 0,
                                (stbir_pixel_layout)channels) == 0) {
    fprintf(stderr, "Error resizing image\n");
    stbi_image_free(img);
    free(new_img);
    exit(1);
  }

  // Allocate buffer for the whole output
  size_t buffer_size =
      (size_t)new_height * (new_width * ANSI_ESCAPE_SEQUENCE_MAX_LEN + 1) +
      strlen(RESET_COLOR) + 1;

  char *output_buffer = malloc(buffer_size);

  if (output_buffer == NULL) {
    fprintf(stderr, "Error allocating output buffer\n");
    stbi_image_free(img);
    free(new_img);
    exit(1);
  }

  char *p = output_buffer;

  const int density_len = strlen(DENSITY);

  for (int i = 0; i < new_height; i++) {
    for (int j = 0; j < new_width; j++) {
      int index = (i * new_width + j) * channels;
      unsigned char r = new_img[index];
      unsigned char g = new_img[index + 1];
      unsigned char b = new_img[index + 2];

      if (color_mode == 8) {
        int color_index = get_closest_color8(r, g, b);
        p += sprintf(p, "%s", colors8[color_index]);
      } else {
        int color_index = get_closest_xterm_color(r, g, b);
        p += sprintf(p, "\033[38;5;%dm", color_index);
      }

      float avg = (r + g + b) / 3.0;
      char c = DENSITY[(unsigned int)MAP(avg, 255, 0, 0, density_len - 1)];
      *p++ = c;
    }
    *p++ = '\n';
  }
  p += sprintf(p, "%s", RESET_COLOR);
  *p = '\0';

  if (clear_screen)
    write(1, CLS, 4); // clear screen

  write(1, output_buffer, strlen(output_buffer));

  stbi_image_free(img);
  free(new_img);
  free(output_buffer);
  return 0;
}
