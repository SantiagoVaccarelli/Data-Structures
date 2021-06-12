#include "pila.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define CANTIDAD_INICIAL 0
#define CAPACIDAD 10
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

//Funcion auxiliar de redimensionamiento.

bool pila_redimensionar(pila_t *pila, size_t capacidad_nueva){
    void *aux = realloc(pila->datos, capacidad_nueva * sizeof(void*));
    if (!aux) return false;
    pila->datos = aux;
    pila->capacidad = capacidad_nueva;
    return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t *pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    if (pila == NULL) return NULL;
    pila->cantidad = CANTIDAD_INICIAL;
    pila->capacidad = CAPACIDAD;
    pila->datos = malloc(sizeof(void*)*pila->capacidad);
    if (pila->datos == NULL){
        free(pila);
        return NULL;}
    return pila;
}


void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
    return (pila->cantidad == 0);
}

bool pila_apilar(pila_t *pila, void *valor){
    if (pila->cantidad == pila->capacidad) {
        if (!pila_redimensionar(pila, pila->capacidad *2)) return false;
    }
    pila->datos[(pila->cantidad)] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    return (pila->cantidad == 0)? NULL: pila->datos[(pila->cantidad)-1];
}


void *pila_desapilar(pila_t *pila){
    if (pila->cantidad == 0) return NULL;
    pila->cantidad --;
    void* tope = pila->datos[(pila->cantidad)];
    if (pila->cantidad * 4 == pila->capacidad) pila_redimensionar(pila, (pila->capacidad)/2);
    return tope;
}