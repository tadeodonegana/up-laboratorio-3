#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "definiciones.h"
#include "archivos.h"
#include "funciones.h"
#include "global.h"
#include <unistd.h>
#include <pthread.h>

void *funcionThread (void *parametro)
{
    int i;
    printf ("Hijo\n");
    for(i=0; i<CANTIDAD; i++)
    {
        pthread_mutex_lock (&mutex);
        printf("Soy el hijo y tengo el mutex\n");
        usleep (1);
        pthread_mutex_unlock (&mutex);
        usleep(1);
    }
    printf("Soy el hijo y espero 10seg\n");
    usleep (10);
    printf ("Hijo : Termino\n");
    pthread_exit ((void *)"Listo");
}
