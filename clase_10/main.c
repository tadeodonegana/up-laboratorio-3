#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "funciones.h"
#include "archivos.h"
#include <pthread.h>
#include "global.h"
#include "thread.h"
#include "definiciones.h"
#include <unistd.h>

int main(int argc, char *argv[]){

    pthread_t idHilo;
    pthread_attr_t atributos;
    int i;
    char* valorDevuelto = NULL;

    /* Inicializo el mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Inicializo los atributos */
    pthread_attr_init(&atributos);

    /* Seteo el estado inicial del hilo */
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    if(pthread_create(&idHilo, &atributos, funcionThread, NULL) != 0){
        printf("Error al crear el hilo\n");
        exit(-1);
    }

    /* Mientras se ejecutan los hilos continua ejecutandose el main */
    for(i=0; i<CANTIDAD; i++){
        pthread_mutex_lock(&mutex);
        printf("Soy el padre y tengo el mutex\n");
        usleep(1);
        pthread_mutex_unlock(&mutex);
        usleep(1);
    }

    printf("Soy el padre y espero el thread\n");
    pthread_join(idHilo, (void **)&valorDevuelto);
    printf("Soy el padre y ya ha terminado el thread\n");
    printf("Padre: devuelve: %s\n", valorDevuelto);
    return 0;
}
