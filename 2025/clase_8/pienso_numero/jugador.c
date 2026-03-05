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
    juego *memoria = NULL;
    int id_memoria, numero_pensado;
    int intentos = 0;
    id_semaforo = creoSemaforo(CLAVE_BASE);
    memoria = (juego*)creoMemoria(sizeof(juego)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));

    /* Creo nombre del jugador en memoria */
    printf("Ingrese el nombre del jugador: ");
    fgets(memoria->nombre_jugador, LARGO, stdin);
    memoria->nombre_jugador[strcspn(memoria->nombre_jugador, "\n")] = 0; /* Eliminar el salto de línea */

    printf("Bienvenido, %s! Intenta adivinar el número entre %d y %d.\n", memoria->nombre_jugador, DESDE, HASTA);

    while(1)
    {
        esperaSemaforo(id_semaforo);
        /* Verifico si el numero fue acertado */
        if(memoria->estado_acierto == TRUE)
        {
            printf("Felicitaciones, %s! Has adivinado el número en %d intentos.\n", memoria->nombre_jugador, intentos);
            break;
        }
        /* Flujo de intento */
        printf("Ingrese el numero: ");
        scanf("%d", &numero_pensado);        
        /* Caso numero_pensado = 0, genero uno aleatorio */
        if(numero_pensado == 0){
            numero_pensado = inDevolverNumeroAleatorio(DESDE, HASTA);
        }

        memoria->numero_pensado = numero_pensado;
        intentos++;
        levantaSemaforo(id_semaforo);
        usleep(100*1000);
    }

    return 0;
}
