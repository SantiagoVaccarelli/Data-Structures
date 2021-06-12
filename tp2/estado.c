#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mensajes.h"
#include "estado.h"

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct estado{
    heap_t* regulares;
    cola_t* urgentes;
};

int cmp(const void* a, const void* b){

	if (*(const int*) a == *(const int*) b) return 0;
	if (*(const int*) a > *(const int*) b) return 1;
	return -1;
}


/* ******************************************************************
 *                DEFINICION DE LAS PRIMITIVAS DE ESTADO
 * *****************************************************************/

estado_t* crear_estado(){
    estado_t* estado = malloc(sizeof(estado_t));
    if(!estado) return NULL;
    heap_t* heap = heap_crear(cmp);
    if (!heap) return NULL;
    cola_t* cola = cola_crear();
    if(!cola){
        heap_destruir(heap, NULL);
        return NULL;
        }
    estado->regulares = heap;
    estado-> urgentes = cola;
    return estado;
}

void *estado_borrar(estado_t *estado){
    if (cola_esta_vacia(estado->urgentes) && heap_esta_vacio(estado->regulares)) return NULL;
    if (!cola_esta_vacia(estado->urgentes)) return cola_desencolar(estado->urgentes);
    return heap_desencolar(estado->regulares);
}   

bool estado_guardar(estado_t* estado,char* urgencia,paciente_t* paciente){
    if(!paciente) return false;
    if (strcmp(urgencia,"URGENTE")==0) return cola_encolar(estado->urgentes,paciente);
    if (strcmp(urgencia,"REGULAR")==0) return heap_encolar(estado->regulares,paciente);
    printf(ENOENT_URGENCIA,urgencia);
    return false;
}

bool estado_esta_vacio(estado_t *estado){
    return (heap_esta_vacio(estado->regulares) && cola_esta_vacia(estado->urgentes));
}

size_t estado_pacientes_restantes(estado_t* estado){
    return (heap_cantidad(estado->regulares)+cola_cantidad(estado->urgentes));
}

void estado_destruir(estado_t* estado,void (*destruir_dato)(void *)){
    heap_destruir(estado->regulares, NULL);
    cola_destruir(estado->urgentes, NULL);
    free(estado);
}

