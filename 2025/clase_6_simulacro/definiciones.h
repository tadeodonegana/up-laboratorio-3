#ifndef _DEF_
#define _DEF_

#define LOTE_SIZE 10

#define VERDE   1
#define ROJO    0
#define LARGO   100
#define CLAVE_BASE  33

#define TRUE    1
#define FALSE   0

#define CAJERO_1 "cajero1.dat"
#define CAJERO_2 "cajero2.dat"
#define CAJERO_3 "cajero3.dat"
#define PRECIO_LIMITE 20000
#define MAX_PRODUCTOS 50

#define ESPERA_CAJA 100

#define MIN_UNIDADES_CAJA1 1
#define MAX_UNIDADES_CAJA1 5
#define MIN_UNIDADES_CAJA2 6
#define MAX_UNIDADES_CAJA2 10
#define MIN_UNIDADES_CAJA3 11

typedef struct 
{
    int precio;
    char descripcion[LARGO];
} Producto;

#endif
