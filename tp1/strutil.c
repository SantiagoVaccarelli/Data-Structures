#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutil.h"

char *substr(const char *str, size_t n){
    size_t i =0;
    for(; i < n && str[i] != '\0';i++);
    char *substr = malloc(i+1);
    strncpy(substr,str,i);
    substr[i] = '\0';
    return substr;
}

char **split(const char *str, char sep){
    size_t separadores = 0, largo = strlen(str), indice = 0, corrimiento = 0, letras =0,palabras;
    for(int i = 0; i< largo; i++){
        if (str[i] == sep) separadores++;
    }
    palabras = separadores+2;
    char **strv = malloc(sizeof(char*) *palabras);
    for (int i = 0; i<largo; i++){
        if (str[i] == sep){
            strv[indice] = substr(str+corrimiento, letras);
            if (!strv[indice]){
                free_strv(strv);
                return NULL;
            } 
            indice++;
            corrimiento += (letras + 1);
            letras=0;
        }
        else{
            letras++;
        }
    }
    strv[indice] = substr(str+corrimiento, letras);
    if (!strv[indice]){
        free_strv(strv);
        return NULL;
    }
    indice++;
    strv[indice] = NULL;
    return strv;
}


char *join(char **strv, char sep){
    size_t palabra = 0, letra = 0, total = 0;
    while (strv[palabra]){
        if (strv[palabra][letra]){
            letra++;
            total++;
        }
        else{
            palabra++;
            total++;
            letra = 0;
        }
    }
    if (sep == '\0') total -= (palabra-2);
    char *str =  calloc(1, total? sizeof(char)*total:1);
    if (!str) return NULL;
    size_t indice_str = 0;
    palabra = 0; letra = 0;
    for(size_t i = 0; i < total; i++){
        if (strv[palabra][letra]){
            str[indice_str] = strv[palabra][letra]; 
            letra++;
        }
        else{
            if (sep != '\0') str[indice_str] = sep; 
            else indice_str--;
            palabra++;
            letra = 0;
        }
        indice_str++;
    }
    if (!total) str[0] = '\0';
    else str[total-1] = '\0';
    return str;
}


void free_strv(char *strv[]){
    for (int i = 0; strv[i] != NULL; i++) free(strv[i]);
    free(strv);
}