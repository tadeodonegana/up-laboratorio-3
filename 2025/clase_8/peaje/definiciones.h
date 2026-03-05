#ifndef _DEF_
#define _DEF_

#define LOTE_SIZE 10
#define CANTIDAD 10
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

typedef struct peaje_dato peaje;
struct peaje_dato
{
    int vehiculos_en_cola[MAX_VIAS];
};
#endif
