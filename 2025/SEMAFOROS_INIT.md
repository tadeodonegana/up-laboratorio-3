# Inicialización coordinada de semáforos con flag de archivo

Este documento explica cómo usar las funciones `crearFlag` y `esperarProcesoInit` definidas en `clase_9/espera.c` para coordinar la inicialización de semáforos entre dos procesos.

- **Proceso A (iniciador del semáforo)**: crea el semáforo, lo inicializa y crea el archivo `flag.txt` llamando `crearFlag`.
- **Proceso B (consumidor que depende del semáforo)**: espera a que exista `flag.txt` llamando `esperarProcesoInit` antes de entrar en su lazo principal `while(1)`.

Esta sincronización por archivo evita que el Proceso B comience sin que el semáforo esté correctamente creado e inicializado por el Proceso A.

---

## API disponible

```1:8:/Users/tadeo/Documents/Code/labo3/clase_9/espera.h
#ifndef _ESPERA_H
#define _ESPERA_H

void esperarProcesoInit();
void crearFlag();

#endif
```

```1:22:/Users/tadeo/Documents/Code/labo3/clase_9/espera.c
#include "espera.h"
#include "archivos.h"
#include "definiciones.h"

/* Verifica si el archivo semaforo.txt existe.*/
void esperarProcesoInit(){
    int abierto = FALSO;

    while(!abierto){
        if(abrirArchivo(&fp, "flag.txt", "r")){
            abierto = VERDADERO;
            cerrarArchivo(&fp);
        }
    }
}

/* Crea el archivo flag.txt.*/
void crearFlag(){
    if(abrirArchivo(&fp, "flag.txt", "w")){
        cerrarArchivo(&fp);
    }
}
```

> Nota: `espera.c` usa `abrirArchivo`/`cerrarArchivo` de `clase_9/archivos.c`. Asegúrate de compilar y linkear esos módulos.

---

## Patrón de uso recomendado

- **Proceso A (iniciador)**
  1. Crear el semáforo con `creoSemaforo(CLAVE_BASE)`.
  2. Inicializar su valor con `iniciaSemaforo(id_semaforo, valor_inicial)`.
  3. Crear el flag con `crearFlag()` para habilitar al Proceso B.
  4. Continuar con su lógica.

- **Proceso B (dependiente)**
  1. Llamar a `esperarProcesoInit()` antes de su `while(1)`.
  2. Luego de que retorna, ya es seguro usar `id_semaforo` para `esperaSemaforo/levantaSemaforo`.

---

## Ejemplos concretos (adaptables a tus procesos)

A continuación se muestran ejemplos mínimos de cómo integrar estas llamadas en dos procesos tipo. Ajusta includes y lógica a tus fuentes reales.

### Proceso A: iniciador del semáforo

```c
#include "stdio.h"
#include "stdlib.h"
#include "semaforo.h"
#include "clave.h"
#include "definiciones.h"
#include "espera.h"
#include "global.h"

int main(int argc, char *argv[]) {
    /* Declaraciones al inicio */
    int id;

    /* Crear e inicializar semáforo */
    id = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id, 1); /* por ejemplo, valor inicial 1 */

    /* Hacer visible que el semáforo ya está listo */
    crearFlag();

    /* Guardar id si usas variable global */
    id_semaforo = id;

    /* Resto de la lógica del proceso A */
    printf("Semáforo iniciado y flag creado.\n");
    return 0;
}
```

### Proceso B: espera la inicialización

```c
#include "stdio.h"
#include "stdlib.h"
#include "semaforo.h"
#include "clave.h"
#include "definiciones.h"
#include "espera.h"
#include "global.h"

int main(int argc, char *argv[]) {
    /* Declaraciones al inicio */
    int id;

    /* Esperar a que el Proceso A inicialice el semáforo */
    esperarProcesoInit();

    /* Obtener/crear handle al mismo semáforo (misma clave) */
    id = creoSemaforo(CLAVE_BASE);
    id_semaforo = id;

    /* Ya es seguro entrar al bucle principal */
    while(1) {
        esperaSemaforo(id_semaforo);
        /* sección crítica */
        /* ... */
        levantaSemaforo(id_semaforo);
        /* sección no crítica */
        /* ... */
    }

    return 0;
}
```

