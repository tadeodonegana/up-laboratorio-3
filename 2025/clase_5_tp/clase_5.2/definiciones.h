#ifndef _DEF_
#define _DEF_

#define ROJO  			0
#define VERDE 			1
#define LARGO 			100
#define CLAVE_BASE 33

#define TRUE 1
#define FALSE 0

#define ARCHIVO "lote.dat"

#define MAX_CAJEROS 3
#define LOTE_SIZE 10

#define IMPORTE_MIN 100
#define IMPORTE_MAX 500

#define TIPO_CHEQUE 0
#define TIPO_EFECTIVO 1

typedef struct {
    int cajero;
    int importe;
    int tipo; /* 0 para cheque, 1 para efectivo */
} Deposito;

typedef struct {
    int cajero;
    int tc_efec;  /* Total Cajero Efectivo */
    int ts_efec;  /* Total Sistema Efectivo */
    int tc_cheq;  /* Total Cajero Cheque */
    int ts_cheq;  /* Total Sistema Cheque */
} ResumenCajero;

#endif
