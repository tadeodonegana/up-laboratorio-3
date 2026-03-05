#include "stdlib.h"
#include "stdio.h"
#include "clave.h"

int main(int argc, char *argv[]) {
    key_t clave = creo_clave();
    printf("Clave generada: %d\n", (int)clave);
    return 0;
}
