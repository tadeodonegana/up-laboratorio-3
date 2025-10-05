#include "espera.h"
#include "archivos.h"
#include "definiciones.h"

/* Verifica si el archivo semaforo.txt existe.*/
void esperarProcesoInit(){
    int abierto = FALSO;

    while(!abierto){
        if(abrirArchivo(&fp, "flag.txt", "r")){
            abierto = VERDADERO;
            cerrarArchivo(&fp);
        }
    }
}

/* Crea el archivo flag.txt.*/
void crearFlag(){
    if(abrirArchivo(&fp, "flag.txt", "w")){
        cerrarArchivo(&fp);
    }
}