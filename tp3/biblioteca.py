from funciones import *
from constantes import *

"""FUNCIONES AUXILIARES"""

def validar_vertice(vertice,grafo):
    if not grafo.validar_vertice(vertice):
        print(ERROR_PERTENECE)
        return False
    return True

def imprimir_lista_formato(lista,n):
    i = 0
    for cancion in lista[0:len(lista)-1]:
        if i == n-1:
            break
        
        print(f'{cancion[1]}{"; " if cancion != lista[n-1][1]  else ""}',end="")
        i += 1
    print(lista[n][1])
    print("")
    
def ordenar_dic(dic,tipo,usuarios,canciones,usuarios_canciones,grafo_canciones):

    if tipo == VERTICE_CANCION:
        return sorted([(dic[v], v) for v in dic if v in grafo_canciones.obtener_vertices() and v not in usuarios_canciones], reverse=True)  
    elif tipo == VERTICE_USUARIO:
        return sorted([(dic[v], v) for v in dic if v in usuarios.values() and v not in usuarios_canciones], reverse=True)
    else : return None


"""FUNCIONES DE COMANDOS"""

def procesar_camino(origen,destino,grafo,playlists,usuarios,canciones):
    if not validar_vertice(origen,grafo): return
    if not validar_vertice(destino,grafo): return
    if not origen in canciones.keys() or destino not in canciones.keys():
        print(ERROR_CANCIONES_CAMINO)
        return 

    camino = devolver_camino(grafo,origen,destino)
    if not camino: print(ERROR_CAMINO)
    else:
        for j in range(len(camino)-1):
            if j%2 == 0:
                playlist = grafo.obtener_peso(camino[j],camino[j+1])
                print(CANCION_SALIDA.format(camino[j],playlist), end="")
            else:
                playlist = grafo.obtener_peso(camino[j],camino[j+1])
                print(USUARIO_SALIDA.format(camino[j],playlist), end="")
            if j == len(camino)-2: print(camino[j+1])


def mas_importantes(grafo,canciones):
    lista_pagerank = pagerank(grafo,canciones) 
    return lista_pagerank


def imprimir_mas_importantes(numero_canciones,lista_pagerank):

    if numero_canciones == 0:
        print(ERROR_MAS_IMPORTANTES)
        return 

    if lista_pagerank:
        i = 0
        for const,cancion in lista_pagerank:
            if i == int(numero_canciones)-1:
                print(cancion)
                return
            print(f'{cancion}; ',end="")
            i+=1


def recomendacion(grafo,usuarios_canciones, n,tipo,usuarios,playlists,grafo_canciones):
    for cancion in usuarios_canciones:
        if not validar_vertice(cancion,grafo_canciones): return
    
    dic = pagerank_random_walks(grafo,usuarios_canciones)
    lista = ordenar_dic(dic,tipo,usuarios,playlists,usuarios_canciones,grafo_canciones)
    if lista:  imprimir_lista_formato(lista,int(n))
    else: print(ERROR_RECOMENDACION)


def ciclo(largo, cancion,grafo):
    if not validar_vertice(cancion,grafo): return
    lista = devolver_ciclo(grafo,largo,cancion)
    if lista: 
        if len(lista) != largo+1: 
            print(ERROR_CAMINO)
            return
        else:
            for i in lista[0:len(lista)-1]:
                print(f"{i} --> ", end="")
            print(lista[-1])
    else: print(ERROR_CAMINO)


def rango(saltos, cancion,grafo):
    if not validar_vertice(cancion,grafo):
        print(ERROR_RANGO)
        return 
    rango = obtener_rango(grafo,saltos,cancion)
    print(rango)


def coeficiente_clustering(cancion,grafo):
    if not validar_vertice(cancion,grafo): return 
    if not cancion:
        clustering_total = 0
        for v in grafo.obtener_vertices():
            clustering_total += obtener_numero_clustering(grafo,v)
        resultado = clustering_total/len(grafo.vertices)
    else: resultado = obtener_numero_clustering(grafo,cancion)
    print("%.3f" % resultado)