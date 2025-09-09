#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "time.h"
#include "global.h"
#include "unistd.h"

int main(int arc, char *argv[])
{
    int i, cajero, importe, tipo, idx;
    int secuenciaArchivo = 0;
    char cadena[LARGO];
    ResumenCajero resumen[MAX_CAJEROS] = {0};
    int total_sistema_efec = 0, total_sistema_cheq = 0;

    memset(resumen, 0x00, sizeof(resumen));
    for (i = 0; i < MAX_CAJEROS; i++) {
        resumen[i].cajero = i + 1;
    }

    id_semaforo = creo_semaforo();
    printf("TESORERO iniciado (Semáforo ID: %d)\n", id_semaforo);

    while(1)
    {
        espera_semaforo(id_semaforo);

        if(!abrirArchivo(&fpRead, ARCHIVO, "r"))
        {
            printf("Archivo %s no disponible, esperando...\n", ARCHIVO);
        }else
        {
            printf("\nTESORERO - Procesando lote de depósitos...\n");

            while(leerArchivo(cadena, LARGO))
            {
                /* Lee la cadena y extrae cajero, importe y tipo */
                sscanf(cadena, "%d,%d,%d", &cajero, &importe, &tipo);
                
                if (cajero >= 1 && cajero <= MAX_CAJEROS) {
                    idx = cajero - 1;
                    
                    if (tipo == TIPO_EFECTIVO) {
                        resumen[idx].tc_efec += importe;
                        total_sistema_efec += importe;
                    } else if (tipo == TIPO_CHEQUE) {
                        resumen[idx].tc_cheq += importe;
                        total_sistema_cheq += importe;
                    }
                }
            }
            cerrarArchivo(&fpRead);

            /* Renombrar el archivo después de procesarlo */
            if (renombrarArchivo(ARCHIVO, secuenciaArchivo)) {
                printf("Lote procesado y archivado correctamente.\n");
                secuenciaArchivo++;
            } else {
                printf("Error al archivar el lote.\n");
            }            
            
            /* Mostrar resumen actualizado */
            printf("\n=== RESUMEN DE DEPÓSITOS (ACUMULATIVO) ===\n");
            printf("CAJERO\tTC-EFEC\tTS-EFEC\tTC-CHEQ\tTS-CHEQ\n");
            printf("------\t-------\t-------\t-------\t-------\n");
            
            for (i = 0; i < MAX_CAJEROS; i++) {
                printf("%d\t$%d\t$%d\t$%d\t$%d\n", 
                       resumen[i].cajero,
                       resumen[i].tc_efec,
                       total_sistema_efec,
                       resumen[i].tc_cheq,
                       total_sistema_cheq);
                usleep(300*1000);
            }
            
            printf("\nTOTAL SISTEMA:\n");
            printf("Efectivo: $%d\n", total_sistema_efec);
            printf("Cheques:  $%d\n", total_sistema_cheq);
            printf("TOTAL:    $%d\n", total_sistema_efec + total_sistema_cheq);
        }
        levanta_semaforo(id_semaforo);
        usleep(1000*500);
    }
    return 0;
}
