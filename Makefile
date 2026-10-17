CC = gcc
CFLAGS = -Wall -Wextra

SRC = parse/argv.c \
      parse/file.c \
      parse/filetype.c \
      parse/list.c \
      lib/pbm/main.c \
      lib/pgm/main.c \
      lib/png/main.c \
      lib/ppm/main.c \

OBJ = $(SRC:%.c=build/%.o)

all: 
	make clean
	make libvq.a

libvq.a: $(OBJ)
	ar rcs $@ $(OBJ)
	./build.sh

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build libvq.a
