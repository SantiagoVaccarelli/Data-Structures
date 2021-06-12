#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testing.h"
#include "cola.h"
#include "pila.h"

void pruebas_unitarias(){
    printf("PRUEBAS UNITARIAS\n\n");
    lista_t *lista = lista_crear();
    int a = 5, b = 23, c = 42;
    printf("La lista fue creada\n");
    print_test("La lista creada esta vacia", lista_esta_vacia(lista));
    print_test("Eliminar el primer elemento en una lista vacia es invalido", !lista_borrar_primero(lista));
    print_test("Insertar un elemento al inicio lista", lista_insertar_primero(lista, &a));
    print_test("El primer elemento de la lista es el insertado", lista_ver_primero(lista) == &a);
    print_test("La lista tiene un elemento", lista_largo(lista) == 1);
    print_test("Insertar un elemento al final de la lista", lista_insertar_ultimo(lista, &b));
    print_test("El elemento insertado es el ultimo de la lista", lista_ver_ultimo(lista) == &b);
    print_test("La lista tiene dos elementos", lista_largo(lista) == 2);
    print_test("Insertar otro elemento al inicio de la lista", lista_insertar_primero(lista, &c));
    print_test("El primer elemento de la lista es el ultimo insertado", lista_ver_primero(lista) == &c);
    print_test("La lista tiene tres elementos", lista_largo(lista) == 3);
    print_test("El ultimo elemento insertado es eliminado", lista_borrar_primero(lista) == &c);
    print_test("La lista tiene dos elementos nuevamente", lista_largo(lista) == 2);
    print_test("El primer elemento insertado vuelve a ser el primero de la lista", lista_ver_primero(lista) == &a);
    print_test("El primer elemento insertado es eliminado", lista_borrar_primero(lista) == &a);
    print_test("La lista tiene un elemento nuevamente", lista_largo(lista) == 1);
    print_test("El elemento restante es tambien el primer elemento de la lista", lista_ver_primero(lista) == &b);
    print_test("El elemento restante es eliminado", lista_borrar_primero(lista) == &b);
    print_test("La lista esta nuevamente vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

void pruebas_listas_vacias(){
    printf("PRUEBAS CON LISTAS VACIAS\n\n");
    lista_t *lista = lista_crear();
    printf("La lista fue creada\n");
    int a = 51;
    char b = 'k';
    print_test("La lista creada esta vacia", lista_esta_vacia(lista));
    print_test("El largo de la lista es cero", lista_largo(lista) == 0);
    print_test("Eliminar un elemento de una lista vacia es invalido", !lista_borrar_primero(lista));
    print_test("Insertar un elemento al inicio de la lista", lista_insertar_primero(lista, &a));
    print_test("Insertar un segundo elemento al inicio de la lista", lista_insertar_primero(lista, &b));
    print_test("El largo de la lista es dos", lista_largo(lista) == 2);
    print_test("Eliminar el primer elemento de la lista", lista_borrar_primero(lista) == &b);
    print_test("Eliminar el elemento restante de la lista", lista_borrar_primero(lista) == &a);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("El largo de la lista es nuevamente cero", lista_largo(lista) == 0);
    print_test("Eliminar un elemento de la lista es invalido", !lista_borrar_primero(lista));
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

void pruebas_con_null(){
    printf("PRUEBAS CON EL ELEMENTO NULL\n\n");
    lista_t *lista = lista_crear();
    int a = 43;
    print_test("La lista creada esta vacia", lista_esta_vacia(lista));
    print_test("Un elemento distinto de NULL es insertado", lista_insertar_primero(lista, &a));
    print_test("El primer y ultimo elemento de la lista es el insertado", lista_ver_primero(lista) == &a && lista_ver_ultimo(lista) == &a);
    print_test("El elemento NULL es insertado", lista_insertar_primero(lista, NULL));
    print_test("El largo de la lista es dos", lista_largo(lista) == 2);
    print_test("El elemento NULL es el primero de la lista", !lista_ver_primero(lista));
    print_test("El elemento distinto de NULL sigue siendo el ultimo de la lista",lista_ver_ultimo(lista) == &a);
    print_test("El elemento NULL es eliminado", !lista_borrar_primero(lista));
    print_test("El elemento distinto de NULL es eliminado", lista_borrar_primero(lista) == &a);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

void pruebas_casos_borde(){
    printf("PRUEBAS CASOS BORDE\n\n");
    lista_t *lista = lista_crear();
    int a = 17;
    char b = 'u';
    printf("La lista fue creada\n");
    print_test("La lista creada esta vacia", lista_esta_vacia(lista));
    print_test("Eliminar un elemento de una lista vacia es invalido", !lista_borrar_primero(lista));
    print_test("Ver el primer elemento de una lsita vacia es invalido", !lista_ver_primero(lista));
    print_test("Inserto un elemento al inicio de la lista", lista_insertar_primero(lista, &a));
    print_test("El largo de la lista es uno", lista_largo(lista) == 1);
    print_test("Inserto un elemento al final de la lista", lista_insertar_ultimo(lista, &b));
    print_test("El largo de la lista es dos", lista_largo(lista) == 2);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Eliminar el primer elemento de la lista", lista_borrar_primero(lista) == &a);
    print_test("Eliminar el elemento restante de la lista", lista_borrar_primero(lista) == &b);
    printf("La lista se comporta como recien creada:\n");
    print_test("    La lista esta vacia", lista_esta_vacia(lista));
    print_test("    El largo de la lista es nuevamente cero", lista_largo(lista) == 0);
    print_test("    Eliminar un elemento de la lista es invalido", !lista_borrar_primero(lista));
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

void pruebas_de_volumen(){
    // Para que no apile siempre el mismo puntero creo un vector de punteros e inserto los elementos del mismo
    printf("PRUEBAS DE VOLUMEN\n\n");
    lista_t *lista = lista_crear();
    printf("La lista fue creada\n");
    bool inserta = true;
    int **punteros[10000];
    for (int i=0; i<10000; i++) inserta &= lista_insertar_primero(lista, punteros[i]);
    print_test("La lista inserto 10000 elementos", inserta);
    print_test("El largo de la lista es de 10000", lista_largo(lista) == 10000);
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

//FUNCIONES WRAPPER PARA DESTRUIR LISTAS CON PILAS O COLAS CONTENIDAS

void destruir_lista_pila(void *pila){
    pila_destruir((pila_t*) pila);
}

void destruir_lista_cola(void* cola){
    cola_destruir((cola_t*) cola, NULL);
}

void pruebas_pilas_colas(){
    printf("PRUEBAS CON PILAS Y COLAS\n\n");
    pila_t *pila1 = pila_crear();
    pila_t *pila2 = pila_crear();
    printf("Las pilas para las pruebas fueron creadas\n");
    cola_t *cola1 = cola_crear();
    cola_t *cola2 = cola_crear();
    printf("Las colas para las pruebas fueron creadas\n");
    lista_t *lista1 = lista_crear();
    lista_t *lista2 = lista_crear();
    printf("Las listas para las pruebas fueron creadas\n\n");
    print_test("La primer lista esta vacia", lista_esta_vacia(lista1));
    print_test("Insertar la primer pila", lista_insertar_primero(lista1, pila1));
    print_test("El largo de la lista es uno", lista_largo(lista1) == 1);
    print_test("El primer elemento de la lista es la primer pila", lista_ver_primero(lista1) == pila1);
    print_test("Insertar la segunda pila", lista_insertar_primero(lista1, pila2));
    print_test("La segunda pila insertada es el primer elemento", lista_ver_primero(lista1) == pila2);
    print_test("El largo de la lista es dos", lista_largo(lista1) == 2);
    lista_destruir(lista1, destruir_lista_pila);
    printf("La primer lista fue destruida con las pilas adentro\n");
    print_test("La segunda lista esta vacia", lista_esta_vacia(lista2));
    print_test("Insertar la primer cola", lista_insertar_primero(lista2, cola1));
    print_test("El largo de la lista es uno", lista_largo(lista2) == 1);
    print_test("El primer elemento de la lista es la primer cola", lista_ver_primero(lista2) == cola1);
    print_test("Insertar la segunda cola", lista_insertar_primero(lista2, cola2));
    print_test("La segunda cola insertada es el primer elemento", lista_ver_primero(lista2) == cola2);
    print_test("El largo de la lista es dos", lista_largo(lista2) == 2);
    lista_destruir(lista2, destruir_lista_cola);
    printf("La segunda lista fue destruida con las colas adentro\n\n");
}

void pruebas_de_destruccion(){
    printf("PRUEBAS DE DESTRUCCION\n\n");
    lista_t *lista = lista_crear();
    printf("La lista fue creada\n");
    lista_destruir(lista, NULL);
    printf("La lista vacia fue destruida con funcion de destruccion NULL\n");
    int a = 1561, b = 21451;
    lista_t *lista2 = lista_crear();
    printf("La segunda lista fue creada\n");
    printf("La lista vacia fue destruida con funcion de destruccion distinta de NULL\n");
    lista_destruir(lista2, destruir_lista_cola);
    lista_t *lista3 = lista_crear();
    printf("La tercer lista fue creada\n");
    pila_t *pila1 = pila_crear();
    pila_t *pila2 = pila_crear();
    printf("Las pilas para las pruebas fueron creadas\n");
    print_test("Insertar dos pilas a la lista", lista_insertar_primero(lista3, pila1) && lista_insertar_primero(lista3, pila2));
    lista_destruir(lista3, destruir_lista_pila);
    printf("La lista no vacia fue destruida con funcion de destruccion distinta de NULL\n");
    lista_t *lista4 = lista_crear();
    printf("La cuarta lista fue creada\n");
    print_test("Insertar dos elementos a la lista", lista_insertar_primero(lista4, &a) && lista_insertar_primero(lista4, &b));
    lista_destruir(lista4, NULL);
    printf("La lista no vacia fue destruida con funcion de destruccion NULL\n\n");
}

void pruebas_de_iterador_externo(){
    printf("PRUEBAS DE ITERADOR EXTERNO\n\n");
    lista_t *lista = lista_crear();
    printf("La lista fue creada\n");
    lista_iter_t *iter = lista_iter_crear(lista);
    printf("El iterador fue creado\n");
    int a = 91, c = 1123, d = 2451;
    char b = 'e', e = 'h';
    print_test("Insertar un elemento con el iterador en una lista vacia", lista_iter_insertar(iter, &a));
    print_test("El elemento insertado es el primer elemento de la lista", lista_ver_primero(lista) == &a);
    print_test("El elemento insertado es tambien el ultimo elemento de la lista", lista_ver_ultimo(lista) == &a);
    print_test("El largo de la lista es uno", lista_largo(lista) == 1);
    print_test("El actual es el elemento insertado", lista_iter_ver_actual(iter) == &a);
    print_test("El iterador avanzo una posicion", lista_iter_avanzar(iter));
    print_test("El iterador esta al final de la lista", lista_iter_al_final(iter));
    print_test("Insertar un elemento con el iterador cuando el iterador esta al final", lista_iter_insertar(iter, &b));
    print_test("El elemento insertado es el ultimo", lista_ver_ultimo(lista) == &b);
    print_test("El largo de la lista es dos", lista_largo(lista) == 2);
    print_test("Borrar el ultimo elemento de la lsita con el iterador", lista_iter_borrar(iter));
    print_test("El ultimo elemento de la lista es ahora el primero insertado", lista_ver_ultimo(lista) == &a);
    lista_iter_destruir(iter);
    print_test("Insertar un elemento al final de la lista", lista_insertar_ultimo(lista, &c));
    print_test("Insertar otro elemento al final de la lista", lista_insertar_ultimo(lista, &d));
    lista_iter_t *iter2 = lista_iter_crear(lista);
    print_test("El primer elemento de la lista es el primero insertado", lista_ver_primero(lista) == &a);
    print_test("Borrar un elemento cuando se crea el iterador", lista_iter_borrar(iter2) == &a);
    print_test("El primer elemento de la lista es ahora el tercer elemento insertado", lista_ver_primero(lista) == &c);
    print_test("Insertar un elemento con el iterador en el medio de la lista", lista_iter_insertar(iter2, &e));
    printf("Avanzo el iterador hasta el final de la lista\n");
    while(!lista_iter_al_final(iter2)) lista_iter_avanzar(iter2);
    print_test("El iterador esta al final", lista_iter_al_final(iter2));
    print_test("Borrar un elemento con la lista ya recorrida es invalido", !lista_iter_borrar(iter2));
    lista_iter_destruir(iter2);
    printf("El iterador fue destruido\n");
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

//FUNCIONES PARA PASAR POR PARAMETRO A LA FUNCION LISTA_ITERAR

bool sumar_elementos_lista(void* dato, void* extra){
    if (!dato) return false;
    *(int*) extra += *(int*) dato;
    return true;
}

bool imprimir_primeros_tres(void* dato, void* extra){
    if (*(size_t*) extra >= 3) return false;
    (*(size_t*) extra)++;
    printf("%i\n", (*(int*)dato));
    return true;
}

bool imprimir_menores_que_cien(void* dato, void* extra){
    if (*(int*)dato >99) return false;
    printf("%i\n", (*(int*)dato));
    return true;
}

void pruebas_de_iterador_interno(){
    printf("PRUEBAS DE ITERADOR INTERNO\n\n");
    lista_t *lista = lista_crear();
    printf("La lista fue creada\n");
    int a = 2, b = 53, c = 123, d = 91;
    int suma = a+b+c+d, suma2 = 0;
    size_t cont = 0;
    print_test("Insertar el primer elemento a la lista", lista_insertar_primero(lista, &a));
    print_test("Insertar el segundo elemento a la lista", lista_insertar_primero(lista, &b));
    print_test("Insertar el tercer elemento a la lista", lista_insertar_primero(lista, &c));
    print_test("Insertar el cuarto elemento a la lista", lista_insertar_primero(lista, &d));
    lista_iterar(lista, sumar_elementos_lista, &suma2);
    print_test("El iterador sumo todos los elementos correctamente", suma == suma2);
    lista_iterar(lista, imprimir_primeros_tres, &cont);
    printf("Los primero tres elementos de la lista fueron impresos\n\n");
    lista_iterar(lista, imprimir_menores_que_cien, NULL);
    printf("Los numero hasta el primero mayor que cien fueron impresos\n\n");
    lista_destruir(lista, NULL);
    printf("La lista fue destruida\n\n");
}

void pruebas_lista_estudiante() {
    pruebas_unitarias();
    pruebas_listas_vacias();
    pruebas_con_null();
    pruebas_casos_borde();
    pruebas_de_volumen();
    pruebas_pilas_colas();
    pruebas_de_destruccion();
    pruebas_de_iterador_externo();
    pruebas_de_iterador_interno();  
}

#ifndef CORRECTOR

int main(void) {
    printf("\nPRUEBAS TDA LISTA\n\n");
    pruebas_lista_estudiante();
    printf("\nFIN DE PRUEBAS TDA LISTA\n\n");
    return failure_count() > 0;
}
#endif 