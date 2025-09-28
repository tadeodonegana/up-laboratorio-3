#include "sys/ipc.h"
#include "sys/sem.h"
#include "definiciones.h"
#include "clave.h"
#include "stdio.h"
#include "stdlib.h"


int creoSemaforo(int clave_base) {
    key_t clave = creoClave(clave_base);
    int id_semaforo = semget(clave, 1, 0600|IPC_CREAT);
    if(id_semaforo == -1) {
        printf("Error: no puedo crear semáforo\n");
        exit(0);
    }
    return id_semaforo;
}

void iniciaSemaforo(int id_semaforo, int valor) {
    semctl(id_semaforo, 0, SETVAL, valor);
}

void levantaSemaforo(int id_semaforo) {
    struct sembuf operacion;
    printf("Levanta semáforo \n");
    operacion.sem_num = 0;
    operacion.sem_op = 1;
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}

void esperaSemaforo(int id_semaforo) {
    struct sembuf operacion;
    printf("Espera semáforo... \n");
    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    semop(id_semaforo, &operacion, 1);
}
