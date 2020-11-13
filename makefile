CC = gcc
DEBUG_FLAGS = -Wall -pedantic -g

all: sfsh

sfsh: src/segfaultshell.c src/segfaultshell.h
	$(CC) src/segfaultshell.c -o sfsh

debug: src/segfaultshell.c src/segfaultshell.h
	$(CC) src/segfaultshell.c $(DEBUG_FLAGS) -o sfsh

.PHONY: clean

clean:
	rm sfsh