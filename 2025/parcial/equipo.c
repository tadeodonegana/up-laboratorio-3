#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "definiciones.h"
#include "semaforo.h"
#include "funciones.h"
#include <time.h>
#include "global.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    int numeroEquipo;
    int maxGoles;

    idSemaforo = creoSemaforo();
    srand(time(NULL));

    if (argc != 3) {
        printf("Uso: %s <equipo(1|2)> <max_goles>\n", argv[0]);
        return 1;
    }
    numeroEquipo = atoi(argv[1]);
    maxGoles = atoi(argv[2]);

    if (numeroEquipo < 1 || numeroEquipo > 2) {
        printf("El número de equipo debe ser 1 o 2\n");
        return 1;
    }
    if (maxGoles < 1) {
        printf("El objetivo de goles debe ser mayor a 0\n");
        return 1;
    }
    printf("Equipo %d iniciado. Objetivo: %d\n", numeroEquipo, maxGoles);
    procesoEquipo(numeroEquipo, maxGoles);
    return 0;
}


