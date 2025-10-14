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

void* threadJugador(void* arg) {
    parametros_jugador* params;
    int numero_pensado;
    int id_jugador;
    int* alguien_acerto;
    int ganador_actual;
    int intento;
    int num_intentos;

    params = (parametros_jugador*)arg;
    numero_pensado = params->numero_pensado;
    id_jugador = params->id_jugador;
    alguien_acerto = params->alguien_acerto;
    ganador_actual = 0;
    num_intentos = 0;

    /* Verificar si alguien ya gano antes de empezar */
    pthread_mutex_lock(&mutex);
    ganador_actual = *alguien_acerto;
    pthread_mutex_unlock(&mutex);
    
    while (ganador_actual == 0) {
        num_intentos++;
        intento = inDevolverNumeroAleatorio(DESDE, HASTA);
        printf("Jugador %d intenta: %d\n", id_jugador, intento);
        
        if (intento == numero_pensado) {
            pthread_mutex_lock(&mutex);
            if (*alguien_acerto == 0) {
                printf("¡Jugador %d ha acertado!\n", id_jugador);
                *alguien_acerto = id_jugador;
                ganador_actual = id_jugador;
            }
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        usleep(inDevolverNumeroAleatorio(500, 5000) * 1000);
        
        /* Verificar si alguien gano mientras esperabamos */
        pthread_mutex_lock(&mutex);
        ganador_actual = *alguien_acerto;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit((void*)(long)num_intentos);
}
