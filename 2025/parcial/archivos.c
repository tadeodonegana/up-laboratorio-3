#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"

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

int renombrarArchivo(const char* nombreOriginal, int secuencia) {
    char nuevoNombre[256];
    memset(nuevoNombre, 0x00, sizeof(nuevoNombre));
    snprintf(nuevoNombre, sizeof(nuevoNombre), "lote.%03d.dat", secuencia);
    
    if (rename(nombreOriginal, nuevoNombre) == 0) {
        printf("Archivo renombrado con éxito: %s\n", nuevoNombre);
        return 1;
    } else {
        perror("Error al renombrar el archivo");
        return 0;
    }
}

int borrarArchivo(const char* nombreArchivo) {
    if (remove(nombreArchivo) == 0) {
        printf("Archivo %s borrado con éxito.\n", nombreArchivo);
        return 1;
    } else {
        perror("Error al borrar el archivo");
        return 0;
    }
}

int contarLineas(const char *archivo) {
    int count;
    char linea[100];

    count = 0;
    memset(linea, 0x00, sizeof(linea));
    if (abrirArchivo(&fpRead, archivo, "r")) {
        while (leerArchivo(linea, 100)) {
            count++;
            memset(linea, 0x00, 100);
        }
        cerrarArchivo(&fpRead);
    }
    return count;
}

int leerLineaN(const char *archivo, int n, char *out, int outLen) {
    int i;
    char linea[100];

    i = 0;
    memset(linea, 0x00, sizeof(linea));
    if (abrirArchivo(&fpRead, archivo, "r")) {
        while (leerArchivo(linea, 100)) {
            i++;
            if (i == n) {
                strncpy(out, linea, outLen - 1);
                return 1;
            }
            memset(linea, 0x00, 100);
        }
        cerrarArchivo(&fpRead);
    }
    return 0;
}
