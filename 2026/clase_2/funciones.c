#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "funciones.h"

int inObtenerNumeroAleatorio(int desde, int hasta)
{
    int num = 0;
    num=(rand()%(hasta-desde+1))+desde;
    return num;
}
