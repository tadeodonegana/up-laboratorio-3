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
    int id_memoria, local_pienso_numero;
    juego *memoria = NULL;
    memoria = (juego*)creoMemoria(sizeof(juego)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    id_semaforo = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id_semaforo, VERDE);
    local_pienso_numero = inDevolverNumeroAleatorio(DESDE, HASTA);
    printf("El numero pensado es: %d\n", local_pienso_numero);
    
    memoria->numero_pensado = 0;
    memoria->estado_acierto = FALSE;
    while(1)
    {
        esperaSemaforo(id_semaforo);

        if(memoria->numero_pensado != 0 && memoria->estado_acierto == FALSE){
            if(memoria->numero_pensado == local_pienso_numero){
                memoria->estado_acierto = TRUE;
                printf("Jugador %s ha adivinado el numero\n", memoria->nombre_jugador);
                levantaSemaforo(id_semaforo);
                usleep(100*1000);
                break;
            } else {
                memoria->estado_acierto = FALSE;
                printf("El numero ingresado es incorrecto\n");
                memoria->numero_pensado = 0;
            }
        }
        levantaSemaforo(id_semaforo);
        usleep(100*1000);
    }
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
