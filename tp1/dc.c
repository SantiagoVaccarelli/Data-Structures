#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "calc_helper.h"
#include "pila.h"
#include "strutil.h"

bool suma(pilanum_t *pila);
bool resta(pilanum_t *pila);
bool multiplicacion(pilanum_t *pila);
bool division(pilanum_t *pila);
bool potencia(pilanum_t *pila);
bool logaritmo(pilanum_t *pila);
bool raiz(pilanum_t *pila);
bool ternario(pilanum_t *pila);

void postfix(char *linea){
    char **caracteres = dc_split(linea);
    bool sin_errores = true;
    if (!caracteres) sin_errores = false;
    pilanum_t *numeros = pilanum_crear();
    int i = 0;
    for (i = 0; caracteres[i] && sin_errores;i++){
        struct calc_token token;
        calc_parse(caracteres[i], &token);
        if (token.type == TOK_NUM) apilar_num(numeros, token.value);
        else if (token.type == TOK_OPER){
            switch (token.oper.op){
                case OP_ADD:
                    sin_errores &= suma(numeros);
                    break;
                case OP_SUB:
                    sin_errores &= resta(numeros);
                    break;
                case OP_MUL:
                    sin_errores &= multiplicacion(numeros);
                    break;
                case OP_DIV:
                    sin_errores &= division(numeros);
                    break;
                case OP_POW:
                    sin_errores &= potencia(numeros);
                    break;
                case OP_LOG:
                    sin_errores &= logaritmo(numeros);
                    break;
                case OP_RAIZ:
                    sin_errores &= raiz(numeros);
                    break;
                case OP_TERN:
                    sin_errores &= ternario(numeros);
                    break;
                default:
                    break;
            }
        }
    }
    calc_num aux;
    sin_errores &= desapilar_num(numeros, &aux);
    if (!pila_esta_vacia(numeros)) sin_errores = false;
    if (sin_errores) printf("%ld\n", aux);
    else printf("ERROR\n");
    pilanum_destruir(numeros);
    free_strv(caracteres);
}


int main(){
    size_t capacidad = 0;
    char *linea = NULL;
    while ((getline(&linea, &capacidad, stdin) != -1)) postfix(linea);
    free(linea);
    return 0;
}


// FUNCIONES DE LAS OPERACIONES

bool suma(pilanum_t *pila){
    calc_num valor1, valor2;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    apilar_num(pila, valor1+valor2);
    return true;
}

bool resta(pilanum_t *pila){
    calc_num valor1, valor2;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    apilar_num(pila, valor2-valor1);
    return true;
}

bool multiplicacion(pilanum_t *pila){
    calc_num valor1, valor2;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    apilar_num(pila, valor1*valor2);
    return true;
}


bool division(pilanum_t *pila){
    calc_num valor1, valor2;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    if (valor1 == 0) return false;
    apilar_num(pila, valor2/valor1);
    return true;
}

bool potencia(pilanum_t *pila){
    calc_num valor1, valor2;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    if (valor1 < 0) return false;
    double resultado = pow((double)valor2, (double)valor1);
    apilar_num(pila, (calc_num)resultado);
    return true;
}


bool logaritmo(pilanum_t *pila){
    calc_num valor1, valor2;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    if (valor1 < 2) return false;
    double resultado = log10((double)valor2)/log10((double)valor1);
    apilar_num(pila,(calc_num)resultado);
    return true;
}

bool raiz(pilanum_t *pila){
    calc_num valor1;
    if (!desapilar_num(pila, &valor1)) return false;
    if (valor1 < 0) return false;
    double resultado = sqrt((double)valor1);
    apilar_num(pila,(calc_num)resultado);
    return true;
}
bool ternario(pilanum_t *pila){
    calc_num valor1, valor2, valor3;
    if (!desapilar_num(pila, &valor1)) return false;
    if (!desapilar_num(pila, &valor2)) return false;
    if (!desapilar_num(pila, &valor3)) return false;
    calc_num resultado = valor3? valor2:valor1;
    apilar_num(pila, resultado);
    return true;
}

