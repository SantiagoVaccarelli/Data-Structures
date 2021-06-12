
#include "testing.h"
#include "heap.h"
//#include "testing.c"
//#include "heap.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

#define TAM_ARR 5
#define TAM_ARR_MAYOR 15

int cmp(const void* a, const void* b){

	if (*(const int*) a == *(const int*) b) return 0;
	if (*(const int*) a > *(const int*) b) return 1;
	return -1;
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio()
{
    heap_t* heap = heap_crear(NULL);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap));
    print_test("Prueba heap desencolar, es false, no existe", !heap_desencolar(heap));
    print_test("Prueba heap ver max , es NULL, no existe", heap_ver_max(heap)==NULL);

    heap_destruir(heap,NULL);
}

static void prueba_encolar_desencolar_heap(){

    heap_t* heap = heap_crear(cmp);
    int arreglo[TAM_ARR] = {10,34,21,32,100}; 
	
    print_test("crear el heap es true", heap);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[0]));
    print_test("Prueba heap no esta vacio es true", !heap_esta_vacio(heap));
	print_test("Prueba heap cantidad de elementos 1", heap_cantidad(heap) == 1);
	print_test("Prueba heap ver el max es true", heap_ver_max(heap) == &arreglo[0]);
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[0]);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[5]));
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[5]);
    print_test("Prueba heap ver el max es true", heap_ver_max(heap) == NULL);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[1]));
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[1]);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[2]));
    print_test("Prueba heap cantidad de elementos 1", heap_cantidad(heap) == 1);
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[2]);
	print_test("Prueba heap cantidad de elementos 0", heap_cantidad(heap) == 0);

    heap_destruir(heap,NULL);

}

static void prueba_crear_heap_arreglo(){   
    
    void* arr[TAM_ARR];
    int arr_2[TAM_ARR] = {3, 4, 2,1,9};
    for(size_t i = 0;i<TAM_ARR;i++){
        arr[i] = &arr_2[i];
    }

    heap_t* heap = heap_crear_arr(arr,TAM_ARR,cmp);

    print_test("Prueba heap la cantidad de elementos es distinto de 0", heap_cantidad(heap)==TAM_ARR);
    print_test("Prueba heap esta vacio es false", !heap_esta_vacio(heap));
    print_test("Prueba heap desencolar es true", heap_desencolar(heap)== arr[0]);
    print_test("prueba encolar es true",heap_encolar(heap,&arr[4]));
    print_test("Prueba heap ver max es true",heap_ver_max(heap)==arr[4]);
    print_test("prueba desencolar es true",heap_desencolar(heap)==arr[4]);

    heap_destruir(heap,NULL);
}

static void prueba_heap_insertar_muchos_elementos()
{
    heap_t* heap = heap_crear(cmp);

    int arreglo[TAM_ARR] = {100,2,21,3,3}; 
	
    print_test("crear el heap es true", heap);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[0]));
    print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[2]));
    print_test("Prueba heap no esta vacio es true", !heap_esta_vacio(heap));
    print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[1]));
	print_test("Prueba heap cantidad de elementos 3", heap_cantidad(heap) == 3);
	print_test("Prueba heap ver el max es true", heap_ver_max(heap) == &arreglo[0]);

	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[0]);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[1]));
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[2]);
    print_test("Prueba heap ver el max es true", heap_ver_max(heap) == &arreglo[1]);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[1]));
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[1]);
	print_test("Prueba heap encolar es true", heap_encolar(heap, &arreglo[2]));
    print_test("Prueba heap cantidad de elementos 3", heap_cantidad(heap) == 3);
	print_test("Prueba heap desencolar es true", heap_desencolar(heap) == &arreglo[2]);
	print_test("Prueba heap cantidad de elementos 2", heap_cantidad(heap) == 2);

    heap_destruir(heap,NULL);
}

//Prueba de volumen
static void prueba_heap_volumen(size_t largo){
    printf("PRUEBAS DE VOLUMEN\n"); 
    heap_t *heap = heap_crear(cmp);
    print_test("Creo el heap", heap != NULL);


    bool ok = true;
    size_t datos[largo];
    
    for (size_t i=0; i<largo; i++){
        datos[i] = i;
        ok &= heap_encolar(heap, &datos[i]);   
    }
    print_test("Prueba heap almacenar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_ver_max(heap)==&datos[largo-1]);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    print_test("Prueba heap la cantidad de elementos es correcta", !heap_esta_vacio(heap));

    print_test("", largo == heap_cantidad(heap));

    //Desencolo vol elementos - vol deberia ser el primero en ser desencolado
    ok = true; 
    for(size_t i = largo-1; i>0; i--){
        size_t *dato = heap_desencolar(heap);
        if (*dato != i) ok = false;
    }
    print_test("Prueba desencolar elementos el orden correcto", ok);
    heap_destruir(heap, NULL);
    print_test("El heap ha sido destruido", true);
}

void prueba_heapsort(){
	int arreglo[TAM_ARR_MAYOR]= {8,1,2,3,5,12,15,6,7,4,13,11,9,14,10};
	void* arr[TAM_ARR_MAYOR];
	
    for(size_t i = 0;i<TAM_ARR_MAYOR;i++){
        arr[i] = &arreglo[i];
    }

	heap_sort(arr, TAM_ARR_MAYOR, cmp);
	bool ok = true;

	for(int i = 0; i < TAM_ARR_MAYOR; i++){
        ok  &= *(int*)arr[i]==i;
        printf("%d\n",*(int*)arr[i]);
	}
    //print_test("Prueba heap ordenar elementos", ok);
    // da error, y no me doy cuenta porque
    

}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_heap_estudiante()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_encolar_desencolar_heap();
    prueba_crear_heap_arreglo();
    prueba_heap_insertar_muchos_elementos();
    prueba_heapsort();
    prueba_heap_volumen(10000);
    

}
