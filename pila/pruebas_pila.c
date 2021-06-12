#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pila.h"
#include "testing.h"



static void pruebas_unitarias(){
    printf("\nPruebas unitarias: \n");
    pila_t* pila = pila_crear();
    int a = 7;
    char b = 'p'; 
    size_t c = 302055;
    printf("Creo una pila\n");
    print_test("La pila creada esta vacia", pila_esta_vacia(pila));
    print_test("Apilo un elemento", pila_apilar(pila, &a)); 
    print_test("Chequeo que sea el tope", pila_ver_tope(pila) == &a);
    print_test("Lo desapilo ", pila_desapilar(pila) == &a);
    print_test("Apilo el primer elemento", pila_apilar(pila, &a));
    print_test("Chequeo que sea el tope", pila_ver_tope(pila) == &a);
    print_test("Apilo otro elemento", pila_apilar(pila, &b));
    print_test("Chequeo que sea el tope", pila_ver_tope(pila) == &b);
    print_test("Apilo un tercer elemento", pila_apilar(pila, &c));
    print_test("Chequeo que sea el tope", pila_ver_tope(pila) == &c);
    print_test("Desapilo el ultimo elemento apilado", pila_desapilar(pila) == &c);
    print_test("Nuevo tope es el segundo elemento apilado", pila_ver_tope(pila) == &b);
    print_test("Desapilo el segundo elemento apilado", pila_desapilar(pila) == &b);
    print_test("Nuevo tope es el primer elemento apilado", pila_ver_tope(pila) == &a);
    print_test("Desapilo el primer elemento apilado", pila_desapilar(pila) == &a);
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
    printf("La pila fue destruida\n\n");
}


static void pruebas_pilas_vacias(){
    printf("Pruebas con pilas vacias:\n");
    pila_t* pila = pila_crear();
    int a = 13, b = 2;
    printf("Creo una pila\n");
    print_test("La pila creada esta vacia", pila_esta_vacia(pila));
    print_test("La funcion ver tope para pilas vacias es invalida", pila_ver_tope(pila) == NULL);
    print_test("La funcion desapilar para pilas vacias es invalida", pila_desapilar(pila) == NULL);
    print_test("Apilo un elemento", pila_apilar(pila, &a));
    print_test("Apilo un segundo elemento", pila_apilar(pila, &b));
    print_test("Desapilo el ulitmo elemento apilado", pila_desapilar(pila) == &b);
    print_test("Desapilo el primer elemento apilado", pila_desapilar(pila) == &a);
    print_test("La pila desapilada no se puede desapilar", pila_desapilar(pila) == NULL);
    print_test("La no se puede ver tope de una pila desapilada", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
    printf("La pila fue destruida\n\n");
}


static void pruebas_con_null(){
    printf("Pruebas con el elemento NULL:\n");
    pila_t* pila = pila_crear();
    int a = 19;
    printf("Creo una pila\n");
    print_test("La pila creada esta vacia", pila_esta_vacia(pila));
    print_test("Apilo un elemento distinto de NULL", pila_apilar(pila, &a));
    print_test("El tope es el elemento apilado", pila_ver_tope(pila) == &a);
    //Apilo un elemento antes de apilar NULL para comprobar despues que al apilar NULL el nuevo tope es NULL
    print_test("Apilo el elemento NULL", pila_apilar(pila, NULL));
    print_test("Compruebo que el tope sea NULL", pila_ver_tope(pila) == NULL);
    print_test("Desapilo el elemento NULL ", pila_desapilar(pila) == NULL);
    print_test("Desapilo el primer elemento apilado", pila_desapilar(pila) == &a);
    print_test("La pila desapilada esta vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
    printf("La pila fue destruida\n\n");
}


static void pruebas_casos_borde(){
    printf("Pruebas con casos borde:\n");
    pila_t* pila = pila_crear();
    int a = 7;
    char b = 'a';
    printf("Creo una pila\n");
    print_test("La pila recien creada esta vacia", pila_esta_vacia(pila));
    print_test("No puedo desapilar una poila recien creada", pila_desapilar(pila) == NULL);
    print_test("No puedo ver tope en una pila recien creda", pila_ver_tope(pila) == NULL);
    print_test("Apilo un elemento", pila_apilar(pila, &a));
    print_test("Apilo un segundo elemento", pila_apilar(pila, &b));
    print_test("Desapilo el ulitmo elemento apilado", pila_desapilar(pila) == &b);
    print_test("Desapilo el primer elemento apilado", pila_desapilar(pila) == &a);
    print_test("La pila desapilada no se puede desapilar", pila_desapilar(pila) == NULL);
    print_test("La no se puede ver tope de una pila desapilada", pila_ver_tope(pila) == NULL);
    printf("La pila desapilada se comporta como recien creada:\n");
    print_test("        La pila no se puede desapilar", pila_desapilar(pila) == NULL);
    print_test("        No se puede ver tope de la lista desapilada", pila_ver_tope(pila) == NULL);
    pila_destruir(pila);
    printf("La pila fue destruida\n\n");


}

static void pruebas_de_volumen(){
    printf("Pruebas de volumen:\n");
    pila_t *pila = pila_crear();
    printf("Creo una pila\n");
    bool apilo = true;
    for (int i=0; i<10000; i++) apilo &= pila_apilar(pila, &i);
    print_test("La pila apiló 10000 elementos", apilo);
    bool desapila_en_orden = true;
    while(!(pila_esta_vacia(pila))){
        void *tope = pila_ver_tope(pila);
        desapila_en_orden &= (pila_desapilar(pila) == tope);
    }
    print_test("El desapilado respeta el orden", desapila_en_orden);
    print_test("La pila desapilo los elementos correctamente", pila_esta_vacia(pila));
    pila_destruir(pila);
    printf("La pila fue destruida\n\n");
  
}

static void pruebas_con_cadenas(){
    printf("Pruebas con cadenas:\n");
    pila_t *pila = pila_crear();
    printf("Creo una pila\n");
    char cadena[15] = "Hola ¿como va?";
    bool apila_bien_cadenas = true;
    for (int i = 0; cadena[i] != '\0'; i++) apila_bien_cadenas &= pila_apilar(pila, &cadena[i]);
    print_test("Apilo bien los elementos de la cadena", apila_bien_cadenas);
    bool desapila_bien_cadenas = true;
    int i = 0;
    while (!pila_esta_vacia(pila)) {
        desapila_bien_cadenas &= pila_desapilar(pila) == &cadena[15-1-i];
        i++;
    }
    print_test("Desapilo bien los elementos de la cadena", desapila_bien_cadenas);
    pila_destruir(pila);
    printf("La pila fue destruida\n\n");
}


void pruebas_pila_estudiante() {
    pruebas_unitarias();
    pruebas_pilas_vacias();
    pruebas_con_null();
    pruebas_casos_borde();
    pruebas_de_volumen();
    pruebas_con_cadenas();
}

#ifndef CORRECTOR

int main(void) {
    printf("\nPRUEBAS TDA PILA:\n");
    pruebas_pila_estudiante();
    return failure_count() > 0;
}

#endif 
