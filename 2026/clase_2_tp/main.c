#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "funciones.h"
#include "global.h"
#include "def.h"
#include "time.h"

int main(int argc, char *argv[]) {
    int cantidad = 5;
    int inNumeroAleatorio=0;
    int i;
    int* numeros;
    
    srand (time(NULL));
    
    /* Numeros aleatorios */
    inNumeroAleatorio=inObtenerNumeroAleatorio(DESDE,HASTA);
    inNumAl=inObtenerNumeroAleatorio(DESDE,HASTA);

    printf("Primer numero %d \n", inNumeroAleatorio);
    printf("Segundo numero %d \n", inNumAl);

    /* Vector de numeros aleatorios no repetidos */
    numeros = inObtenerNumerosAleatorios(DESDE, HASTA, cantidad);

    printf("Vector de numeros aleatorios de longitud %d \n", cantidad);

    if(numeros == NULL)
    {
        printf("Error al generar numeros aleatorios \n");
        return 1;
    }

    for(i=0; i<cantidad; i++)
    {
        printf("%d \n", numeros[i]);
    }

    free(numeros);

    return 0;
}
