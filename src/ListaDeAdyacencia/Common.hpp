#ifndef COMMON_HPP
#define COMMON_HPP

class Arista;

/// Simula un vertice de un grafo
class Vertice {
 public:
  Vertice(char etiqueta) : etiqueta(etiqueta) {}
  /// Etiqueta de el vertice
  char etiqueta = '\0';
  /// Puntero a las aristas que contiene el vertice
  Arista* siguienteArista = nullptr;
  /// Puntero al siguiente vertice del grafo
  Vertice* siguiente = nullptr;
};

/// Simula arista de un vertice
class Arista {
 public:
  /// Puntero al vertice adyacente de la arista
  Vertice* verticeAdyacente = nullptr;
  /// Peso de la arista
  int peso = 0;
  /// Puntero a siguiente arista adyacente del vertice principal
  Arista* siguienteArista = nullptr;
};

#endif