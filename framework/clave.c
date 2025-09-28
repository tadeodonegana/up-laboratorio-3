#include <sys/ipc.h>
#include "clave.h"
#include "stdio.h"
#include "stdlib.h"
#include "definiciones.h"

key_t creoClave(int clave_base) {
    key_t clave;
    clave = ftok("/bin/ls", clave_base);
    if (clave == (key_t)-1) {
        printf("No puedo conseguir clave semáforo\n");
        exit(0);
    }
    return clave;
}
