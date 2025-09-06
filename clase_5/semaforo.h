#ifndef _SEMAFORO_H
#define _SEMAFORO_H
int creo_semaforo(void);
void inicia_semaforo(int id_semaforo, int valor);
void levanta_semaforo(int id_semaforo);
void espera_semaforo(int id_semaforo);

#endif
