#include "clave.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include "definiciones.h"
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "cola.h"
#include <sys/msg.h>

int creoIdColaMensajes(int clave) {
    int id_cola_mensajes = msgget(creoClave(clave), 0600 | IPC_CREAT);
    if (id_cola_mensajes == -1) {
        printf("Error al obtener id para cola de mensajes\n");
        exit(-1);
    }
    return id_cola_mensajes;
}

int enviarMensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg) 
{
    mensaje msg;
    msg.long_dest = rLongDest;
    msg.int_rte = rIntRte;
    msg.int_evento = rIntEvento;
    strcpy(msg.char_mensaje, rpCharMsg);
    return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), IPC_NOWAIT);
}

int recibirMensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg) 
{
    mensaje msg;
    int res;
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), rLongDest,0);
    rMsg->long_dest = msg.long_dest;
    rMsg-> int_rte = msg.int_rte;
    rMsg-> int_evento = msg.int_evento;
    strcpy(rMsg->char_mensaje, msg.char_mensaje);
    return res;
}

void liberarCola(int id_cola_mensajes){
    msgctl (id_cola_mensajes, IPC_RMID, (struct msqid_ds *)NULL);
}


int borrarTodaCola(int id_cola_mensajes){
    mensaje msg;
	int res;
	do
	{
		res = msgrcv (id_cola_mensajes, (struct msgbuf *)&msg, sizeof(msg.int_rte)+sizeof(msg.int_evento)+sizeof(msg.char_mensaje), 0, IPC_NOWAIT);
	}while(res>0);
	return res;
}
