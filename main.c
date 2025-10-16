#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "img2txt.h"
#include <getopt.h>
#include <unistd.h>

void print_usage(const char *prog_name) {
  fprintf(stderr, "Usage: %s [-s <size>] [-c <8|256>] <image>\n", prog_name);
}

int main(int ac, char **av) {
  int color_mode = 256; // Default to 256 colors
  int new_width = 0;
  int opt;

  while ((opt = getopt(ac, av, "s:c:")) != -1) {
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

    default:
      print_usage(av[0]);
      exit(1);
    }
  }

  if (optind >= ac) {
    fprintf(stderr, "Error: Missing image file\n");
    print_usage(av[0]);
    exit(1);
  }

  if (new_width == 0) {
    if (isatty(STDOUT_FILENO)) {
      new_width = get_terminal_width();
    } else {
      new_width = 80; // Default width if not a tty
    }
  }

  if (new_width <= 0 || new_width >= 1500) {
    printf("Size must be between 1 and 1500\n");
    exit(1);
  }

  int width, height, channels;
  unsigned char *img = stbi_load(av[optind], &width, &height, &channels, 0);

  if (img == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }
  if (channels < 3) {
    printf("Image must be RGB or RGBA.\n");
    stbi_image_free(img);
    exit(1);
  }

  // Preserve aspect ratio, characters are roughly 2x taller than wide
  int new_height =
      (int)((float)new_width * ((float)height / (float)width) / 2.0f);

  unsigned char *new_img = malloc(new_width * new_height * channels);
  if (new_img == NULL) {
    printf("Error in allocating memory for the new image\n");
    stbi_image_free(img);
    exit(1);
  }

  if (stbir_resize_uint8_linear(img, width, height, 0, new_img, new_width,
                                new_height, 0,
                                (stbir_pixel_layout)channels) == 0) {
    printf("Error resizing image\n");
    stbi_image_free(img);
    free(new_img);
    exit(1);
  }

  // Allocate buffer for the whole output
  size_t buffer_size =
      (size_t)new_height * (new_width * 13 + 1) + strlen(RESET_COLOR) + 1;
  char *output_buffer = malloc(buffer_size);
  if (output_buffer == NULL) {
    printf("Error allocating output buffer\n");
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

  write(1, CLS, 4); // clear screen
  write(1, output_buffer, strlen(output_buffer));

  stbi_image_free(img);
  free(new_img);
  free(output_buffer);
  return 0;
}
