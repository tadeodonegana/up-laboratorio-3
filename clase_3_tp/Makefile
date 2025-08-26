CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean principal

principal: main.c archivos.h definiciones.h funciones.h
	$(CC) $(FLAGS) -o programa main.c archivos.c funciones.c

clean:
	rm -f programa