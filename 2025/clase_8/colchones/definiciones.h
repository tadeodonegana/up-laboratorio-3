#ifndef _DEF_
#define _DEF_

#define LOTE_SIZE 10
#define CANTIDAD 5
#define CANTIDAD_TOTAL 10
#define DESDE 1
#define HASTA 99
#define CLAVE_BASE 33
#define TRUE    1
#define FALSE   0
#define VERDE 1
#define ROJO 0
#define LARGO 			100
#define MAX_VIAS 10
#define LARGO_NOMBRE 100
#define NUM_COLCHONES 5
#define STOCK_INICIAL 10
#define STOCK_MAXIMO 10

typedef struct colchon_dato colchon;
struct colchon_dato
{
    int codigo;
    int cantidad;
    char nombre[LARGO_NOMBRE];
};
#endif
