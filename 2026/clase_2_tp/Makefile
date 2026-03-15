CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -pthread -I./

all: clean programa

programa: main.c funciones.c global.c funciones.h def.h global.h 
	$(CC) $(FLAGS) -o programa main.c funciones.c global.c


clean:
	rm -rf *o programa