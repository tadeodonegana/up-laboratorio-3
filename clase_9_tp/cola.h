#ifndef COLA_H
#define COLA_H
#include "definiciones.h"
int creoIdColaMensajes(int clave);
int enviarMensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento,char* rpCharMsg);
int recibirMensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg);
void liberarCola(int id_cola_mensajes);
int borrarTodaCola(int id_cola_mensajes);

#endif
