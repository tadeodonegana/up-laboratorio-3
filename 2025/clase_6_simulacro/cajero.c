#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "definiciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "funciones.h"
#include <time.h>
#include <unistd.h>
#include "global.h"
#include "string.h"

int main(int argc, char *argv[]){
    /* Se define el numero de cajero, por defecto es 1 */
    int numeroCajero = 1;

    if (argc == 2){
        numeroCajero = atoi(argv[1]);
    }

    if (numeroCajero < 1 || numeroCajero > 3){
        printf("El número de cajero debe ser entre 1 y 3\n");
        return 1;
    }
    
    printf("Cajero %d iniciado\n", numeroCajero);

    id_semaforo = creo_semaforo();

    while(1){
        espera_semaforo(id_semaforo);
        consumirProductosCajero(numeroCajero);
        levanta_semaforo(id_semaforo);
        usleep(ESPERA_CAJA*1000);
    }
    return 0;
}
