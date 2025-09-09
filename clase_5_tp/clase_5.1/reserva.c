#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "definiciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "time.h"
#include "global.h"
#include "unistd.h"

int main(int arc, char *argv[])
{
    int i, vuelo, encontrado;
    int num_vuelos = 0;
    int secuenciaArchivo = 0;
    char cadena[LARGO];
    char destino[MAX_DESTINO];
    char nombre_pasajero[MAX_PASAJERO];
    Resumen resumen[MAX_VUELOS] = {0};

    memset(resumen, 0x00, sizeof(resumen));
    memset(cadena, 0x00, sizeof(cadena));
    memset(destino, 0x00, sizeof(destino));

    id_semaforo = creo_semaforo();

    while(1)
    {
        espera_semaforo(id_semaforo);

        if(!abrirArchivo(&fpRead, ARCHIVO, "r"))
        {
            printf("Error al abrir el archivo %s\n", ARCHIVO);
        }else
        {
            printf("Procesando reservas...\n");

            while(leerArchivo(cadena, LARGO))
            {
                /*Lee la cadena y extrae numero de vuelo, destino y nombre del pasajero*/
                sscanf(cadena, "%d,%[^,],%s", &vuelo, destino, nombre_pasajero);
                encontrado = FALSE;

                for(i=0; i < num_vuelos; i++)
                {
                    /*Evito duplicados en vuelos, los sumo al existente*/
                    if(resumen[i].numero == vuelo)
                    {
                        resumen[i].pasajeros++;
                        encontrado = TRUE;
                        break;
                    }
                }

                if(!encontrado && num_vuelos < MAX_VUELOS)
                {
                    resumen[num_vuelos].numero = vuelo;
                    strncpy(resumen[num_vuelos].destino, destino, MAX_DESTINO);
                    resumen[num_vuelos].pasajeros = 1;
                    num_vuelos++;
                }
            }
            cerrarArchivo(&fpRead);

            /*Renombro el archivo despues de procesarlo*/
            if (renombrarArchivo(ARCHIVO, secuenciaArchivo)) {
                printf("Archivo procesado y renombrado correctamente.\n");
                /*Incremento la secuencia para el proximo archivo*/
                secuenciaArchivo++;
            } else {
                printf("Error al renombrar el archivo.\n");
            }            
            printf("\nResumen de reservas (acumulativo):\n");
            printf("VUELO DESTINO PASAJEROS\n");
            for (i = 0; i < num_vuelos; i++) {
                printf("%d %s %d\n", resumen[i].numero, resumen[i].destino, resumen[i].pasajeros);
                /*Espero 0.3s*/
                usleep(300*1000);
            }
        }
        levanta_semaforo(id_semaforo);
        usleep(300*1000);
    }
    return 0;
}
