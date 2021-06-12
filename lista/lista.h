#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

// DECLARACION DE LOS TYPEDEF lista_t, nodo_t y lista_iter_t

struct nodo;
struct lista;
struct lista_iter;

typedef struct nodo nodo_t;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

// PRIMITIVAS DE LA LISTA 


// Crea una lista
// Post: Devuelve la lista creada o NULL si no pudo hacerlo
lista_t *lista_crear(void);

// Dice si la lista tiene elementos o no.
// Pre: la lista fue creada
// Post: Devuelve true si la lista esta vacia y false en caso contrario
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento al inicio de la lista
// Pre: la lista fue creada
// Post: se inserto un nodo con el dato al inicio de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta un elemento al final de la lista
// Pre: la lista fue creada
// Post: se inserto un nodo con el dato al final de la lista
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista
// Pre: la lista fue creada
/* Post: elimina el primer nodo y devuelve el dato contenido,
   si la lista esta vacia devuelve NULL */
void *lista_borrar_primero(lista_t *lista);

// Devuelve el dato contenido en el primer nodo
// Pre: la lista fue creada
/* Post: devuelve el valor contenido en el primer nodo, 
   si la lista esta vacia devuelve NULL. */
void *lista_ver_primero(const lista_t *lista);

// Devuelve el dato contenido en el ultimo nodo
// Pre: la lista fue creada
/* Post: devuelve el valor contenido en el ultimo nodo, 
   si la lista esta vacia devuelve NULL */
void *lista_ver_ultimo(const lista_t *lista);

// Devuelve el largo de la lista
// Pre: la lista fue creada
// Post: Devuelve la cantidad de elementos insertados
size_t lista_largo(const lista_t *lista);

// Destruye la lista
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));



// PRIMITIVAS DEL ITERADOR EXTERNO


// Obtiene un iterador de la lista
// Pre: la lista fue creada
// Post: se devuelve un nuevo iterador
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza una posición en la lista
// Pre: el iterador fue creado
// Post: se avanzó la posición actual en el iterador. Devuelve false si ya
// está al final de la lista
bool lista_iter_avanzar(lista_iter_t *iter);

// Almacena en dato el valor que se encuentra en la posición actual
// Pre: el iterador fue creado
// Post: se almacenó el dato actual en dato. Devuelve false si está al final
// de la lista
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Verifica si ya está al final de la lista
// Pre: el iterador fue creado
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador de la lista
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un elemento en la posición actual
// Pre: el iterador fue creado
// Post: se insertó un nuevo nodo antes de la posición actual, quedando este
// nuevo nodo como posición actual
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina el elemento de la posición actual
// Pre: el iterador fue creado
// Post: se eliminó el nodo que se encontraba en la posición actual indicada por el
// iterador. Devuelve NULL si el iterador está al final de la lista
void *lista_iter_borrar(lista_iter_t *iter);



// PRIMITIVAS DEL ITERADOR INTERNO
 
// Recorre la lista llamando para cada elemento la funcion visitar
// La funcion visitar es pasada por parametro al ogual que extra y la lista.
// Pre: la lista fue creada.
// Post: se llama a la funcion visitar para cada elemento de la lista
// Devuelve true si debe seguir iterando y false en caso contrario.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);


#endif