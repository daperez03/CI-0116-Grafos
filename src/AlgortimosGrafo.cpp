#include "AlgortimosGrafo.hpp"

//-------------------------------Floyd-----------------------------

#include <iostream>
int obtenerIndice(std::vector<Vertice*>& vertices, Vertice* v) {
  int indice = -1;
  while (v != vertices[++indice]);
  return indice;
}

int InitEDA (Grafo& grafo, std::vector<Vertice*>& vertices
  , Matriz(int)& costos, Matriz(Vertice*)& conexiones) {
  Vertice* v = grafo.PrimerVertice();
  int n = 0;
  while (v != nullptr) {
    vertices.push_back(v);
    ++n;
    v = grafo.SiguienteVertice(v);
  }
  conexiones.resize(n);
  costos.resize(n);
  for (int i = 0; i < n; i++) {
    conexiones[i].resize(n);
    costos[i].resize(n);
    for (int j = 0; j < n; j++) {
      costos[i][j] = infinito;
      conexiones[i][j] = nullptr;
    }
  }
  v = grafo.PrimerVertice();
  while (v != nullptr) {
    Vertice* va = grafo.PrimerVerticeAdyacente(v);
    while (va != nullptr) {
      int i = obtenerIndice(vertices, v);
      int j = obtenerIndice(vertices, va);
      costos[i][j] = grafo.Peso(v, va);
      va = grafo.SiguienteVerticeAdyacente(v,va);
    }
    v = grafo.SiguienteVertice(v);
  }
  return n;
}

void Floyd (Grafo& grafo, Matriz(Vertice*)& conexiones
  , std::vector<Vertice*>& vertices) {
  Matriz(int) costos;
  int n = InitEDA(grafo, vertices, costos, conexiones);
  for (int pivote = 0; pivote < n; pivote++) {
    for (int i = 0; i < n; ++i) {
      if (i != pivote) {
        for (int j = 0; j < n; ++j) {
          if (i != pivote && i != j) {
            if (costos[i][pivote] != infinito && costos[pivote][j] != infinito
              && costos[i][j] > costos[i][pivote] + costos[pivote][j]) {
              costos[i][j] = costos[i][pivote] + costos[pivote][j];
              conexiones[i][j] = vertices[pivote];
            }
          }
        }
      }
    }
  }
}

//-------------------------------Kruskal-----------------------------

bool Kruskal (Grafo& grafo, std::vector<AristaKruskal>& solMejor) {
  std::priority_queue<AristaKruskal, std::vector<AristaKruskal>, OrderOfPriority> APO;
  std::vector<Par<Vertice*>> diccionario;
  ConjuntoDeConjuntos<Vertice*> conjuntoDeConjuntos;
  Vertice* v = grafo.PrimerVertice();
  int n = 0;
  while (v != nullptr) {
    conjuntoDeConjuntos.AgregarSubConjunto(v);
    Vertice* va = grafo.PrimerVerticeAdyacente(v);
    while (va != nullptr) {
      if (!Existe<Par<Vertice*>>(diccionario, Par<Vertice*>(v, va))) {
        AristaKruskal nuevaArista;
        nuevaArista.salida = v;
        nuevaArista.llegada = va;
        nuevaArista.peso = grafo.Peso(v, va);
        APO.push(nuevaArista);
        diccionario.push_back(Par<Vertice*>(v, va));
      }
      va = grafo.SiguienteVerticeAdyacente(v, va);
    }
    v = grafo.SiguienteVertice(v);
    ++n;
  }
  int TotalAristasEscogidas = 0;
  while (TotalAristasEscogidas < n-1 && !APO.empty()) {
    AristaKruskal arista = APO.top();
    APO.pop();
    int identificador1 = conjuntoDeConjuntos.buscarElemento(arista.salida);
    int identificador2 = conjuntoDeConjuntos.buscarElemento(arista.llegada);
    if (identificador1 != identificador2) {
      solMejor.push_back(arista);
      conjuntoDeConjuntos.unir(identificador1, identificador2);
      TotalAristasEscogidas++;
    }
  }
  return TotalAristasEscogidas == n-1;
}

//-------------------------------ColorearVertice-----------------------------

void ColorearVertice(Grafo& grafo, Vertice* v, ConjuntoDeConjuntos<Vertice*>& conjuntoDeConjuntos
  , std::map<Vertice*, std::set<Vertice*>>& VectorDeAdyacentes, int& solMejor
  , ConjuntoDeConjuntos<Vertice*>& solucion) {
  int n = grafo.NumVertice();
  for (int i = 0; i < n; i++) {
    if(conjuntoDeConjuntos.disjuntos(i, VectorDeAdyacentes[v])) {
      if (conjuntoDeConjuntos.count() <= i) {
        conjuntoDeConjuntos.AgregarSubConjunto(v);
      } else {
        conjuntoDeConjuntos.agregarElemento(i, v);
      }
      if (grafo.SiguienteVertice(v) == nullptr) {
        if (conjuntoDeConjuntos.count() - conjuntoDeConjuntos.emptySets() < solMejor || solMejor == -1) {
          solMejor = conjuntoDeConjuntos.count() - conjuntoDeConjuntos.emptySets();
          solucion = conjuntoDeConjuntos;
        }
      } else {
        ColorearVertice(grafo, grafo.SiguienteVertice(v), conjuntoDeConjuntos, VectorDeAdyacentes, solMejor, solucion);
      }
      conjuntoDeConjuntos.borrarElemento(i, v);
    }
  }
}

void ColorearGrafo(Grafo& grafo, ConjuntoDeConjuntos<Vertice*>& solucion) {
  std::map<Vertice*, std::set<Vertice*>> VectorDeAdyacentes;
  Vertice* v = grafo.PrimerVertice();
  int n = 0;
  while (v != nullptr) {
    Vertice* va = grafo.PrimerVerticeAdyacente(v);
    std::set<Vertice*> adyacentes;
    while (va != nullptr) {
      adyacentes.insert(va);
      va = grafo.SiguienteVerticeAdyacente(v, va);
    }
    VectorDeAdyacentes.insert({v, adyacentes});
    v = grafo.SiguienteVertice(v);
    ++n;
  }
  ConjuntoDeConjuntos<Vertice*> conjuntoDeConjuntos;
  int solMejor = -1;
  ColorearVertice(grafo, grafo.PrimerVertice(), conjuntoDeConjuntos
    , VectorDeAdyacentes, solMejor, solucion);
}
