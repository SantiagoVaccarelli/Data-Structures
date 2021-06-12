#!/usr/bin/python3
from biblioteca import *
from constantes import *
from cargar_grafos import *
import sys

def crear_grafo_canciones_(grafo_canciones,playlists):
    if grafo_canciones == None: 
        grafo_canciones = crear_grafo_canciones(playlists)
    return grafo_canciones

def comandos(grafo,playlists,usuarios,canciones):
    
    grafo_canciones = None
    lista_pagerank = []
    linea = sys.stdin.readline().strip("\n")
    while linea:

        stdin = linea.split(maxsplit =1)
        comando = stdin[0]
        if comando == CAMINO:
            entrada = stdin[1].split(SEPARADOR)
            if (len(entrada)) != 2:
                print(ERROR_PARAMETROS)   
                continue
            procesar_camino(entrada[0], entrada[1],grafo,playlists,usuarios,canciones)
        
        elif comando == MAS_IMPORTANTES:
            entrada = stdin[1].split()
            if not entrada[0].isdigit():
                print(ERROR_PARAMETROS) 
                continue
            if len(lista_pagerank)==0:
                lista_pagerank = mas_importantes(grafo,canciones)
            imprimir_mas_importantes(int(entrada[0]),lista_pagerank)

        
        elif comando == RECOMENDACION: 
            entrada = stdin[1].split(maxsplit=2)
            usuarios_canciones = entrada[2].split(SEPARADOR)
            if not entrada[1].isdigit():
                print(ERROR_PARAMETROS)
                continue 
            grafo_canciones = crear_grafo_canciones_(grafo_canciones,playlists)
            recomendacion(grafo,usuarios_canciones,int(entrada[1]),entrada[0],usuarios,playlists,grafo_canciones)
        
        elif comando == CICLO:
            entrada = stdin[1].split(maxsplit=1)
            if not entrada[0].isdigit():
                print(ERROR_PARAMETROS)
                continue
            grafo_canciones = crear_grafo_canciones_(grafo_canciones,playlists)
            ciclo(int(entrada[0]), entrada[1],grafo_canciones)
        
        elif comando == RANGO:
            entrada = stdin[1].split(maxsplit=1)   
            if  not entrada[0].isdigit():
                print(ERROR_PARAMETROS)
                continue
            grafo_canciones = crear_grafo_canciones_(grafo_canciones,playlists)
            rango(int(entrada[0]),entrada[1],grafo_canciones)
        
        elif comando == CLUSTERING:
            grafo_canciones = crear_grafo_canciones_(grafo_canciones,playlists)
            coeficiente_clustering(None if len(stdin) == 1 else stdin[1],grafo_canciones)
        
        else:
            print(ERROR_COMANDO)
        
        linea = sys.stdin.readline().strip("\n")

def main():
    tsv = sys.argv[1]
    bipartito,playlists,usuarios,canciones = crear_grafo_usuarios(tsv)
    comandos(bipartito ,playlists,usuarios,canciones)
        
main()