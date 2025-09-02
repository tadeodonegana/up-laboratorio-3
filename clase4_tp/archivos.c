#include "stdio.h"
#include "stdlib.h"
#include "string.h"

FILE *fpRead = NULL;
FILE *fpWrite = NULL;

int abrirArchivo(FILE **fp, const char* nombreArchivo, const char* modo) {
    *fp = fopen(nombreArchivo, modo);
    if (*fp == NULL) {
        return 0;  
    }
    return 1;  
}

int cerrarArchivo(FILE **fp) {
    if (*fp != NULL) {
        fclose(*fp);
        *fp = NULL;
        return 1;  
    }
    return 0;  
}

int leerArchivo(char* buffer, int maxLen) {
    if (fpRead == NULL) {
        return 0;  
    }
    
    if (fgets(buffer, maxLen, fpRead) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        return 1;  
    }
    return 0;  
}

int escribirArchivo(char* texto) {
    if (fpWrite == NULL) {
        return 0;
    }
    fprintf(fpWrite, "%s\n", texto);
    return 1;
}
