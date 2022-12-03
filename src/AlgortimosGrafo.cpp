#include <vector>
#include <queue>
#include <map>
#include "Common.hpp"
#include "Grafo.hpp"
#define Matriz(x) std::vector<std::vector<x>>
#define infinito -1

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
  }
  return n;
}

void Floyd (Grafo grafo) {
  std::vector<Vertice*> vertices;
  Matriz(int) costos;
  Matriz(Vertice*) conexiones;
  int n = InitEDA(grafo, vertices, costos, conexiones);
  for (int pivote = 0; pivote < n-1; pivote++) {
    for (int i = 0; i < n; ++i) {
      if (i != pivote) {
        for (int j = 0; j < n; ++j) {
          if (i != pivote && i != j) {
            if (costos[i][pivote] != -infinito && costos[pivote][j] != infinito
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

bool Kruskal (Grafo grafo, std::vector<AristaKruskal>& solMejor) {
  std::priority_queue<AristaKruskal, std::vector<AristaKruskal>, OrderOfPriority> APO;
  std::vector<Par<Vertice*>> diccionario;
  ConjuntoDeConjuntos<Vertice*> CC;
  Vertice* v = grafo.PrimerVertice();
  int n = 0;
  while (v != nullptr) {
    CC.AgregarSubConjunto(v);
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
    std::set<Vertice*>* conjunto1 = CC.buscarElemento(arista.salida);
    std::set<Vertice*>* conjunto2 = CC.buscarElemento(arista.llegada);
    if (conjunto1 != conjunto2) {
      solMejor.push_back(arista);
      ++TotalAristasEscogidas;
      CC.unir(conjunto1, conjunto2);
    }
  }
  return TotalAristasEscogidas == n-1;
}


