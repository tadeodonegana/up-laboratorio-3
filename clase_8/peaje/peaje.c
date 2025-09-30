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
#include "archivos.h"


/* Función para escribir el número de liberaciones de autos en un archivo */
void escribirLiberaciones(int liberaciones)
{
    char buffer[50];
    sprintf(buffer, "%d", liberaciones);
        
    if (abrirArchivo(&fpWrite, "liberaciones.txt", "w")) {
        escribirArchivo(buffer);
        cerrarArchivo(&fpWrite);
    } else {
        fprintf(stderr, "Error al abrir el archivo de liberaciones de autos\n");
    }
}

int main(int argc,char *argv[])
{
    int id_memoria, num_vias = 0, i = 0, tiempo_espera = 0, liberaciones = 0, via_actual = 0;
    peaje *memoria = NULL;
    memoria = (peaje*)creoMemoria(sizeof(peaje)*CANTIDAD, &id_memoria, CLAVE_BASE);
    srand(time(NULL));
    id_semaforo = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id_semaforo, VERDE);
    
    if(argc != 2){
        printf("Uso: %s <numero de vias>\n", argv[0]);
        exit(1);
    }
    num_vias = atoi(argv[1]);
    
    /* Inicializo vias en 0 */
    for(i = 0; i < num_vias; i++){
        memoria->vehiculos_en_cola[i] = 0;
    }

    while(1)
    {
        esperaSemaforo(id_semaforo);
        /* Libero la via si tiene mas de 10 vehiculos*/
        if(memoria->vehiculos_en_cola[via_actual] > 10){
            memoria->vehiculos_en_cola[via_actual] = 0;
            liberaciones++;
            escribirLiberaciones(liberaciones);
        }else{
            /* Atender la via actual*/
            if(memoria->vehiculos_en_cola[via_actual] > 0){
                memoria->vehiculos_en_cola[via_actual]--;
            }
        }

        /* Mostrar el estado de las vías */
        printf("\033[2J\033[H");  /* Limpiar la pantalla */
        for (i = 0; i < num_vias; i++) {
            printf("VIA [%d]: %d Vehículos.\n", i + 1, memoria->vehiculos_en_cola[i]);
        }
         
        via_actual = (via_actual + 1) % num_vias;

        levantaSemaforo(id_semaforo);
        tiempo_espera = inDevolverNumeroAleatorio(100, 5000);
        usleep(tiempo_espera*1000);
    }
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);

    return 0;
}
