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
