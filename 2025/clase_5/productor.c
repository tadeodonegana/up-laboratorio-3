#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "def.h"
#include "archivos.h"
#include "semaforo.h"
#include "time.h"
#include "unistd.h"
#include "global.h"
#include "string.h"
#include "funciones.h"


int main(int argc, char *argv[])
{
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
	
    while(1)
    {
        espera_semaforo(id_semaforo);           
        printf("\nHOLA\n");
        levanta_semaforo(id_semaforo);
        usleep(1000*1000);
    };
    return 0;
}
