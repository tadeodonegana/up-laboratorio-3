CC=gcc
FLAGS = -Wall -std=gnu89 -pedantic-errors -O3 -I./

all: clean producer consumer

producer: producer.c archivos.h definiciones.h funciones.h global.h
	$(CC) $(FLAGS) -o producer producer.c archivos.c funciones.c global.c

consumer: consumer.c archivos.h definiciones.h funciones.h global.h
	$(CC) $(FLAGS) -o consumer consumer.c archivos.c funciones.c global.c

clean:
	rm -f programa producer consumer producto.txt

ejecutar_ambos: clean producer consumer
	./producer
	./consumer 8