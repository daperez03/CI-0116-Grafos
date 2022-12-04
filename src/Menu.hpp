#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#ifdef _WIN32
  #include <windows.h>
#endif
#include "AlgortimosGrafo.hpp"

void clearTerminal() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

template <class T>
void input(const char* txt, T& contenedor) {
  std::cout << std::endl << txt << ": ";
  std::cin >> contenedor;
  std::cout << std::endl;
}

template <class T>
void output(T contenido, const char* txt = " ") {
  std::cout << std::endl << txt << ": " << contenido << std::endl;
}

void output(const char* txt = " ") {
  std::cout << txt << std::endl;
}

void output(const char* txt, int& lista) {
  std::cout << lista++ << ". " << txt << std::endl;
}

void output(const char* txt, Vertice* vertice) {
  if (vertice == nullptr)  {
    std::cout << std::endl << txt << ": " << "Null" << std::endl;
  } else {
    std::cout << std::endl << txt << ": " << vertice->etiqueta << std::endl;
  }
}

void crearTabla(Grafo& grafo, Vertice* vertice, Vertice* v
  , std::map<Vertice*, Vertice*> solucion, int identacion) {
  if (v != vertice) {
    crearTabla(grafo, vertice, solucion[v], solucion, 1);
  }
  std::cout << grafo.Etiqueta(v);
  if (identacion) std::cout << "\t->\t";
}

void outputDijkstra(Grafo& grafo, Vertice* vertice, std::map<Vertice*, Vertice*> solucion) {
  Vertice* v = grafo.PrimerVertice();
  while (v != nullptr) {
    if (v != vertice) {
      std::cout << "Salida: " << grafo.Etiqueta(vertice) << "\t";
      std::cout << "Llegada: " << grafo.Etiqueta(v) << std::endl;
      crearTabla(grafo, vertice, v, solucion, 0);
      std::cout << std::endl;
    }
    v = grafo.SiguienteVertice(v);
  }
}

void outputFloyd(Matriz(Vertice*)& solucion, std::vector<Vertice*>& vertices) {
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << "\t" << vertices[i]->etiqueta;
  }
  std::cout << std::endl;
  for (int i = 0; i < solucion.size(); ++i) {
    std::cout << vertices[i]->etiqueta << "\t";
    for (int j = 0; j < solucion[i].size(); ++j) {
      if (solucion[i][j] != nullptr) {
        std::cout << solucion[i][j]->etiqueta << "\t";
      } else {
        std::cout << "-" << "\t";
      }
    }
    std::cout << std::endl;
  }
}

void outputN_VecesDijkstra(Grafo& grafo, std::map<Vertice*, std::map<Vertice*, Vertice*>> solucion) {
  Vertice* v = grafo.PrimerVertice();
  while (v != nullptr) {
    std::cout << "\t" << grafo.Etiqueta(v);
    v = grafo.SiguienteVertice(v);
  }
  std::cout << std:: endl;
  Vertice* v1 = grafo.PrimerVertice();
  while (v1 != nullptr) {
    std::cout << grafo.Etiqueta(v1) << "\t";
    Vertice* v2 = grafo.PrimerVertice();
    while (v2 != nullptr) {
      if (v1 != v2) {
        if (solucion[v1][v2] == v1) {
          std::cout << "-" << "\t";
        } else {
          std::cout << grafo.Etiqueta(solucion[v1][v2]) << "\t";
        }
      } else {
        std::cout << "-" << "\t";
      }
      v2 = grafo.SiguienteVertice(v2);
    }
    v1 = grafo.SiguienteVertice(v1);
    std::cout << std::endl;
  }
}

void outputPrim(Grafo& grafo, std::map<Vertice*, Vertice*> solucion) {
  Vertice* v = grafo.PrimerVertice();
  v = grafo.SiguienteVertice(v);
  while (v != nullptr) {
    std::cout << grafo.Etiqueta(solucion[v]) << "\t->\t"
      << grafo.Etiqueta(v) << std::endl;
    v = grafo.SiguienteVertice(v);
  }
}

void outputKruskal(std::vector<AristaKruskal>& solucion) {
  for (int i = 0; i < solucion.size(); ++i) {
    std::cout << solucion[i].salida->etiqueta << "->" << solucion[i].llegada->etiqueta << ": " << solucion[i].peso << std::endl;
  }
  std:: cout << std::endl;
}

void outputColorearGrafo(Grafo& grafo, ConjuntoDeConjuntos<Vertice*>& solucion) {
  Vertice* vertice = grafo.PrimerVertice();
  while (vertice != nullptr) {
    std::cout << vertice->etiqueta << ": " << solucion.buscarElemento(vertice) << std::endl;
    vertice = grafo.SiguienteVertice(vertice);
  }
  std::cout << std::endl;
}

#endif
