from grafo import Grafo

def leer_linea(archivo):
    linea = archivo.readline()
    return linea.strip().split("\t") if linea else None

def tsv_reader(ruta, grafo, playlists,usuarios,canciones):
    archivo = open(ruta,"r")
    linea = leer_linea(archivo)
    while linea:
        cancion = " - ".join((linea[2], linea[3]))
        if not grafo.pertenece(linea[1]):
            grafo.insertar_vertice(linea[1])
        if not grafo.pertenece(cancion):
            grafo.insertar_vertice(cancion)
        if not grafo.es_adyacente(linea[1], cancion):
            grafo.insertar_arista(linea[1], cancion,linea[5])
        
        if linea[5] not in playlists:
            playlists[linea[5]] = []
        if cancion not in playlists[linea[5]]:
            playlists[linea[5]].append(cancion)
        if linea[5] not in usuarios:
            usuarios[linea[5]] =linea[1]
        if linea[2]:
            canciones[cancion] = True
        linea = leer_linea(archivo)
    archivo.close()
    

def crear_grafo_usuarios(archivo):
    usuarios = Grafo()
    playlists = {}
    canciones = {}
    usuarios_playlist = {}
    tsv_reader(archivo, usuarios, playlists,usuarios_playlist,canciones)
    return usuarios, playlists,usuarios_playlist,canciones

def crear_grafo_canciones(playlists):

    canciones = Grafo()
    for _,lista_canciones in playlists.items():
        for j in range(len(lista_canciones)-1):
            cancion2 = lista_canciones[j]
            if not canciones.validar_vertice(cancion2):
                canciones.insertar_vertice(cancion2)
            for i in range(j+1,len(lista_canciones)):
                cancion1 = lista_canciones[i]
                if not canciones.validar_vertice(cancion1):
                    canciones.insertar_vertice(cancion1)
                if not canciones.es_adyacente(cancion1,cancion2):
                    canciones.insertar_arista(cancion1,cancion2)
    return canciones