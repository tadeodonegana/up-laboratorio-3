#ifndef _SEMAFORO_H
#define _SEMAFORO_H
int creoSemaforo(void);
void iniciaSemaforo(int idSemaforo, int valor);
void levantaSemaforo(int idSemaforo);
void esperaSemaforo(int idSemaforo);

#endif
