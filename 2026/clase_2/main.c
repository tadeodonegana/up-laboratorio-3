#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "funciones.h"
#include "global.h"
#include "def.h"
#include "time.h"

int main(int argc, char *argv[]) {
    int inNumeroAleatorio=0;
    
    srand (time(NULL));
    
    inNumeroAleatorio=inObtenerNumeroAleatorio(DESDE,HASTA);
    inNumAl=inObtenerNumeroAleatorio(DESDE,HASTA);

    printf("Primer numero %d \n", inNumeroAleatorio);
    printf("Segundo numero %d \n", inNumAl);

    return 0;
}
