NAME=img2txt
CC=cc
LDFLAGS= -lm 
SRC=main.c
OBJ=$(SRC:.c=.o)
INCLUDE=-I./include
CFLAGS= -O2 $(INCLUDE)

all: $(NAME)

debug: 
	$(CC) -g $(CFLAGS) $(SRC) -o $(NAME) $(LDFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	@printf "$(NAME) compiled successfully!\n"
	@printf "\nUsage:\n\timg2txt <image.[png/jpg]> [-s size] [-c 256] [-l 'AEIOUuopdv    '\n"
	@printf "example:\n./img2txt zebra.jpg -s 84\n"
	@printf "./img2txt zebra.jpg 42 -c 8 \t# 8-bit color: default its 255\n \n"

clean:
	rm -f $(OBJ) $(NAME)

re: clean all

