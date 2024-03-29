#ifndef GRAFO_HPP
#define GRAFO_HPP

#define is_end(x) (x == nullptr)
#define verticeNulo nullptr

#include "Common.hpp"

/// Modelo Grafo representado mediante lista de listas
class Grafo {
 private:
  /// Vertice de partida del grafo
  Vertice* inicio = nullptr;

  /// Efecto: Busca una arista especifica de un vertice.
  /// Requiere: Grafo inicializado.
  /// Modifica: No modifica el grafo.
  Arista* buscarArista(Vertice* vertice1, Vertice* vertice2);

  /// Efecto: Borra arista de vertice1 la cual contiene a vertice 2.
  /// Requiere: Grafo inicializado.
  /// Modifica: Borra 1 arista de vertice 1.
  void borrarArista(Vertice* vertice1, Vertice* vertice2);

 public:
  /// Constructor por default
  Grafo() = default;

  /// Destructor por default
  ~Grafo() = default;

  /// Efecto: Crea un nuevo grafo.
  /// Requiere: Grafo no inicializado.
  /// Modifica: Inicializa el grafo.
  void Crear();

  /// Efecto: Destruye un grafo
  /// Requiere: Grafo inicializado.
  /// Modifica: Destruye el grafo.
  void Destruir();

  /// Efecto: Agrega un nuevo vértice al grafo con la
  /// etiqueta enviada por parámetros y lo retorna.
  /// Requiere: Grafo inicializado y una etiqueta.
  /// Modifica: Grafo pasado por parámetro agregando un
  /// vértice más con la etiqueta pasada por parámetro.
  Vertice* AgregarVertice(char etiqueta);

  /// Efecto: Elimina un vértice aislado.
  /// Requiere: Grafo inicializado, vértice válido en el grafo
  /// y que este vértice esté aislado.
  /// Modifica: Elimina el vértice que se le indica en el grafo
  /// que se envía por parámetro.
  void EliminarVertice(Vertice* actual);

  /// Efecto: Modifica la etiqueta de un vértice
  /// Requiere: Requiere un grafo inicializado, un vértice que se le
  /// cambiará la etiqueta y un elemento que será nuestra nueva etiqueta.
  /// Modifica: Modifica la etiqueta de un vértice dado en nuestro grafo.
  void ModificarEtiqueta(Vertice* actual, char etiqueta);

  /// Efecto: Retorna la etiqueta del vértice solicitado.
  /// Requiere: Requiere el grafo inicializado y el vértice válido en el grafo.
  /// Modifica: No modifica el grafo.
  char Etiqueta(Vertice* actual);

  /// Efecto: Agrega una arista entre un par de vértices.
  /// Requiere: Requiere el grafo inicializado, ambos vértices y el peso
  /// válidos en el grafo.
  /// Modifica: Agrega una nueva arista entre el par de vértices.
  void AgregarArista(Vertice* vertice1, Vertice* vertice2, int peso);

  /// Efecto: Elimina la arista entre un par de vértices.
  /// Requiere: Requiere el grafo inicializado y ambos vértices válidos en el grafo.
  /// Modifica: Elimina la arista existente entre un par de vértices, en caso de no
  /// existir, no modifica al grafo.
  void EliminarArista(Vertice* vertice1, Vertice* vertice2);

  /// Efecto: Modifica el peso de la arista entre un par de vértices.
  /// Requiere: Requiere grafo inicializado, ambos vértices válidos en el grafo y
  /// una arista existente entre este par de vértices.
  /// Modifica: Modifica el peso de la arista entre un par de vértices.
  void ModificarPeso(Vertice* vertice1, Vertice* vertice2, int peso);

  /// Efecto: Retorna el peso de la arista entre un par de vértices.
  /// Requiere: Requiere grafo inicializado, ambos vértices válidos en el grafo
  /// y una arista existente entre ambos vértices.
  /// Modifica: No modifica el grafo.
  int Peso(Vertice* vertice1, Vertice* vertice2);

  /// Efecto: Devuelve el primer vértice del grafo.
  /// Requiere: Grafo inicializado.
  /// Modifica: No modifica el grafo.
  Vertice* PrimerVertice();

  /// Efecto: Devuelve el primer vértice del grafo.
  /// Requiere: Grafo inicializado.
  /// Modifica: No modifica el grafo.
  Vertice* SiguienteVertice(Vertice* actual);

  /// Efecto: Devuelve el primer vértice adyacente de un vértice.
  /// Requiere: Grafo inicializado y vértice principal válido.
  /// Modifica: No modifica el grafo.
  Vertice* PrimerVerticeAdyacente(Vertice* actual);

  /// Efecto: Devuelve el primer vértice adyacente de un vértice.
  /// Requiere: Grafo inicializado y vértice principal válido.
  /// Modifica: No modifica el grafo.
  Vertice* SiguienteVerticeAdyacente(Vertice* actual, Vertice* ultimoAdyacente);

  /// Efecto: Devuelve el número de vértices de un grafo.
  /// Requiere:  Grafo inicializado.
  /// Modifica: No modifica el grafo.
  int NumVertice();

  /// Efecto: Indica si existe una arista.
  /// Requiere:  Grafo inicializado.
  /// Modifica: No modifica el grafo.
  bool ExisteArista(Vertice* v1, Vertice* v2);
};
#endif
