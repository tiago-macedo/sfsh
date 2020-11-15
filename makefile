CC = gcc
GENRL_FLAGS = -std=gnu17
DEBUG_FLAGS = -D_FORTIFY_SOURCE=1 -Wall -pedantic -g
PRODU_FLAGS = -D_FORTIFY_SOURCE=2

SRC =	src/main.c src/utils.c  src/command.c

all: sfsh

sfsh: $(SRC)
	$(CC) $(SRC) $(GENRL_FLAGS) $(PRODU_FLAGS) -o sfsh

debug: $(SRC)
	$(CC) $(SRC) $(GENRL_FLAGS) $(DEBUG_FLAGS) -o sfsh

.PHONY: clean

clean:
	rm sfsh