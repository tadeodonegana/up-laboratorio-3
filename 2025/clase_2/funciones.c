#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "definiciones.h"


int inDevolverNumeroAleatorio(int desde, int hasta)
{ 
    return rand() % (hasta - desde + 1) + desde;
}

int estaRepetido(int numero, int* array, int longitud) {
    int i = 0;
    for (i = 0; i < longitud; i++) {
        if (array[i] == numero) {
            return TRUE;
        }
    }
    return FALSE;
}

/* Función genérica para generar números únicos no repetitivos */
int* generarNumerosUnicos(int desde, int hasta, int* cantidad) {
    int numerosUnicos = 0, numeroAleatorio = 0, *numerosGenerados = NULL;
    
    /* Calcular cantidad de números en el rango */
    *cantidad = hasta - desde + 1;
    
    /* Validar rango */
    if (*cantidad <= 0) {
        *cantidad = 0;
        return NULL;
    }
    
    /* Asignar memoria para el array de números */
    numerosGenerados = malloc(*cantidad * sizeof(int));
    if (numerosGenerados == NULL) {
        *cantidad = 0;
        return NULL;
    }
    
    /* Generar números únicos usando el algoritmo existente */
    while (numerosUnicos < *cantidad) {
        numeroAleatorio = inDevolverNumeroAleatorio(desde, hasta);
        if (estaRepetido(numeroAleatorio, numerosGenerados, numerosUnicos) == FALSE) {
            numerosGenerados[numerosUnicos] = numeroAleatorio;
            numerosUnicos++;    
        }
    }
    
    return numerosGenerados;
}
