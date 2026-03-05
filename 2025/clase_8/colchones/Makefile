CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean vendedor colchoneria

vendedor: vendedor.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o vendedor vendedor.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

colchoneria: colchoneria.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o colchoneria colchoneria.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

clean:
	rm -f vendedor colchoneria
