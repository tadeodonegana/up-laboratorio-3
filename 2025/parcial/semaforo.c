#include "sys/ipc.h"
#include "sys/sem.h"
#include "definiciones.h"
#include "clave.h"
#include "stdio.h"
#include "stdlib.h"


int creoSemaforo(void) {
    key_t clave = creoClave();
    int idSemaforo = semget(clave, 1, 0600|IPC_CREAT);
    if(idSemaforo == -1) {
        printf("Error: no puedo crear semáforo\n");
        exit(0);
    }
    return idSemaforo;
}

void iniciaSemaforo(int idSemaforo, int valor) {
    semctl(idSemaforo, 0, SETVAL, valor);
}

void levantaSemaforo(int idSemaforo) {
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop(idSemaforo, &operacion, 1);
}

void esperaSemaforo(int idSemaforo) {
    struct sembuf operacion;
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop(idSemaforo, &operacion, 1);
}
