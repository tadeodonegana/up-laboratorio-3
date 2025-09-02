CC = gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean principal

principal: main.c clave.h
	$(CC) $(FLAGS) -o programa main.c clave.c

clean:
	rm -f programa