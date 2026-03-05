#include <stdio.h>
#include <stdlib.h>
#include "archivos.h"
#include "string.h"
#include "definiciones.h"

typedef struct {
    char nombre[50];
    int legajo;
    int sueldo;
} Empleado;

void escribirEmpleados(void){
    Empleado emp;
    char buffer[100+1];
    int continuar = 1;

    if (!inAbrirArchivo("empleados.txt", "w")){
        printf("No se puede abrir el archivo para su escritura.\n");
        return;
    }

    while(continuar){
        printf("Ingrese nombre: ");
        scanf("%s", emp.nombre);

        printf("Ingrese legajo: ");
        scanf("%d", &emp.legajo);

        printf("Ingrese sueldo: ");
        scanf("%i", &emp.sueldo);

        sprintf(buffer, "%s %d %i\n", emp.nombre, emp.legajo, emp.sueldo);

        if(!inEscribirArchivo(buffer)){
            printf("Error al escribir el archivo.\n");
        }
        printf("¿Desea ingresar otro empleado? (1: Si, 0: No): ");
        scanf("%d", &continuar);
    }
    voCerrarArchivo();
}

void leerEmpleados(void){
    char linea[100+1];
    char nombre[50+1];
    int legajo;
    int sueldo;
    if (!inAbrirArchivo("empleados.txt", "r")) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }
    
    while (!feof(ptrFile)) {
        if (inLeerArchivo(linea)==TRUE) {
            /*Se puede cargar en variables por los espacios, usando sscanf*/
            if (sscanf(linea, "%s %d %d", nombre, &legajo, &sueldo) == 3) {
                printf("Nombre: %s | Legajo: %d | Sueldo: %d\n", nombre, legajo, sueldo);
            }
        }
    }
    voCerrarArchivo();
}

int main(int argc,char *argv[]) {
    escribirEmpleados();
    printf("\n=== Datos leídos del archivo ===\n");
    leerEmpleados();
    
    return 0;
}
