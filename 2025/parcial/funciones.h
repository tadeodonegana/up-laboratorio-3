#ifndef _FUNCIONES_H
#define _FUNCIONES_H

void producirLote(void);
void consumirProductos(int cantidadProductos);
int inDevolverNumeroAleatorio(int desde, int hasta);
int estaRepetido(int numero, int* array, int longitud);
int* generarNumerosUnicos(int desde, int hasta, int* cantidad);
int obtenerUltimoScore(int* s1, int* s2);
int escribirScore(int s1, int s2);
int appendLogEquipo(int equipo, char* linea);
void inicializarArchivosPartido(void);
int procesoEquipo(int numeroEquipo, int maxGoles);
int procesoPanel(int maxGoles);
#endif
