#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "funciones.h"
#include "archivos.h"

int main(int argc, char *argv[]){

    /*Asigno un valor por defecto de 5 en caso de que no se pase un arg de programa*/
    int cantProductos = 5;

    if (argc == 2) {
        cantProductos = atoi(argv[1]);
    }

    producirLote();
    consumirProductos(cantProductos);
    return 0;
}
