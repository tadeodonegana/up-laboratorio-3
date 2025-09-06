#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "def.h"
#include "archivos.h"
#include "funciones.h"
#include "semaforo.h"
#include "time.h"
#include "global.h"
#include "unistd.h"


int main(int argc, char *argv[])
{

    id_semaforo = creo_semaforo();
    printf("ID del semáforo: %d\n", id_semaforo);

    while(1)
    {
        espera_semaforo(id_semaforo);
        printf("\nCHAU\n");
        levanta_semaforo(id_semaforo);
        usleep(1000*1000);
    }

    return 0;
}
