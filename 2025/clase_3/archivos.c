#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "archivos.h"
#include "definiciones.h"

FILE *ptrFile;

int inAbrirArchivo(char *szNombreArchivo, char *szModo)
{
    ptrFile = fopen(szNombreArchivo,szModo);
    if(ptrFile==NULL)
        return FALSE;
    return TRUE;
}

void voCerrarArchivo(void)
{
    fclose(ptrFile);
}

int inLeerArchivo(char *szBuffer)
{
    if (fgets(szBuffer, 100, ptrFile) != NULL) {
        // Remover el salto de línea
        szBuffer[strcspn(szBuffer, "\n")] = 0;
        return TRUE;
    }
    return FALSE;
}

int inEscribirArchivo(char *szDatos)
{
    int inRes = 0;
    inRes = fprintf(ptrFile,"%s",szDatos);

    if (inRes<0)
        return FALSE;
    return TRUE;
}
