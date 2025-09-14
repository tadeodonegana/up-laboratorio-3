CC=gcc
FLAGS = -std=c89 -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean cajero menu

cajero: cajero.c archivos.h definiciones.h funciones.h global.h semaforo.h clave.h
	$(CC) $(FLAGS) -o cajero cajero.c archivos.c funciones.c global.c semaforo.c clave.c

menu: menu.c archivos.h definiciones.h funciones.h global.h semaforo.h clave.h
	$(CC) $(FLAGS) -o menu menu.c archivos.c funciones.c global.c semaforo.c clave.c

clean:
	rm -f cajero menu *.dat
