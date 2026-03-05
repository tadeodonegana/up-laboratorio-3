#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <memoria.h>
#include <definiciones.h>
#include <clave.h>
#include <funciones.h>
#include <time.h>
#include <semaforo.h>
#include "global.h"

int main(int argc,char *argv[])
{
    int id_memoria;
    dato *memoria = NULL;
    int i;
    memoria = (dato*)creoMemoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    id_semaforo = creoSemaforo(CLAVE_BASE);
    while(1)
    {
        printf("Leemos en la memoria\n");
        esperaSemaforo(id_semaforo);
        for (i=0; i<CANTIDAD; i++)
        {
            printf("Leido %d %c\n", memoria[i].numero, memoria[i].letra);
        }
        printf("Dejamos de leer en la memoria\n");
        levantaSemaforo(id_semaforo);
        sleep (5);
    }
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
