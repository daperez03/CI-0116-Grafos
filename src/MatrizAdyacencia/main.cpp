#include "Grafo.hpp"
#include <iostream>
#define verticeNulo nullptr

Vertice* buscarVertice(Grafo& grafo, char etiqueta) {
  Vertice* vertice = grafo.PrimerVertice();
  bool salida = false;

  while (vertice != verticeNulo && !salida) {
    if (grafo.Etiqueta(vertice) == etiqueta) {
      salida = true;
    } else {
      vertice = grafo.SiguienteVertice(vertice);
    }
  }

  return vertice;
}


int main() {
  Grafo grafo;
  grafo.Crear();
  grafo.AgregarVertice('a');
  grafo.AgregarVertice('b');
  grafo.AgregarVertice('c');
  grafo.AgregarVertice('d');
  grafo.AgregarVertice('e');
  grafo.AgregarVertice('f');
  Vertice* vertice = grafo.PrimerVertice();
  while (vertice != verticeNulo) {
    std::cout << grafo.Etiqueta(vertice) << std::endl;
    vertice = grafo.SiguienteVertice(vertice);
  }
  std::cout << std::endl;

  vertice = grafo.PrimerVertice();
  Vertice* verticeAdyacente = buscarVertice(grafo, 'b');
  grafo.AgregarArista(vertice, verticeAdyacente, 10);
  verticeAdyacente = buscarVertice(grafo, 'c');
  grafo.AgregarArista(vertice, verticeAdyacente, 15);
  
  verticeAdyacente = grafo.PrimerVerticeAdyacente(vertice);
  while (verticeAdyacente != verticeNulo) {
    std::cout << grafo.Etiqueta(verticeAdyacente) << std::endl;
    std::cout << "Peso: " << 
    grafo.Peso(vertice, verticeAdyacente) << std::endl;
    verticeAdyacente = grafo.SiguienteVerticeAdyacente(vertice
      , verticeAdyacente);
  }

  return 0;
}