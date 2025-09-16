#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "definiciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "funciones.h"
#include <time.h>
#include "global.h"
#include <unistd.h>

int main(int argc, char *argv[]){
    int opcion;

    id_semaforo = creo_semaforo();
    num_productos = 0;
    
    inicia_semaforo(id_semaforo, VERDE);

    while (1){
        mostrarMenu();
        scanf("%d", &opcion);
        switch (opcion){
            case 1:
                /* Agrego un producto */
                agregarProducto();
                break;
            case 2:
                /* Finaliza una compra */
                espera_semaforo(id_semaforo);
                finalizarCompra();
                levanta_semaforo(id_semaforo);
                usleep(200*1000);
                break;
            case 3:
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opción inválida\n");
                break;
        }
    }
    return 0;
}
