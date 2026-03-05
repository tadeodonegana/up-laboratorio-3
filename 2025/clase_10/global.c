#include "global.h"
#include <pthread.h>

int productoActual = 0;
int id_semaforo;
pthread_mutex_t mutex;
