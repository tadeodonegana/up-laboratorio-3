CC = gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean principal

principal: main.c funciones.h definiciones.h
	$(CC) $(FLAGS) -o programa main.c funciones.c

clean:
	rm -f programa ejemplo_uso