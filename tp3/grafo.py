class Grafo:
    def __init__(self, vertices = []):
        self.vertices = {}
        for v in vertices:
            self.vertices[v] = {}
    
    def _len_(self):
        return len(self.vertices)
        
    def insertar_vertice(self, vertice):
        if not vertice in self.vertices:
            self.vertices[vertice] = {}     
        
    def insertar_arista(self, vertice1, vertice2,peso=1):
        if vertice1 in self.vertices and vertice2 in self.vertices:
            if not self.es_adyacente( vertice1,vertice2):
                self.vertices[vertice1][vertice2] = peso
                self.vertices[vertice2][vertice1] = peso

    def borrar_vertice(self,vertice):
        for i in self.vertices:
            if vertice in i:
                del self.vertices[i][vertice]
        del self.vertices[vertice]
    
    def validar_vertice(self, v):
        if v not in self.vertices: return False
        return True

    def borrar_arista(self, vertice1, vertice2):
        if not self.es_adyacente(vertice1,vertice2): return
        del self.vertices[vertice1][vertice2]
    
    def vertice_aleatorio(self):
        return self.obtener_vertices()[0]
        
    def es_adyacente(self, vertice1, vertice2):
        if vertice1 not in self.vertices or vertice2 not in self.vertices:
            return False
        return vertice2 in self.vertices[vertice1]

    def obtener_vertices(self):
        return list(self.vertices.keys())

    def obtener_peso(self,vertice1,vertice2):
        if self.es_adyacente(vertice1,vertice2):
            return self.vertices[vertice1][vertice2]

    def adyacentes(self, vertice):
        return list(self.vertices[vertice].keys())
    
    def pertenece(self, vertice):
        return vertice in self.vertices