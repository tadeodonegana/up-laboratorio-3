#include <sys/ipc.h>
#include "clave.h"
#include "stdio.h"
#include "stdlib.h"

key_t creoClave(void) {
    key_t clave;
    clave = ftok("/bin/ls", 33);
    if (clave == (key_t)-1) {
        printf("No puedo conseguir clave semáforo\n");
        exit(0);
    }
    return clave;
}
