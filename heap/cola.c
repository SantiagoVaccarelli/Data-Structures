#include "cola.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



typedef struct nodo{
    void *dato;
    struct nodo *siguiente;
}nodo_t;


struct cola {
    nodo_t *primero;
    nodo_t *ultimo;
};

cola_t *cola_crear(void){
    cola_t *cola = malloc(sizeof(nodo_t));
    if (cola == NULL) return NULL;
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}


void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    if (destruir_dato == NULL) while (!cola_esta_vacia(cola)) cola_desencolar(cola);
    else {
        void *aux = cola_desencolar(cola);
        while (aux != NULL) {
            destruir_dato(aux);
            aux = cola_desencolar(cola);
        }
    }
    free(cola);
}


bool cola_esta_vacia(const cola_t *cola){
    return (!cola->primero);
}


bool cola_encolar(cola_t *cola, void *valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) return false;
    nodo->dato = valor;
    nodo->siguiente = NULL;
    if (cola_esta_vacia(cola)){
        cola->primero = nodo;
        cola->ultimo = nodo;
    }
    else{
        cola->ultimo->siguiente = nodo;
        cola->ultimo = nodo;
    }
    return true;
}

void *cola_ver_primero(const cola_t *cola){
    return cola_esta_vacia(cola)? NULL:(cola->primero->dato);
}

void *cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)) return NULL;
    void* dato = cola->primero->dato;
    nodo_t* segundo_nodo = cola->primero->siguiente;
    free(cola->primero);
    cola->primero = segundo_nodo;
    return dato;
}
