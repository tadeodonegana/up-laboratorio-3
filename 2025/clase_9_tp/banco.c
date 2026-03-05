#include "funciones.h"
#include "archivos.h"
#include "cola.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"
#include "memoria.h"
#include "semaforo.h"
#include "definiciones.h"
#include "espera.h"

/* Función para limpiar recursos */
void limpiar_recursos(void) {
    borrarTodaCola(id_cola_mensajes);
    liberarCola(id_cola_mensajes);
}

/* Manejador de señal SIGINT */
void sigint_handler(int signo) {
    printf("\nRecibida señal SIGINT. Limpiando recursos...\n");
    limpiar_recursos();
    exit(0);
}

void procesar_evento(int id_cola_mensajes, mensaje msg, Cliente* memoria_clientes)
{
    char respuesta[LARGO];
    char copia[LARGO];
    char* token = NULL;
    int codigo = 0;
    int importe = 0;

    memset(respuesta, 0x00, sizeof(respuesta));
    memset(copia, 0x00, sizeof(copia));
    memcpy(copia, msg.char_mensaje, LARGO);

    printf("Destino   %d\n", (int) msg.long_dest);
    printf("Remitente %d\n", msg.int_rte);
    printf("Evento    %d\n", msg.int_evento);
    printf("Mensaje   %s\n", msg.char_mensaje);

    switch (msg.int_evento)
    {
        case EVT_CONSULTA_SALDO:
		    /* Primera parte del mensaje*/
            token = strtok(copia, "|");
            if (token != NULL) {
                codigo = atoi(token);
            }
            if (codigo < 1 || codigo > MAX_CLIENTES) {
                snprintf(respuesta, LARGO, "%d|CLIENTE_INEXISTENTE", codigo);
                enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_SALDO_NOK, respuesta);
                break;
            }
            snprintf(respuesta, LARGO, "%d|%d", codigo, memoria_clientes[codigo-1].saldo);
            enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_SALDO, respuesta);
        break;

        case EVT_DEPOSITO:
		    /* Obtengo primera parte del mensaje*/
            token = strtok(copia, "|");
            if (token != NULL) {
                codigo = atoi(token);
            }
            /* Segunda parte del mensaje*/
            token = strtok(NULL, "|");
            if (token != NULL) {
                importe = atoi(token);
            }
            if (codigo < 1 || codigo > MAX_CLIENTES) {
                snprintf(respuesta, LARGO, "%d|CLIENTE_INEXISTENTE", codigo);
                enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_NOK, respuesta);
                break;
            }
            esperaSemaforo(id_semaforo);
            memoria_clientes[codigo-1].saldo += importe;
            levantaSemaforo(id_semaforo);
            snprintf(respuesta, LARGO, "%d|%d", codigo, memoria_clientes[codigo-1].saldo);
            enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_DEPOSITO_OK, respuesta);
        break;

        case EVT_EXTRACCION:
            token = strtok(copia, "|");
            if (token != NULL) {
                codigo = atoi(token);
            }
            token = strtok(NULL, "|");
            if (token != NULL) {
                importe = atoi(token);
            }
            if (codigo < 1 || codigo > MAX_CLIENTES) {
                snprintf(respuesta, LARGO, "%d|CLIENTE_INEXISTENTE", codigo);
                enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, respuesta);
                break;
            }
            esperaSemaforo(id_semaforo);
            if (memoria_clientes[codigo-1].saldo >= importe) {
                memoria_clientes[codigo-1].saldo -= importe;
                levantaSemaforo(id_semaforo);
                snprintf(respuesta, LARGO, "%d|%d", codigo, memoria_clientes[codigo-1].saldo);
                enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_OK, respuesta);
            } else {
                levantaSemaforo(id_semaforo);
                snprintf(respuesta, LARGO, "%d|SALDO_INSUFICIENTE", codigo);
                enviarMensaje(id_cola_mensajes, msg.int_rte, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, respuesta);
            }
        break;

        default:
            printf("\nEvento sin definir\n");
        break;
    }
    printf("------------------------------\n");
}

int main(int argc, char *argv[]){
    int id_memoria, i;
    Cliente* memoria_clientes;
    mensaje msg;

    id_cola_mensajes = creoIdColaMensajes(CLAVE_BASE);
    id_semaforo = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id_semaforo, VERDE);

    /* El semáforo está listo para otros procesos */
    crearFlag();

    memoria_clientes = (Cliente*)creoMemoria(sizeof(Cliente)*MAX_CLIENTES, &id_memoria, CLAVE_BASE);

    for (i = 0; i < MAX_CLIENTES; i++) {
        memoria_clientes[i].codigo = i + 1;
        memoria_clientes[i].saldo = 0;
    }

    signal(SIGINT, sigint_handler);

    while(1)
    {
        memset(&msg, 0x00, sizeof(msg));
        recibirMensaje(id_cola_mensajes, MSG_BANCO, &msg);
        procesar_evento(id_cola_mensajes, msg, memoria_clientes);
    }

    return 0;
}
