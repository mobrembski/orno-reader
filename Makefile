CC = gcc
CFLAGS = -g -std=c99 -ansi -D_BSD_SOURCE -Wall
LIBS =
OBJS = src/main.c \
	src/rs232.c \
	src/crc.c \
	src/ansparser.c

all:	orno-reader

orno-reader: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test:	ornoc
	valgrind --leak-check=full --show-leak-kinds=all ./orno-reader

clean:
	rm orno-reader

.PHONY: all
