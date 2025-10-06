#include "funciones.h"
#include "archivos.h"
#include "cola.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"
#include "definiciones.h"
#include "espera.h"

void mostrarMenuCajero(void)
{
    printf("1. Consulta de saldo\n");
    printf("2. Deposito\n");
    printf("3. Extraccion\n");
    printf("4. Salir\n");
    printf("Ingrese una opcion: ");
}

int main(int argc, char *argv[]){
    int opcion, codigo, importe, numeroCajero;
    long cajeroDestino;
    char cadena[LARGO];
    mensaje msg;

    id_cola_mensajes = creoIdColaMensajes(CLAVE_BASE);

    /* Esperar a que el banco inicialice el semáforo */
    esperarProcesoInit();

    /* Numero de cajero por argumento, por defecto 1 */
    numeroCajero = 1;
    if (argc == 2)
    {
        numeroCajero = atoi(argv[1]);
        if (numeroCajero < 1)
        {
            numeroCajero = 1;
        }
    }
    printf("Cajero %d iniciado\n", numeroCajero);

    /* Cada cajero tiene su numero de destino, para diferenciar remitentes/respuestas */
    cajeroDestino = 1000 + numeroCajero;

    while(1)
    {
        opcion = 0;
        codigo = 0;
        importe = 0;
        memset(cadena, 0x00, sizeof(cadena));

        mostrarMenuCajero();
        scanf("%d", &opcion);

        if (opcion == 1)
        {
            printf("Ingrese codigo de cliente: ");
            scanf("%d", &codigo);
            snprintf(cadena, LARGO, "%d", codigo);
            enviarMensaje(id_cola_mensajes , MSG_BANCO, (int)cajeroDestino, EVT_CONSULTA_SALDO, cadena);
            memset(&msg, 0x00, sizeof(msg));
            recibirMensaje(id_cola_mensajes, cajeroDestino, &msg);
            printf("Respuesta (%d): %s\n", msg.int_evento, msg.char_mensaje);
        }
        else if (opcion == 2)
        {
            printf("Ingrese codigo de cliente: ");
            scanf("%d", &codigo);
            printf("Ingrese importe: ");
            scanf("%d", &importe);
            snprintf(cadena, LARGO, "%d|%d", codigo, importe);
            enviarMensaje(id_cola_mensajes , MSG_BANCO, (int)cajeroDestino, EVT_DEPOSITO, cadena);
            memset(&msg, 0x00, sizeof(msg));
            recibirMensaje(id_cola_mensajes, cajeroDestino, &msg);
            printf("Respuesta (%d): %s\n", msg.int_evento, msg.char_mensaje);
        }
        else if (opcion == 3)
        {
            printf("Ingrese codigo de cliente: ");
            scanf("%d", &codigo);
            printf("Ingrese importe: ");
            scanf("%d", &importe);
            snprintf(cadena, LARGO, "%d|%d", codigo, importe);
            enviarMensaje(id_cola_mensajes , MSG_BANCO, (int)cajeroDestino, EVT_EXTRACCION, cadena);
            memset(&msg, 0x00, sizeof(msg));
            recibirMensaje(id_cola_mensajes, cajeroDestino, &msg);
            printf("Respuesta (%d): %s\n", msg.int_evento, msg.char_mensaje);
        }
        else if (opcion == 4)
        {
            break;
        }
        else
        {
            printf("Opcion invalida\n");
        }
    }

    return 0;
}
