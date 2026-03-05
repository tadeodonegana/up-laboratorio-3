#include "stdio.h"
#include "stdlib.h"
#include "funciones.h"
#include <time.h>
#include "definiciones.h"

int main(int argc, char* argv[]) {
    
    /* Devuelve numeros aleatorios sin repetirlos, DESDE - HASTA */

    int cantidad = 0, desde = DESDE, hasta = HASTA, *numerosGenerados = NULL, i = 0;

    if (argc == 3) {
        /* En vez de leer desde definiciones leo desde los parametros del programa */
        desde = atoi(argv[1]);
        hasta = atoi(argv[2]);
    }

    srand(time(NULL));

    /* CÓDIGO ANTERIOR (COMENTADO) - Ya no se usa:
    cantidad = hasta - desde + 1;
    printf("\nCantidad: %d\n", cantidad);
    if (cantidad <= 0) {
        printf("El rango no es válido\n");
        return 1;
    }

    numerosGenerados = malloc(cantidad * sizeof(int));
    if (numerosGenerados == NULL) {
        printf("Error de asignación de memoria\n");
        return 1;
    }

    while (numerosUnicos < cantidad) {
        numeroAleatorio = inDevolverNumeroAleatorio(desde, hasta);
        if (estaRepetido(numeroAleatorio, numerosGenerados, numerosUnicos) == FALSE) {
            numerosGenerados[numerosUnicos] = numeroAleatorio;
            printf("%d\n", numeroAleatorio);
            numerosUnicos++;    
        }
    }
    */

    /* NUEVO CÓDIGO: Usar la función genérica */
    numerosGenerados = generarNumerosUnicos(desde, hasta, &cantidad);
    
    if (numerosGenerados == NULL) {
        printf("Error: No se pudieron generar números únicos\n");
        return 1;
    }

    printf("\nCantidad: %d\n", cantidad);
    printf("Números únicos generados:\n");
    
    /* Mostrar los números generados */
    for (i = 0; i < cantidad; i++) {
        printf("%d\n", numerosGenerados[i]);
    }

    /* Liberar memoria */
    free(numerosGenerados);

    /*
    Devuelve un numero aleatorio entre 0 y 10
    numero = inDevolverNumeroAleatorio(DESDE, HASTA);
    printf("Numero: %d\n", numero);
    */

    return 0;
}
