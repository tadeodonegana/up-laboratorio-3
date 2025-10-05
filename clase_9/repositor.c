#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "funciones.h"
#include "archivos.h"
#include "cola.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"

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

void procesar_evento(int id_cola_mensajes, mensaje msg)
{

	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_RESPUESTA_STOCK:
			printf("Rta stock\n");
			printf("STOCK %d\n", atoi(msg.char_mensaje));
		break;

		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printf("------------------------------\n");
}

int main(int argc, char *argv[]){

    mensaje msg;

    id_cola_mensajes = creoIdColaMensajes(CLAVE_BASE);	
	
    while(1)
	{
		enviarMensaje(id_cola_mensajes , MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_SUMA_STOCK, "SUMA UNO");
		enviarMensaje(id_cola_mensajes , MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_CONSULTA_STOCK, "DECIME EL STOCK POR FAVOR");
		memset(&msg, 0x00, sizeof(msg));
		recibirMensaje(id_cola_mensajes, MSG_REPOSITOR, &msg);
		procesar_evento(id_cola_mensajes, msg);
        usleep(INTERVALO_PEDIDOS*1000);
    }
    
    return 0;
}
