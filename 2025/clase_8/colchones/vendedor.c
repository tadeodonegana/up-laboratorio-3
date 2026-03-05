#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <time.h>
#include <string.h>
#include "memoria.h"
#include "definiciones.h"
#include "clave.h"
#include "funciones.h"
#include "semaforo.h"
#include "global.h"


int main(int argc,char *argv[])
{
    int id_memoria, codigo, cantidad;
    colchon *memoria = NULL;
    memoria = (colchon*)creoMemoria(sizeof(colchon)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    id_semaforo = creoSemaforo(CLAVE_BASE);

    while(1)
    {
        esperaSemaforo(id_semaforo);
        printf("Ingrese el codigo del colchon (1-5): ");
        scanf("%d", &codigo);
        printf("Ingrese la cantidad de colchones a vender (1-5): ");
        scanf("%d", &cantidad);
        /* Actualizar stock */
        if (memoria[codigo-1].cantidad >= cantidad) {
            memoria[codigo-1].cantidad -= cantidad;
            printf("Venta realizada: %d unidades de %s\n", cantidad, memoria[codigo-1].nombre);
        } else {
            printf("Stock insuficiente. Venta no realizada.\n");
        }
        levantaSemaforo(id_semaforo);
        usleep(500*1000);
    }

    return 0;
}
