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
#include <time.h>

int main(int argc, char *argv[]){

    int i, cantidad, numero_pensado, alguien_acerto;
    parametros_jugador* params;
    pthread_attr_t atributos;
    pthread_t* idHilo;
    int* intentos;
    void* resultado;
    i = 0, cantidad = 0, alguien_acerto = 0;

    srand(time(NULL));

    if (argc < 2) {
        printf("Uso: %s <numero_de_jugadores>\n", argv[0]);
        return 1;
    }

    numero_pensado = inDevolverNumeroAleatorio(DESDE, HASTA);
    printf("El número pensado es: %d\n", numero_pensado);

    cantidad = atoi(argv[1]);
    params = (parametros_jugador*)malloc(sizeof(parametros_jugador) * cantidad);
    idHilo = (pthread_t*)malloc(sizeof(pthread_t) * cantidad);
    intentos = (int*)malloc(sizeof(int) * cantidad);

    /* Inicializo el mutex */
    pthread_mutex_init(&mutex, NULL);

    /* Inicializo los atributos */
    pthread_attr_init(&atributos);

    /* Seteo el estado inicial del hilo */
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    printf("Creando %d hilos\n", cantidad);

    for (i = 0; i < cantidad; i++) {
        params[i].numero_pensado = numero_pensado;
        params[i].id_jugador = i + 1;
        params[i].alguien_acerto = &alguien_acerto;
        pthread_create(&idHilo[i], &atributos, threadJugador, &params[i]);
    }

    for (i = 0; i < cantidad; i++) {
        printf("Voy a esperar al thread %d\n", i);
        // resultado no debe obtenerse del join, debe obtenerse de otro lado, como por ejemplo una variable global
        pthread_join(idHilo[i], &resultado);
        intentos[i] = (long)resultado;
    }

    /* Mostrar resumen */
    printf("\n=== RESUMEN FINAL ===\n");
    printf("El jugador %d ha acertado\n", alguien_acerto);
    for (i = 0; i < cantidad; i++) {
        printf("Jugador %d: %d intentos\n", i+1, intentos[i]);
    }

    free(intentos);
    free(idHilo);
    free(params);
    return 0;
}
