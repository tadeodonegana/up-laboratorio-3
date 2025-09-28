CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean proceso_uno proceso_dos

proceso_uno: proceso_uno.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o proceso_uno proceso_uno.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

proceso_dos: proceso_dos.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o proceso_dos proceso_dos.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

clean:
	rm -f proceso_uno proceso_dos
