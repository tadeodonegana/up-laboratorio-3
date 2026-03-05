CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean repositor supermercado

repositor: repositor.c archivos.h definiciones.h funciones.h global.h cola.h clave.h
	$(CC) $(FLAGS) -o repositor repositor.c archivos.c funciones.c global.c cola.c clave.c

supermercado: supermercado.c archivos.h definiciones.h funciones.h global.h cola.h clave.h
	$(CC) $(FLAGS) -o supermercado supermercado.c archivos.c funciones.c global.c cola.c clave.c

clean:
	rm -f repositor supermercado
