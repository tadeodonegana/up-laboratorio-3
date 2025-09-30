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
    colchon *memoria = NULL;
    int id_memoria, i;
    id_semaforo = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id_semaforo, VERDE);
    memoria = (colchon*)creoMemoria(sizeof(colchon)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));

    /* Carga inicial de colchones */
    for(i=0; i<NUM_COLCHONES; i++){
        memoria[i].codigo = i+1;
        memoria[i].cantidad = STOCK_INICIAL;
        memset(memoria[i].nombre, 0x00, LARGO_NOMBRE);
    }

    strcpy(memoria[0].nombre, "PIERO");
    strcpy(memoria[1].nombre, "SUAVESTAR");
    strcpy(memoria[2].nombre, "CANNON");
    strcpy(memoria[3].nombre, "SIMMONS");
    strcpy(memoria[4].nombre, "BELMO");

    while(1)
    {
        esperaSemaforo(id_semaforo);
        /* Reviso y actualizo el stock*/
        for(i=0; i<NUM_COLCHONES; i++){
            printf("Verificando cantidad de colchones %s: %d\n", memoria[i].nombre, memoria[i].cantidad);
            if(memoria[i].cantidad < STOCK_MAXIMO){
                memoria[i].cantidad++;
                printf("Stock de colchones %s incrementado a %d\n", memoria[i].nombre, memoria[i].cantidad);
            }
        }
        levantaSemaforo(id_semaforo);
        usleep(500*1000);
    }
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
