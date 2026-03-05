#ifndef _DEF_
#define _DEF_

#define LOTE_SIZE 10
#define CANTIDAD 10
#define CANTIDAD_TOTAL 10
#define DESDE 1
#define HASTA 100
#define CLAVE_BASE 33
#define TRUE    1
#define FALSE   0
#define VERDE 1
#define ROJO 0
#define LARGO 			100
#define INTERVALO_PEDIDOS 2000

typedef struct tipo_dato dato;
struct tipo_dato
{
    int numero;
    char letra;
};

typedef struct mensaje {
    long long_dest;          
    int int_rte;            
    int int_evento;         
    char char_mensaje[LARGO];
} mensaje;

typedef enum
{
	EVT_NINGUNO,
	EVT_CONSULTA_STOCK,
	EVT_RESPUESTA_STOCK,
	EVT_SUMA_STOCK,
	EVT_RESTA_STOCK
}Eventos;

typedef enum
{
	MSG_NADIE,				
	MSG_SUPERMERCADO,		
	MSG_REPOSITOR,			
	MSG_CLIENTE	
}Destinos;

#endif
