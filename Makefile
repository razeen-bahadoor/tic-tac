#compiler flags

DEBUG = -ggdb
FLAVOUR = -ansi -pedantic
OPTIMIZE = -O0
WARNINGS = -Wall
CFLAGS = $(DEBUG) $(FLAVOUR) $(OPTIMIZE) $(WARNINGS)

#commands
CC = gcc
RM = rm -f
COMPILE = $(CC) $(CFLAGS)

#rules 
all: client

client: client.c game board
	$(COMPILE) -o client client.c game.o board.o
all: server
server: server.c game board
	$(COMPILE) -o server server.c game.o board.o

game: game.c game.h 
	$(COMPILE) -c game.c
board: board.c board.h
	$(COMPILE) -c board.c

clean:
	$(RM) *.o
	$(RM) server
	$(RM) client
