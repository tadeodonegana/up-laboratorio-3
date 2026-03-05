CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean cajero banco

cajero: cajero.c archivos.h definiciones.h funciones.h global.h cola.h clave.h memoria.h semaforo.h espera.h
	$(CC) $(FLAGS) -I../clase_9 -o cajero cajero.c archivos.c funciones.c global.c cola.c clave.c memoria.c semaforo.c espera.c

banco: banco.c archivos.h definiciones.h funciones.h global.h cola.h clave.h memoria.h semaforo.h espera.h
	$(CC) $(FLAGS) -I../clase_9 -o banco banco.c archivos.c funciones.c global.c cola.c clave.c memoria.c semaforo.c espera.c

clean:
	rm -f cajero banco flag.txt
