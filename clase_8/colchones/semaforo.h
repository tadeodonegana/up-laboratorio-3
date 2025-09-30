#ifndef _SEMAFORO_H
#define _SEMAFORO_H
int creoSemaforo(int clave_base);
void iniciaSemaforo(int id_semaforo, int valor);
void levantaSemaforo(int id_semaforo);
void esperaSemaforo(int id_semaforo);

#endif
