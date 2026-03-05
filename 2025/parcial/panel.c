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
    int maxGoles, estaTerminado;

    idSemaforo = creoSemaforo();
    srand(time(NULL));

    if (argc != 2) {
        printf("Uso: %s <max_goles>\n", argv[0]);
        return 1;
    }
    maxGoles = atoi(argv[1]);
    if (maxGoles < 1) {
        printf("La meta de goles debe ser mayor a 0\n");
        return 1;
    }

    iniciaSemaforo(idSemaforo, VERDE);

    while (1){
        esperaSemaforo(idSemaforo);
        estaTerminado = procesoPanel(maxGoles);
        if (estaTerminado) {
            levantaSemaforo(idSemaforo);
            break;
        }
        levantaSemaforo(idSemaforo);
        usleep(ESPERA_TURNO*1000);
    }

    return 0;
}


