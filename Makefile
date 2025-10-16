NAME=img2txt
CC=cc
CFLAGS= -O2
LDFLAGS= -lm
SRC=main.c
OBJ=$(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	@printf "$(NAME) compiled successfully!\n"
	@printf "\nUsage:\n\timg2txt <image.[png/jpg]> [-s size] [-c 256]\n"
	@printf "example:\n./img2txt zebra.jpg -s 84\n"
	@printf "./img2txt zebra.jpg\tDefaults to current tty size\n"
	@printf "./img2txt zebra.jpg 42 -c 8 \t# 8-bit color: default its 255\n \n"
clean:
	rm -f $(OBJ) $(NAME)

re:
	make clean
	make all


