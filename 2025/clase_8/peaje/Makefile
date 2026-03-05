CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean peaje autos

peaje: peaje.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o peaje peaje.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

autos: autos.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o autos autos.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

clean:
	rm -f peaje autos liberaciones.txt
