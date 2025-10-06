#include "espera.h"
#include "archivos.h"
#include "definiciones.h"

/* Verifica si el archivo semaforo.txt existe.*/
void esperarProcesoInit(void){
    int abierto = FALSE;

    while(!abierto){
        if(abrirArchivo(&fpRead, "flag.txt", "r")){
            abierto = TRUE;
            cerrarArchivo(&fpRead);
        }
    }
}

/* Crea el archivo flag.txt.*/
void crearFlag(void){
    if(abrirArchivo(&fpWrite, "flag.txt", "w")){
        cerrarArchivo(&fpWrite);
    }
}
