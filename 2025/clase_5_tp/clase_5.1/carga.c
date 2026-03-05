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

int main(int argc, char *argv[]){
    int numero_vuelo = 0;
    int vuelos_ingresados = 0;
    char cadena[LARGO];
    char destino[MAX_DESTINO];
    char nombre_pasajero[MAX_PASAJERO];
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    printf("%d\n", id_semaforo);

    while(1)
    {
        espera_semaforo(id_semaforo);
        printf("\nCARGA VUELOS\n");

        if (!abrirArchivo(&fpWrite, ARCHIVO, "a")) {
            printf("Error al abrir el archivo %s\n", ARCHIVO);
        } else {
            while (vuelos_ingresados < MAX_VUELOS)
            {
                memset(cadena, 0x00, LARGO);
                
                printf("Ingrese vuelo: ");
                scanf("%d", &numero_vuelo);
                
                if (numero_vuelo == 0) {
                    printf("Carga de vuelos finalizada.\n");
                    break;
                }

                printf("Ingrese destino: ");
                scanf("%s", destino);
                
                printf("Ingrese nombre del pasajero: ");
                scanf("%s", nombre_pasajero);
                                
                /*Armar cadena*/
                sprintf(cadena, "%d,%s,%s", 
                    numero_vuelo,
                    destino,
                    nombre_pasajero
                );

                escribirArchivo(cadena);
                printf("Vuelo ingresado: %s\n", cadena);
                vuelos_ingresados++;
                usleep(100*1000);
            }
            cerrarArchivo(&fpWrite);
        }
        levanta_semaforo(id_semaforo);
        usleep(300*1000);
    }
    return 0;
}
