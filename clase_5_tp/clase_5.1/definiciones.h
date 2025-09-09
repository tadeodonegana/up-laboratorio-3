#ifndef _DEF_
#define _DEF_

#define ROJO  			0
#define VERDE 			1
#define LARGO 			100
#define CLAVE_BASE 33

#define TRUE 1
#define FALSE 0

#define ARCHIVO "lote.dat"

#define MAX_DESTINO 50
#define MAX_VUELOS 100
#define MAX_PASAJERO 100

typedef struct {
    int numero;
    char destino[MAX_DESTINO];
    int pasajeros;
} Resumen;

#endif
