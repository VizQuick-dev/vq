CC = gcc
CFLAGS = -Wall -Wextra -fPIC -O3 -I.#-DENABLE_LOG
LDLIBS = -lz

SRC = vq.c \
      parse/argv.c \
      parse/file.c \
      parse/filetype.c \
      parse/list.c \
      lib/pbm/main.c \
      lib/pgm/main.c \
      lib/png/main.c \
      lib/ppm/main.c \

OBJ = $(SRC:%.c=build/%.o)

TARGET = libvq.so

all: $(TARGET)
	./build.sh

$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $(OBJ) $(LDLIBS)

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build libvq.so