---

## Cómo integrarlo en `clase_9`

En `clase_9`, puedes aplicar este patrón a procesos como `supermercado` y `repositor`.

- Si `supermercado` debe iniciar el semáforo: agrega en su `main` la creación e inicialización y luego `crearFlag()` antes del `while(1)`.

```41:55:/Users/tadeo/Documents/Code/labo3/clase_9/supermercado.c
int main(int argc, char *argv[]){

    mensaje msg;

    id_cola_mensajes = creoIdColaMensajes(CLAVE_BASE);

    /* Crear e inicializar semáforo y liberar al otro proceso */
    id_semaforo = creoSemaforo(CLAVE_BASE);
    iniciaSemaforo(id_semaforo, 1);
    crearFlag();

    while(1)
    {
        memset(&msg, 0x00, sizeof(msg));
        recibirMensaje(id_cola_mensajes, MSG_SUPERMERCADO, &msg);
        procesar_evento(id_cola_mensajes, msg);
    }

    return 0;
}
```

- Si `repositor` debe esperar: llama a `esperarProcesoInit()` al inicio del `main`, antes del `while(1)`, y luego toma el id del semáforo con la misma clave.

```48:66:/Users/tadeo/Documents/Code/labo3/clase_9/repositor.c
int main(int argc, char *argv[]){

    mensaje msg;

    /* Esperar a que el otro proceso inicialice el semáforo */
    esperarProcesoInit();
    id_semaforo = creoSemaforo(CLAVE_BASE);

    id_cola_mensajes = creoIdColaMensajes(CLAVE_BASE);

    while(1)
    {
        enviarMensaje(id_cola_mensajes , MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_SUMA_STOCK, "SUMA UNO");
        enviarMensaje(id_cola_mensajes , MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_CONSULTA_STOCK, "DECIME EL STOCK POR FAVOR");
        memset(&msg, 0x00, sizeof(msg));
        recibirMensaje(id_cola_mensajes, MSG_REPOSITOR, &msg);
        procesar_evento(id_cola_mensajes, msg);
        usleep(INTERVALO_PEDIDOS*1000);
    }

    return 0;
}
```

> Importante: añade los `#include` necesarios (`espera.h`, `semaforo.h`, `clave.h`) en cada archivo donde uses estas funciones.

---

## Compilación

Asegúrate de linkear `espera.c`, `archivos.c`, `semaforo.c`, `clave.c` y cualquier dependencia usada por tus procesos.

Un ejemplo de reglas en `clase_9/Makefile` podría ser (ajústalo a tu proyecto si agregas nuevos .c):

```make
repositor: repositor.c archivos.c funciones.c global.c cola.c clave.c espera.c semaforo.c
	$(CC) $(FLAGS) -o repositor repositor.c archivos.c funciones.c global.c cola.c clave.c espera.c semaforo.c

supermercado: supermercado.c archivos.c funciones.c global.c cola.c clave.c espera.c semaforo.c
	$(CC) $(FLAGS) -o supermercado supermercado.c archivos.c funciones.c global.c cola.c clave.c espera.c semaforo.c
```

Si separas `espera.c`/`semaforo.c` como objetos, agrega sus `.o` a cada objetivo.

---

## Limpieza del flag

Si deseas reiniciar la sincronización, elimina `flag.txt` manualmente o con una función que llame a `borrarArchivo("flag.txt")` de `archivos.c`.

---

## Observaciones y límites

- Este mecanismo usa un archivo en disco; es simple y suficiente para coordinación de inicio.
- Asegúrate de que ambos procesos compartan el mismo directorio de trabajo para que `flag.txt` sea visible.
- Para sincronización avanzada, podrías reemplazar el flag por memoria compartida o señales, pero para esta materia el archivo es apropiado.

