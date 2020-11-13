CC = gcc
FLAGS = -std=gnu99
DEBUG_FLAGS = -Wall -pedantic -g

SRC =	src/main.c src/main.h src/utils.c src/utils.h src/command.c \
		src/command.h

all: sfsh

sfsh: $(SRC)
	$(CC) $(SRC) $(FLAGS) -o sfsh

debug: $(SRC)
	$(CC) $(SRC) $(FLAGS) $(DEBUG_FLAGS) -o sfsh

.PHONY: clean

clean:
	rm sfsh