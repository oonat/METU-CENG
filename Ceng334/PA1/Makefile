CC=gcc

CFLAGS=-c -Wall -g

all: world monster

world: game_world.o logging.o
	$(CC) game_world.o logging.o -o world

game_world.o: game_world.c
	$(CC) $(CFLAGS) game_world.c

logging.o: logging.c
	$(CC) $(CFLAGS) logging.c

monster: monster.o
	$(CC) monster.o -o monster

monster.o: monster.c
	$(CC) $(CFLAGS) monster.c

clean:
	rm -rf *o world
	rm -rf *o monster