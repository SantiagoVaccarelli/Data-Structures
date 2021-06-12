#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "pila.h"
#include "calc_helper.h"
#include "cola.h"
#include "strutil.h"

void imprimir_postfix(cola_t *cola, bool imprimir){
    if (cola_esta_vacia(cola)) imprimir = false;
    if(imprimir){
        while(!cola_esta_vacia(cola)){
            struct calc_token *aux = cola_ver_primero(cola);
            if (aux->type == TOK_NUM) printf("%ld ", aux->value);
            else if(aux->type == TOK_OPER){
                switch (aux->oper.op){
                    case OP_ADD:
                        printf("+ ");
                        break;
                    case OP_SUB:
                        printf("- ");
                        break;
                    case OP_MUL:
                        printf("* ");
                        break;
                    case OP_DIV:
                        printf("/ ");
                        break;
                    case OP_POW:
                        printf("^ ");
                        break;
                    default:
                        break;
                }
            }
            cola_desencolar(cola);
            free(aux);
        }
    }
    else printf("ERROR");
    printf("\n"); 
}

void infix_to_postfix(char *linea){
    bool sin_errores = true;
    char **caracteres = infix_split(linea);
    sin_errores &= (caracteres != NULL);
    pila_t *operadores = pila_crear();
    sin_errores &= (operadores != NULL);
    cola_t *postfix = cola_crear();
    sin_errores &= (postfix != NULL);
    for (int i = 0; caracteres[i] && sin_errores;i++){
        struct calc_token *token = malloc(sizeof(struct calc_token));
        if (!token) sin_errores = false;
        sin_errores &= calc_parse(caracteres[i], token);
        if (token->type == TOK_NUM) cola_encolar(postfix,token); 
        else if (token->type == TOK_LPAREN) pila_apilar(operadores, token);
        else if (token->type == TOK_RPAREN){
            struct calc_token *token2 = pila_ver_tope(operadores);
            while (token2->type != TOK_LPAREN){
                cola_encolar(postfix,pila_desapilar(operadores));     
                token2 = pila_ver_tope(operadores);    
            } 
            free(pila_desapilar(operadores));
            free(token);
        }
        else if (token->type == TOK_OPER){
            struct calc_token* token2 = pila_ver_tope(operadores);
            while((!pila_esta_vacia(operadores)) && (token2->type == TOK_OPER) && 
            ((token->oper.asociatividad == ASSOC_LEFT && token->oper.precedencia <= token2->oper.precedencia) || 
            (token->oper.asociatividad == ASSOC_RIGHT && token->oper.precedencia < token2->oper.precedencia))){
                cola_encolar(postfix, pila_desapilar(operadores));
                token2 = pila_ver_tope(operadores);
            }
            pila_apilar(operadores, token);
        }
    }
    while(!pila_esta_vacia(operadores)){
        if (!cola_encolar(postfix, pila_desapilar(operadores))) sin_errores = false;
    }
    imprimir_postfix(postfix, sin_errores);
    cola_destruir(postfix, NULL);
    pila_destruir(operadores);
    free_strv(caracteres);
}

int main(){
    size_t capacidad = 0;
    char *linea = NULL;
    while ((getline(&linea, &capacidad, stdin) != -1)) infix_to_postfix(linea);
    free(linea);
    return 0;
}