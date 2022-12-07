#if 1

#include <chrono>
#include <cstdbool>
#include <iostream>
#include <cstdlib>

#include "AlgortimosGrafo.hpp"
#include "Grafo.hpp"

// 10 000
// 50 000
// 100 000

// AveriguarProfundidad
// ListarIesimo
// BuscarHermanoIzq
// existe

#define todos(x) x * x-1
#define unico(x) x-1

#define n 10000
#define a todos(n)


int main() {
// Crear Grafo
  Grafo grafo;
  grafo.Crear();

  // Agregar Nodos
  for (int indice = 1; indice <= n; indice++){
    grafo.AgregarVertice((char)indice);
  }

  // Agregar Aristas
  int count = 0;
  Vertice* v1 = grafo.PrimerVertice();
  while (v1 != nullptr && count < a) {
    Vertice* v2 = grafo.PrimerVertice();
    while (v2 != nullptr && count < a) {
      if (v1 != v2 && !grafo.ExisteArista(v1, v2)) {
        grafo.AgregarArista(v1, v2, (rand() % 30));
        ++count;
      }
      v2 = grafo.SiguienteVertice(v2);
    }
    v1 = grafo.SiguienteVertice(v1);
  }

  // Algoritmo
  std::map<Vertice*, std::map<Vertice*, Vertice*>> solucion;
  auto start_time = 
    std::chrono::high_resolution_clock::now();
    N_VecesDijkstra(grafo, solucion);
  auto finish_time = 
    std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_time = finish_time - start_time;
  double duracion = elapsed_time.count();
  std::cout << "Duracion: " << duracion << " segundos" << std::endl;
  return EXIT_SUCCESS;
}

#endif