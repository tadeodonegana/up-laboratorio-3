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
#include "definiciones.h"
#include "global.h"

int main(int argc,char *argv[])
{
    int id_memoria;
    dato *memoria = NULL;
    int i, aleatorio;
    id_semaforo = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id_semaforo, VERDE);
    memoria = (dato*)creoMemoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    while(1)
    {
        printf("Escribimos en la memoria\n");
        esperaSemaforo(id_semaforo);
        for (i=0; i<CANTIDAD; i++)
        {
            aleatorio = inDevolverNumeroAleatorio(DESDE, HASTA);
            memoria[i].numero = aleatorio ;
            memoria[i].letra = 0x41 + aleatorio ;

            printf("Escrito %d %c\n", memoria[i].numero, memoria[i].letra);
            sleep (1);
        }
        printf("Dejamos de escribir en la memoria\n");
        levantaSemaforo(id_semaforo);
        sleep (10);
    }
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
