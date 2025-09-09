CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean carga reserva

carga: main.c archivos.h definiciones.h funciones.h global.h clave.h semaforo.h
	$(CC) $(FLAGS) -o carga carga.c archivos.c funciones.c global.c clave.c semaforo.c

reserva: main.c archivos.h definiciones.h funciones.h global.h clave.h semaforo.h
	$(CC) $(FLAGS) -o reserva reserva.c archivos.c funciones.c global.c clave.c semaforo.c

clean:
	rm -f carga reserva *.dat
