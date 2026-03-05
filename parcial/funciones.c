#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.h"
#include "definiciones.h"
#include "global.h"
#include "semaforo.h"
#include <unistd.h>

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


int obtenerUltimoScore(int *s1, int *s2) {
    char linea[LARGO];
    int a = 0;
    int b = 0;

    memset(linea, 0x00, sizeof(linea));
    if (abrirArchivo(&fpRead, SCORE_FILE, "r")) {
        if (leerArchivo(linea, LARGO)) {
            if (sscanf(linea, "%d %d", &a, &b) == 2) {
                *s1 = a;
                *s2 = b;
                cerrarArchivo(&fpRead);
                return 1;
            }
        }
        cerrarArchivo(&fpRead);
    }
    return 0;
}

int escribirScore(int s1, int s2) {
    char linea[LARGO];

    memset(linea, 0x00, sizeof(linea));
    snprintf(linea, LARGO, "%d %d", s1, s2);
    if (!abrirArchivo(&fpWrite, SCORE_FILE, "w")) {
        return 0;
    }
    escribirArchivo(linea);
    cerrarArchivo(&fpWrite);
    return 1;
}

int appendLogEquipo(int equipo, char *linea) {
    char *archivo;
    if(equipo == 1) {
        archivo = EQUIPO_1_FILE;
    } else {
        archivo = EQUIPO_2_FILE;
    }
    if (!abrirArchivo(&fpWrite, archivo, "a")) {
        return 0;
    }
    escribirArchivo(linea);
    cerrarArchivo(&fpWrite);
    return 1;
}

void inicializarArchivosPartido(void) {
    char linea[LARGO];

    borrarArchivo(EQUIPO_1_FILE);
    borrarArchivo(EQUIPO_2_FILE);
    borrarArchivo(SCORE_FILE);

    memset(linea, 0x00, sizeof(linea));
    if (abrirArchivo(&fpWrite, SCORE_FILE, "w")) {
        snprintf(linea, LARGO, "%d %d", 0, 0);
        escribirArchivo(linea);
        cerrarArchivo(&fpWrite);
    }
}

int procesoEquipo(int numeroEquipo, int maxGoles) {
    int score1;
    int score2;
    int numeroIngresado;
    int numeroAleatorio;
    int gol;
    char buffer[LARGO];
    int c1;
    int c2;
    int esMiTurno;

    memset(buffer, 0x00, sizeof(buffer));

    while (1) {
        esperaSemaforo(idSemaforo);

        if (!obtenerUltimoScore(&score1, &score2)) {
            score1 = 0;
            score2 = 0;
        }
        if (score1 >= maxGoles || score2 >= maxGoles) {
            levantaSemaforo(idSemaforo);
            return 1;
        }

        c1 = contarLineas(EQUIPO_1_FILE);
        c2 = contarLineas(EQUIPO_2_FILE);
        esMiTurno = (numeroEquipo == 1) ? (c1 == c2) : (c2 < c1);

        levantaSemaforo(idSemaforo);

        if (!esMiTurno) {
            usleep(ESPERA_TURNO*1000);
            continue;
        }

        printf("Equipo %d - Remate: ingrese un número (1-3): ", numeroEquipo);
        scanf("%d", &numeroIngresado);
        if (numeroIngresado < 1 || numeroIngresado > 3) {
            printf("Entrada inválida. Debe ser 1, 2 o 3.\n");
            usleep(ESPERA_TURNO*1000);
            continue;
        }

        numeroAleatorio = inDevolverNumeroAleatorio(1, 3);
        gol = (numeroIngresado == numeroAleatorio) ? 1 : 0;
        printf("Equipo %d -> Remate: %d vs %d => %s\n", numeroEquipo, numeroIngresado, numeroAleatorio, (gol ? "GOL" : "FUERA"));

        esperaSemaforo(idSemaforo);

        if (!obtenerUltimoScore(&score1, &score2)) {
            score1 = 0;
            score2 = 0;
        }

        snprintf(buffer, LARGO, "Remate: %d vs %d => %s", numeroIngresado, numeroAleatorio, (gol ? "GOL" : "FUERA"));
        appendLogEquipo(numeroEquipo, buffer);

        if (gol) {
            if (numeroEquipo == 1) {
                score1++;
            } else {
                score2++;
            }
        }
        escribirScore(score1, score2);

        levantaSemaforo(idSemaforo);
        usleep(ESPERA_TURNO*1000);
    }
}

int procesoPanel(int maxGoles) {
    int c1;
    int c2;
    int s1;
    int s2;
    char linea[LARGO];
    int hayEvento;

    if (!inicializado) {
        memset(linea, 0x00, sizeof(linea));
        inicializarArchivosPartido();
        printf("Panel iniciado. Meta: %d\n", maxGoles);
        inicializado = 1;
    }

    c1 = contarLineas(EQUIPO_1_FILE);
    c2 = contarLineas(EQUIPO_2_FILE);
    hayEvento = 0;

    if (c1 > lastC1) {
        memset(linea, 0x00, sizeof(linea));
        if (leerLineaN(EQUIPO_1_FILE, c1, linea, LARGO)) {
            printf("Equipo 1 -> %s\n", linea);
        }
        lastC1 = c1;
        hayEvento = 1;
    }
    if (c2 > lastC2) {
        memset(linea, 0x00, sizeof(linea));
        if (leerLineaN(EQUIPO_2_FILE, c2, linea, LARGO)) {
            printf("Equipo 2 -> %s\n", linea);
        }
        lastC2 = c2;
        hayEvento = 1;
    }

    if (obtenerUltimoScore(&s1, &s2)) {
        if (hayEvento) {
            printf("Marcador: %d - %d\n", s1, s2);
        }
        if (s1 >= maxGoles || s2 >= maxGoles) {
            printf("Partido terminado. Ganador: Equipo %d. Resultado final %d-%d\n", (s1 > s2) ? 1 : 2, s1, s2);
            return 1;
        }
    }

    return 0;
}
