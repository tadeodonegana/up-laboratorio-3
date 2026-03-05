CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean productor consumidor

productor: productor.c archivos.h def.h funciones.h global.h semaforo.h
	$(CC) $(FLAGS) -o productor productor.c archivos.c funciones.c global.c semaforo.c clave.c

consumidor: consumidor.c archivos.h def.h funciones.h global.h semaforo.h
	$(CC) $(FLAGS) -o consumidor consumidor.c archivos.c funciones.c global.c semaforo.c clave.c


clean:
	rm -f productor consumidor producto.txt
