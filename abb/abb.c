#define _POSIX_C_SOURCE 200809L 
#include <string.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"
#include "pila.c"

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct nodo{
    struct nodo* izq;
    struct nodo* der; 
    char* clave;
    void* dato;
}nodo_t;

struct abb{
    nodo_t* raiz;
	size_t cantidad;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
};

struct abb_iter{
	const abb_t* abb;
    pila_t* pila;
};

/* ******************************************************************
 *                FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t *nodo_crear(const char* clave, void* dato){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    char *clave_dup = strdup(clave);
    if (!clave_dup){
        free(nodo);
        return NULL;
    }
    nodo->clave = clave_dup;
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;

}
void *destruir_nodo(nodo_t *nodo){
    void *aux = nodo->dato;
    free(nodo->clave);
	free(nodo);
    return aux;
}

bool _abb_guardar(abb_t *abb, nodo_t* raiz, nodo_t* nodo){

    if(abb->cmp(nodo->clave,raiz->clave)>0 ){
        // primero mas grande es mayor a 0 
        if(!raiz->izq) raiz->izq = nodo;
        else return _abb_guardar(abb,raiz->izq,nodo);
    }
    else if(abb->cmp(nodo->clave,raiz->clave)<=0){
        if(!raiz->der) raiz->der = nodo;
        else return  _abb_guardar(abb,raiz->der,nodo);
    }else{
        
    }
    abb->cantidad++;
    return true;
}


nodo_t *abb_buscar(nodo_t *raiz,const char *clave,abb_comparar_clave_t cmp){
    if (!raiz) return NULL;
    if(!cmp(raiz->clave, clave)) return raiz;
    return cmp(raiz->clave, clave) > 0? abb_buscar(raiz->der, clave, cmp):abb_buscar(raiz->izq, clave, cmp);
} 

nodo_t *abb_buscar_padre(nodo_t *raiz,const char *clave,abb_comparar_clave_t cmp){
    if (!cmp(raiz->clave, clave)) return NULL;
    if (!(cmp(raiz->der->clave,clave) && cmp(raiz->izq->clave,clave))) return raiz;
    return cmp(raiz->clave, clave) > 0? abb_buscar_padre(raiz->der, clave, cmp):abb_buscar_padre(raiz->izq, clave, cmp);
}

void *borrar0(abb_t *abb, nodo_t *nodo){
    nodo_t *padre = abb_buscar_padre(abb->raiz, nodo->clave, abb->cmp);
    if (!padre) abb->raiz = NULL;
    else if (abb->cmp(nodo->clave,padre->der->clave)) padre->izq = NULL;
    else padre->der = NULL;
    abb->cantidad--;
    return destruir_nodo(nodo);
}

void *borrar1(abb_t *abb, nodo_t *nodo){
    nodo_t *padre = abb_buscar_padre(abb->raiz, nodo->clave, abb->cmp);
    if (nodo->der){
        if (!padre) abb->raiz = nodo->der;
        else if(padre->der && !abb->cmp(padre->izq->clave, nodo->clave)) padre->der = nodo->der;
        else padre->izq = nodo->der;
    }
    else if (nodo->izq){
        if (!padre) abb->raiz = nodo->izq;
        else if(padre->der && !abb->cmp(padre->der->clave, nodo->clave)) padre->der = nodo->izq;
        else padre->izq = nodo->izq;
    }
    abb->cantidad--;
    return destruir_nodo(nodo);
}

nodo_t *buscar_nodo_aux(nodo_t *nodo){
    nodo_t *actual = nodo;
    while(actual->der) actual = actual->der;
    return actual;
}

void *borrar2(abb_t *abb, nodo_t *nodo){
    nodo_t *aux = buscar_nodo_aux(nodo->izq);
    char *aux_clave = strdup(aux->clave);
    void *aux_dato = abb_borrar(abb, aux->clave);
    void *nodo_dato = nodo->dato;
    nodo->dato = aux_dato;
    free(nodo->clave);
    nodo->clave = aux_clave;
    abb->cantidad--;
    return nodo_dato;
}


/* ******************************************************************
 *                DEFINICION DE LAS PRIMITIVAS DE ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;

    abb->cmp= cmp;
    abb->raiz = NULL;
    abb->destruir_dato= destruir_dato;
    abb->cantidad = 0;

    return abb;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

    nodo_t* nodo = nodo_crear(clave,dato);
    if (!nodo) return false;
    
    if(!arbol->raiz) {
        arbol->raiz = nodo;
        arbol->cantidad++;
        nodo->izq = NULL;
        nodo->der = NULL;
        return true;
    }else if (abb_pertenece(arbol, clave)){
        nodo_t* nodo_clave = abb_buscar(arbol->raiz,clave,arbol->cmp);
        if(arbol->destruir_dato) arbol->destruir_dato(nodo_clave->dato);
        nodo_clave->dato = dato;
        destruir_nodo(nodo);
        return true;
    }
    return _abb_guardar(arbol,arbol->raiz,nodo);
}


void *abb_borrar(abb_t *arbol, const char *clave){
    if (!arbol || !arbol->raiz) return NULL;
    nodo_t *nodo = abb_buscar(arbol->raiz,clave, arbol->cmp);
    if (!nodo) return NULL;
    if(!nodo->izq && !nodo->der) return borrar0(arbol,nodo);
    if(nodo->der && nodo->izq) return borrar2(arbol,nodo);
    return borrar1(arbol,nodo);
}

void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_t *nodo = abb_buscar(arbol->raiz,clave,arbol->cmp);
    return nodo?nodo->dato:NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    return abb_buscar(arbol->raiz,clave,arbol->cmp);
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}

void abb_destruir_(abb_t *arbol, nodo_t *raiz){
    if (!raiz) return;
    abb_destruir_ (arbol, raiz->izq);
    abb_destruir_ (arbol, raiz->der);
    void *aux = (destruir_nodo(raiz));
    if (arbol->destruir_dato) arbol->destruir_dato(aux);
}

void abb_destruir(abb_t *arbol){
    abb_destruir_(arbol, arbol->raiz);
    free(arbol);
}


/* ******************************************************************
 *               DEFINICION DE PRIMITIVAS DE ITERADOR INTERNO
 * *****************************************************************/

bool abb_in_order_(nodo_t* nodo, bool visitar(const char *, void *, void *), void *extra){
    
    if (!nodo) return true;
    if(!abb_in_order_(nodo->izq,visitar,extra)) return false;
	if (!visitar(nodo->clave,nodo->dato,extra))return false;
	if(!abb_in_order_(nodo->der,visitar,extra)) return false;
    return true;
	
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){ 
    if(!arbol->raiz) return;
    abb_in_order_(arbol->raiz,visitar, extra);
}

/* ******************************************************************
 *               DEFINICION DE PRIMITIVAS DE ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;
    iter->pila = pila_crear();
    if(!iter->pila){
        free(iter);
        return NULL;
    }
    nodo_t* actual = arbol->raiz;
    while (actual){
        pila_apilar(iter->pila,actual);
        actual = actual->izq;
    }
    iter->abb = arbol;
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

    if (abb_iter_in_al_final(iter)) return false;
    
    nodo_t* desapilado = pila_desapilar(iter->pila);
    if(!desapilado) return false;
    if (desapilado->der){
        pila_apilar(iter->pila,desapilado->der);
        nodo_t* actual = desapilado->der->izq;
        while(actual != NULL){
            pila_apilar(iter->pila,actual);
            actual = actual->izq;
        }
    }
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return NULL;
    nodo_t* tope = pila_ver_tope(iter->pila);
    return tope->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}