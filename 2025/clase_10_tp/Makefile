CC=gcc
FLAGS = -pthread -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean programa

programa: main.c archivos.h definiciones.h funciones.h global.h thread.h
	$(CC) $(FLAGS) -o programa main.c archivos.c funciones.c global.c thread.c


clean:
	rm -f programa
