CC = gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean principal

principal: main.c archivos.h definiciones.h
	$(CC) $(FLAGS) -o programa main.c archivos.c

clean:
	rm -f programa ejemplo_uso