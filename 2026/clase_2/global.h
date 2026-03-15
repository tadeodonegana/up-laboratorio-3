#ifndef GLOBAL_H
#define GLOBAL_H

extern char szVarGlobal[20+1];
extern int inNumAl;
typedef struct tipo_datos datos;
struct tipo_datos
{
    int dato;
};
typedef enum
{
    MSG_NADIE,
    MSG_SUPERMERCADO,
    MSG_REPOSITOR
}Destinos;

#endif
