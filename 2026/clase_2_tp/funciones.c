#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "funciones.h"
#include "def.h"

/* Devuelve un numero aleatorio */
int inObtenerNumeroAleatorio(int desde, int hasta)
{
    int num = 0;
    num=(rand()%(hasta-desde+1))+desde;
    return num;
}

/* Devuelve un vector de numeros aleatorios no repetidos */
int* inObtenerNumerosAleatorios(int desde, int hasta, int cantidad)
{
    int numero, repetido, i;
    int generados = 0;
    int* vector;
    
    vector = malloc(sizeof(int)*cantidad);

    /* Valido el rango, por que si cantidad > (hasta - desde + 1) no puedo generar */
    if(cantidad > (hasta-desde+1))
    {
        return NULL;
    }

    while(generados < cantidad)
    {
        repetido = FALSE;
        numero = inObtenerNumeroAleatorio(desde, hasta);
        for(i=0; i<generados; i++)
        {
            if(vector[i] == numero)
            {
                repetido=TRUE;
                break;
            }
        }

        if(!repetido)
        {
            vector[generados] = numero;
            generados++;
        }
    }
    return vector;
}
