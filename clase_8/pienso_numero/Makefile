CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean jugador pienso

jugador: jugador.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o jugador jugador.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

pienso: pienso.c archivos.h definiciones.h funciones.h global.h semaforo.h memoria.h clave.h
	$(CC) $(FLAGS) -o pienso pienso.c archivos.c funciones.c global.c semaforo.c memoria.c clave.c

clean:
	rm -f jugador pienso
