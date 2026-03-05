CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean cajero tesorero

cajero: cajero.c archivos.h definiciones.h funciones.h global.h clave.h semaforo.h
	$(CC) $(FLAGS) -o cajero cajero.c archivos.c funciones.c global.c clave.c semaforo.c

tesorero: tesorero.c archivos.h definiciones.h funciones.h global.h clave.h semaforo.h
	$(CC) $(FLAGS) -o tesorero tesorero.c archivos.c funciones.c global.c clave.c semaforo.c

clean:
	rm -f cajero tesorero *.dat
