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
    peaje *memoria = NULL;
    int id_memoria, num_vias, i, via_seleccionada, min_autos, tiempo_espera;
    id_semaforo = creoSemaforo(CLAVE_BASE);
    memoria = (peaje*)creoMemoria(sizeof(peaje)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));

    if(argc != 2){
        printf("Uso: %s <numero de vias>\n", argv[0]);
        exit(1);
    }
    num_vias = atoi(argv[1]);

    while(1)
    {
        esperaSemaforo(id_semaforo);
        /* Encontrar la via con menor cantidad de autos */
        via_seleccionada = 0;
        min_autos = memoria->vehiculos_en_cola[0];
        for(i = 1; i < num_vias; i++){
            if(memoria->vehiculos_en_cola[i] < min_autos){
                min_autos = memoria->vehiculos_en_cola[i];
                via_seleccionada = i;
            }
        }

        /* Agrego un auto a la via seleccionada */
        memoria->vehiculos_en_cola[via_seleccionada]++;
        printf("Auto agregado a la via %d\n", via_seleccionada);
        levantaSemaforo(id_semaforo);

        tiempo_espera = inDevolverNumeroAleatorio(400, 600);
        usleep(tiempo_espera*1000);
    }

    return 0;
}
