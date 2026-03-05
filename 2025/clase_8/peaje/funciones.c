#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.h"
#include "definiciones.h"
#include "global.h"

void producirLote(void){
    int i = 0;
   
    char producto[20];
    
    char numStr[3] = {'0', '0', '\0'};

    memset(producto, 0x00, sizeof(producto));
    memcpy(producto, "PRODUCTO-", 9);

    if (!abrirArchivo(&fpWrite, "producto.txt", "w")) {
        printf("Error al abrir el archivo para producción.\n");
        return;
    }

    for (i = 1; i <= LOTE_SIZE; i++) {
        productoActual++;
        
        numStr[1] = (productoActual % 10) + '0';
        numStr[0] = ((productoActual / 10) % 10) + '0';

        memcpy(producto + 9, numStr, 2);
        if (!escribirArchivo(producto)) {
            printf("Error al escribir en el archivo.\n");
            break;
        }
    }

    if (!cerrarArchivo(&fpWrite)) {
        printf("Error al cerrar el archivo.\n");
    } else {
        printf("Lote de %d productos producido.\n", LOTE_SIZE);
    }
}

void consumirProductos(int cantidadProductos){
    int productosConsumidos = 0;
    char linea[20];
    memset(linea, 0x00, sizeof(linea));

    if (!abrirArchivo(&fpRead, "producto.txt", "r")) {
        printf("Error al abrir el archivo para consumo.\n");
        return;
    }

    while (productosConsumidos < cantidadProductos && leerArchivo(linea, sizeof(linea))) {
        printf("Consumiendo: %s\n", linea);
        productosConsumidos++;
        memset(linea, 0x00, sizeof(linea));
    }

    if (!cerrarArchivo(&fpRead)) {
        printf("Error al cerrar el archivo.\n");
    } else {
        if (productosConsumidos == cantidadProductos) {
            printf("Se han consumido %d productos.\n", productosConsumidos);
        } else {
            printf("Se han consumido %d productos. No había suficientes productos en el archivo.\n", productosConsumidos);
        }
    }
}

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

