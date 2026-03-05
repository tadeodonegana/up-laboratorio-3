#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "definiciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "time.h"
#include "unistd.h"
#include "global.h"
#include "string.h"
#include "funciones.h"

int main(int argc, char *argv[]){
    int cajero_id = 1;
    int i = 0;
    int tiempo_espera = 0;
    char cadena[LARGO];
    Deposito deposito;
    
    srand(time(NULL));
    
    /* Determinar ID del cajero desde argumentos o usar 1 por defecto */
    if (argc > 1) {
        cajero_id = atoi(argv[1]);
        if (cajero_id < 1 || cajero_id > MAX_CAJEROS) {
            cajero_id = 1;
        }
    }
    
    id_semaforo = creo_semaforo();
    
    /* Solo el cajero 1 inicializa el semáforo */
    if (cajero_id == 1) {
        inicia_semaforo(id_semaforo, VERDE);
        printf("Cajero %d iniciado y semáforo inicializado (Semáforo ID: %d)\n", cajero_id, id_semaforo);
    } else {
        printf("Cajero %d iniciado (Semáforo ID: %d)\n", cajero_id, id_semaforo);
    }

    while(1)
    {
        espera_semaforo(id_semaforo);
        printf("\nCAJERO %d - GENERANDO LOTE DE DEPÓSITOS\n", cajero_id);

        if (!abrirArchivo(&fpWrite, ARCHIVO, "a")) {
            printf("Error al abrir el archivo %s\n", ARCHIVO);
        } else {
            /* Generar lote de depósitos */
            for (i = 0; i < LOTE_SIZE; i++)
            {
                memset(cadena, 0x00, LARGO);
                
                /* Generar depósito aleatorio */
                deposito.cajero = cajero_id;
                deposito.importe = inDevolverNumeroAleatorio(IMPORTE_MIN, IMPORTE_MAX);
                deposito.tipo = inDevolverNumeroAleatorio(0, 1); /* 0=cheque, 1=efectivo */
                
                /* Armar cadena: cajero,importe,tipo */
                sprintf(cadena, "%d,%d,%d", 
                    deposito.cajero,
                    deposito.importe,
                    deposito.tipo
                );

                escribirArchivo(cadena);
                printf("Depósito generado: Cajero %d, $%d, %d\n", 
                    deposito.cajero, 
                    deposito.importe, 
                    deposito.tipo);
                usleep(100*1000);
            }
            cerrarArchivo(&fpWrite);
            printf("Lote de %d depósitos generado por Cajero %d\n", LOTE_SIZE, cajero_id);
        }
        levanta_semaforo(id_semaforo);
        
        /* Espera aleatoria entre 1000ms y 2500ms */
        tiempo_espera = inDevolverNumeroAleatorio(1000, 2500);
        printf("Cajero %d esperando %dms antes del próximo lote...\n", cajero_id, tiempo_espera);
        usleep(tiempo_espera * 1000);
    }
    return 0;
}
