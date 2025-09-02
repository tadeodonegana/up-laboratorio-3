#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <stdio.h>

extern FILE *fpRead;
extern FILE *fpWrite;

int abrirArchivo(FILE **fp, const char* nombreArchivo, const char* modo);
int cerrarArchivo(FILE **fp);
int leerArchivo(char* buffer, int maxLen);
int escribirArchivo(char* texto);

#endif
