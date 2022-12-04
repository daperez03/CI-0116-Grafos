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
        std::cout << "null" << "\t";
      }
    }
    std::cout << std::endl;
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
