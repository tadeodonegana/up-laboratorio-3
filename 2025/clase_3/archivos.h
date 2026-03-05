#ifndef _ARCHIVOS
#define _ARCHIVOS

extern FILE *ptrFile;

int inAbrirArchivo(char *szNombreArchivo, char *szModo);
void voCerrarArchivo(void);
int inLeerArchivo(char *szBuffer);
int inEscribirArchivo(char *szDatos);

#endif
