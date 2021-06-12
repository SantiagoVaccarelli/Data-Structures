#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

//DEFINICION DE LOS STRUCTS lista, nodo y lista_iter

typedef struct nodo{
    void *dato;
    struct nodo *prox;
}nodo_t;

typedef struct lista{
    nodo_t *primero;
    nodo_t *ultimo;
    size_t largo;
} lista_t;

typedef struct lista_iter{
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
} lista_iter_t;


//FUNCION AUXILIAR PARA CREAR NODOS 

nodo_t* nodo_crear(void *dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

//PRIMITIVAS DE LA LISTA

lista_t *lista_crear(void){
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return (!lista->largo);
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) lista->ultimo = nodo;
    else nodo->prox = lista->primero;       
    lista->primero = nodo;
    lista->largo++;
    return true;
} 

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) lista->primero = nodo;
    else lista->ultimo->prox = nodo;
    lista->ultimo = nodo;
    lista->largo++;
    return true;
} 

void *lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;
    nodo_t *aux = lista->primero;
    void *dato = lista->primero->dato;
    lista->primero = lista->primero->prox;
    lista->largo--;
    free(aux);
    if (lista_esta_vacia(lista)) lista->ultimo = NULL;
    return dato;
} 

void *lista_ver_primero(const lista_t *lista){
    return (lista_esta_vacia(lista)? NULL:lista->primero->dato);
}

void *lista_ver_ultimo(const lista_t* lista){
    return (lista_esta_vacia(lista)? NULL:lista->ultimo->dato);
} 

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    // lo pude mejorar para que sea solo con un while pasando la condicion de si existe destruir dato adentro del ciclo
    while (!lista_esta_vacia(lista)){
        void *aux = lista_borrar_primero(lista);
        if (destruir_dato) destruir_dato(aux);
    }
    free(lista);
}

//PRIMITIVAS DEL ITERADOR EXTERNO

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = NULL;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)) return false;
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    return (lista_iter_al_final(iter)? NULL: iter->actual->dato); 
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;
    nodo->prox = iter->actual;
    if (lista_iter_al_final(iter)) iter->lista->ultimo = nodo;
    if (iter->actual != iter->lista->primero) iter->anterior->prox = nodo;
    else iter->lista->primero = nodo;
    iter->actual = nodo;
    iter->lista->largo++;
    return true;

}

void *lista_iter_borrar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)) return NULL;
    nodo_t *nodo_aux = iter->actual;
    void *aux = iter->actual->dato;
    if (iter->actual == iter->lista->primero) iter->lista->primero = iter->actual->prox;
    else iter->anterior->prox = iter->actual->prox;
    if (iter->actual == iter->lista->ultimo) iter->lista->ultimo = iter->anterior;
    iter->actual = iter->actual->prox;
    iter->lista->largo--;
    free(nodo_aux);
    return aux;
}

//PRIMITIVA DEL ITERADOR INTERNO

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
    if(lista_esta_vacia(lista) || !visitar) return;
    nodo_t *nodo = lista->primero;
    void *dato = lista->primero->dato;
    while (nodo){
        if (!visitar(dato, extra)) return;
        nodo = nodo->prox;
        if (nodo) dato = nodo->dato;
    }
}
