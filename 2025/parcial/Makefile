CC=gcc
FLAGS = -std=c89 -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean equipo panel

equipo: equipo.c archivos.h definiciones.h funciones.h global.h semaforo.h clave.h
	$(CC) $(FLAGS) -o equipo equipo.c archivos.c funciones.c global.c semaforo.c clave.c

panel: panel.c archivos.h definiciones.h funciones.h global.h semaforo.h clave.h
	$(CC) $(FLAGS) -o panel panel.c archivos.c funciones.c global.c semaforo.c clave.c

clean:
	rm -f equipo panel *.dat
