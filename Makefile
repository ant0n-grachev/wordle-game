CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: wordle_game

wordle_game: wordle_game.o wordle_lib.o
	$(CC) wordle_game.o wordle_lib.o -o wordle_game

wordle_game.o: wordle_game.c wordle_lib.h
	$(CC) $(CFLAGS) -c wordle_game.c 

wordle_lib.o: wordle_lib.c wordle_lib.h
	$(CC) $(CFLAGS) -c wordle_lib.c

clean:
	rm -f wordle_game
	rm -f wordle_game.o wordle_lib.o

format:
	clang-format -i -style=file *.[ch]
