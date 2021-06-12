from collections import*
from constantes import*
from random import randint

def devolver_camino_( padres, fin,origen):
    camino = []
    while fin != origen:
        camino.append(fin)
        fin = padres[fin]
    camino.append(origen)
    return camino[::-1]


def devolver_camino(grafo, origen, fin):
    padres = bfs_camino(grafo, origen, fin)
    if not padres: return None
    #if fin not in padres: return None
    camino = devolver_camino_( padres, fin,origen)
    return camino

def bfs_camino(grafo, origen,destino):
    padres = {}
    visitados = set()
    visitados.add(origen)
    padres[origen] = None
    q = deque([])
    q.append(origen)
    while q:
        vertice = q.popleft()
        for adyacente in grafo.adyacentes(vertice):
            if adyacente not in visitados:
                padres[adyacente] = vertice
                visitados.add(adyacente)
                q.append(adyacente)
                if adyacente == destino:
                    return padres
    return None

def devolver_ciclo(grafo,largo,cancion):
    visitados = set()
    camino = []
    camino.append(cancion)
    ciclo = dfs_ciclo(grafo,cancion,cancion,visitados,camino,largo)
    return ciclo


def dfs_ciclo(grafo,origen,v,visitados,camino,largo):
    visitados.add(v)

    if len(camino) == largo:
        if origen in grafo.adyacentes(v):
            camino.append(origen)
            return camino
        else: return None    

    for w in grafo.adyacentes(v):
        if w not in visitados:
            camino.append(w)
            ciclo = dfs_ciclo(grafo,origen,w,visitados,camino, largo)
            if ciclo!= None:  return ciclo
    
    visitados.remove(v)
    return None


def obtener_rango(grafo,n ,origen):
    q = deque([])
    q.append(origen)
    orden = {}
    visitados = set()
    visitados.add(origen)
    orden[origen] = 0
    canciones_en_rango = 0
    while q:
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                orden[w] = orden[v]+1
                if orden[w] == n: canciones_en_rango += 1
                if orden[w] > n: break
                q.append(w)
    return canciones_en_rango


def pagerank(grafo,canciones):
    rank = {}
    const  = 0.85
    pagerank_(grafo,float(const),rank)
    return sorted([(rank[v], v) for v in rank if v in canciones.keys()], reverse=True)


def pagerank_(grafo, const ,rank):
    
    largo_grafo = grafo._len_()
    for vertice in grafo.obtener_vertices():
        rank[vertice] = (1-const)/largo_grafo

    for _ in range(20):
        for v in grafo.obtener_vertices():
            rank[v] = (1 - const) / largo_grafo + const * sum(rank[w] /len(grafo.adyacentes(w)) for w in grafo.adyacentes(v))


def random_walks_inicializar(rank,dic):
    for i in rank:
        if i not in dic:dic[i] = 1


def pagerank_random_walks(grafo,usuarios_canciones):
    dic = {}
    largo = 20
    for cancion in usuarios_canciones:
        camino = random_walks(grafo,cancion)
        random_walks_inicializar(camino,dic)
        for j in range(largo):
            i = 1
            while i <= largo:
                largo_ady = len(grafo.adyacentes(camino[i-1]))
                dic[camino[i-1]] = (dic[camino[i]] /largo_ady)
                i += 1
    return dic


def random_walks(grafo,usuario_cancion):
    camino = [usuario_cancion]
    actual = usuario_cancion

    for j in range(20):
        adyacentes = grafo.adyacentes(actual)
        actual = adyacentes[(randint(0,len(adyacentes)-1))]
        camino.append(actual)

    return camino


def obtener_numero_clustering(grafo, cancion):
    if cancion not in grafo.vertices: 
        print(ERROR_PERTENECE)
        return None
    adyacentes  = grafo.adyacentes(cancion)
    if len(adyacentes) < 2: return 0.000
    aristas=0
    for w in adyacentes:
        for i in adyacentes:
            if w != i:
                if grafo.es_adyacente(i,w):aristas+=1

    return float(aristas/(len(adyacentes)*(len(adyacentes)-1)))