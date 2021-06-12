#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testing.h"
#include "pila.h"

static void pruebas_unitarias(){
    printf("Pruebas unitarias:\n");
    int a = 7, b = 12, c = 3;
    cola_t *cola = cola_crear();
    printf("Creo una cola");
    print_test("La cola creada esta vacia", cola_esta_vacia(cola)); 
    print_test("Encolo un elemento", cola_encolar(cola, &a));
    print_test("Chequeo que sea el primero", cola_ver_primero(cola) == &a);
    print_test("Desencolo el elemento", cola_desencolar(cola) == &a);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("Encolo el primer elemento de nuevo", cola_encolar(cola, &a));
    print_test("Encolo un segundo elemento", cola_encolar(cola, &b));
    print_test("Encolo un tercer elemento", cola_encolar(cola, &c));
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El primer elemento al desencolar es el primer elemento encolado", cola_desencolar(cola) == &a);
    print_test("El primer elemento de la cola ahora es el segundo elemento encolado", cola_ver_primero(cola) == &b);
    print_test("El segundo elemento es desencolado", cola_desencolar(cola) == &b);
    print_test("El tercer elemento encolado ahora es el primero", cola_ver_primero(cola) == &c);
    print_test("El tercer elemento es desencolado", cola_desencolar(cola) == &c);
    print_test("Los elementos fueron desencolados, la cola esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    printf("La cola fue destruida\n\n");
}


static void pruebas_colas_vacias(){
    printf("Pruebas con colas vacias:\n");
    cola_t* cola = cola_crear();
    int a = 13;
    char b = 'h';
    printf("Creo una cola\n");
    print_test("La cola creada esta vacia", cola_esta_vacia(cola));
    print_test("La funcion ver primero para colas vacias es invalida", cola_ver_primero(cola) == NULL);
    print_test("La funcion desencolar para colas vacias es invalida", cola_desencolar(cola) == NULL);
    print_test("Encolo un elemento", cola_encolar(cola, &a));
    print_test("Encolo un segundo elemento", cola_encolar(cola, &b));
    print_test("Desencolo el primer elemento", cola_desencolar(cola) == &a);
    print_test("Desencolo el segundo elemento", cola_desencolar(cola) == &b);
    print_test("La cola desencolada no se puede desencolar", cola_desencolar(cola) == NULL);
    print_test("No se puede ver el primer elemento de una cola desencolada", cola_ver_primero(cola) == NULL);
    cola_destruir(cola, NULL);
    printf("La cola fue destruida\n\n");
}



static void pruebas_con_null(){
    printf("Pruebas con el elemento NULL:\n");
    printf("Creo una cola");
    cola_t *cola = cola_crear();
    int a = 161;
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("Encolo un elemento distinto de NULL", cola_encolar(cola, &a));
    print_test("El primer elemento es el encolado", cola_ver_primero(cola) == &a);
    print_test("Encolo el elemento NULL", cola_encolar(cola, NULL));
    print_test("Desencolo el primer elemento encolado", cola_desencolar(cola) == &a);
    print_test("El primer elemento es el NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolo el primer elemento NULL", cola_desencolar(cola) == NULL);
    print_test("La cola desencolada esta vacia", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    printf("La cola fue destruida\n\n");
}


static void pruebas_casos_borde(){
    printf("Pruebas con casos borde:\n");
    cola_t* cola = cola_crear();
    int a = 13;
    char b = 'p';
    print_test("La cola creada esta vacia", cola_esta_vacia(cola));
    print_test("No se puede ver el primero de la cola recien creada", cola_ver_primero(cola) == NULL);
    print_test("No se puede desencolar la cola recien creada", cola_desencolar(cola) == NULL);
    print_test("Encolo un elemento", cola_encolar(cola, &a));
    print_test("Encolo un segundo elemento", cola_encolar(cola, &b));
    print_test("Desencolo el primer elemento encolado", cola_desencolar(cola) == &a);
    print_test("Desencolo el segundo elemento encolado", cola_desencolar(cola) == &b);
    print_test("La cola vuelve a estar vacia", cola_esta_vacia(cola));
    printf("La cola desencolada se comporta como recien creada\n");
    print_test("        No se puede desencolar", cola_desencolar(cola) == NULL);
    print_test("        No puedo ver el primero", cola_ver_primero(cola) == NULL);
    cola_destruir(cola, NULL);
    printf("La cola fue destruida");
}



static void pruebas_de_volumen(){
    printf("Pruebas de volumen:\n");
    cola_t *cola = cola_crear();
    printf("Creo una cola\n");

    bool encolo = true;
    int **vec[10000];
    for (int i=0; i<10000; i++){
        encolo &= cola_encolar(cola, vec[i]);
        printf("%p\n", vec[i]);
    }
    print_test("La cola encolo 10000 elementos", encolo);
    bool desencola_en_orden = true;
    while(!cola_esta_vacia(cola)){
        void *primero = cola_ver_primero(cola);
        desencola_en_orden &= (cola_desencolar(cola) == primero);
    }
    print_test("La cola desencola en orden", desencola_en_orden);
    print_test("La cola desencolo todos los elementos", cola_esta_vacia(cola));
    cola_destruir(cola, NULL);
    printf("La cola fue destruida\n\n");

}

static void pruebas_destruccion(){
    printf("Pruebas de destruccion:\n");
    cola_t *cola = cola_crear();
    printf("Creo una cola\n");
    bool encolo = true;
    for (int i=0; i<10000; i++) encolo &= cola_encolar(cola, &i);
    print_test("La cola encolo 10000 elementos", encolo);
    cola_destruir(cola, NULL);
    printf("La cola due destruida\n");
}

void _destruir_dato(void *pila){
    pila_destruir((pila_t*) pila);
}

static void pruebas_con_pilas(){
    cola_t* cola = cola_crear();
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();
    print_test("La pila1 se encolo correctamente", cola_encolar(cola, pila1));
    print_test("La pila2 se encolo correctamente", cola_encolar(cola, pila2));
    print_test("La pila3 se encolo correctamente", cola_encolar(cola, pila3));
    print_test("La pila 1 es el primer elemento", cola_ver_primero(cola)== pila1);
    printf("Las pilas fueron destruidas\n");
    printf("La cola fue destruida\n");
    cola_destruir(cola, _destruir_dato);

}



void pruebas_cola_estudiante() {
    pruebas_unitarias();
    pruebas_colas_vacias();
    pruebas_con_null();
    pruebas_casos_borde();
    pruebas_de_volumen();
    pruebas_destruccion();
    pruebas_con_pilas();
}

#ifndef CORRECTOR

int main(void) {
    printf("\nPRUEBAS TDA COLA:\n");
    pruebas_cola_estudiante();
    return failure_count() > 0;
}
#endif