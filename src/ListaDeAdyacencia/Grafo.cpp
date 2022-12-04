#include <cstdlib>
#include "Grafo.hpp"

// Public:

void Grafo::Crear() {
  this->inicio = nullptr;
}

void Grafo::Destruir() {
  Vertice* vertice = this->inicio;
  while (!is_end(vertice)) {
    Arista* actual = vertice->siguienteArista;
    while (!is_end(actual)) {
      Arista* anterior = actual;
      actual = actual->siguienteArista;
      delete anterior;
    }
    Vertice* anterior = vertice;
    vertice = vertice->siguiente;
    delete anterior;
  }
}

Vertice* Grafo::AgregarVertice(char etiqueta) {
  Vertice* siguiente = this->inicio;
  this->inicio = new Vertice(etiqueta);
  this->inicio->siguiente = siguiente;
  return this->inicio;
}

void Grafo::EliminarVertice(Vertice* actual) {
  if (this->inicio == actual) {
    Vertice* anterior = this->inicio;
    this->inicio = inicio->siguiente;
    delete anterior;
  } else {
    Vertice* vertice = this->inicio;
    while (vertice->siguiente != actual) {
      vertice = vertice->siguiente;
    }
    Vertice* anterior = vertice->siguiente;
    vertice->siguiente = vertice->siguiente->siguiente;
    delete anterior;
  }
}

void Grafo::ModificarEtiqueta(Vertice* actual, char etiqueta) {
  actual->etiqueta = etiqueta;
}

char Grafo::Etiqueta(Vertice* actual) {
  return actual->etiqueta;
}

void Grafo::AgregarArista(Vertice* vertice1, Vertice* vertice2, int peso) {
  if (buscarArista(vertice1, vertice2) == nullptr) {
    Arista* nueva1 = new Arista();
    Arista* nueva2 = new Arista();
    nueva1->verticeAdyacente = vertice2;
    nueva1->peso = peso;
    nueva2->verticeAdyacente = vertice1;
    nueva2->peso = peso;
    nueva1->siguienteArista = vertice1->siguienteArista;
    nueva2->siguienteArista = vertice2->siguienteArista;
    vertice1->siguienteArista = nueva1;
    vertice2->siguienteArista = nueva2;
  }
}

void Grafo::EliminarArista(Vertice* vertice1, Vertice* vertice2) {
  borrarArista(vertice1, vertice2);
  borrarArista(vertice2, vertice1);
}

void Grafo::ModificarPeso(Vertice* vertice1, Vertice* vertice2, int peso) {
  buscarArista(vertice1, vertice2)->peso = peso;
  buscarArista(vertice2, vertice1)->peso = peso;
}

int Grafo::Peso(Vertice* vertice1, Vertice* vertice2) {
  return buscarArista(vertice1, vertice2)->peso;
}

Vertice* Grafo::PrimerVertice() {
  return this->inicio;
}

Vertice* Grafo::SiguienteVertice(Vertice* actual) {
  return actual->siguiente;
}

Vertice* Grafo::PrimerVerticeAdyacente(Vertice* actual) {
  Vertice* adyacente = nullptr;
  if (actual->siguienteArista != nullptr) {
    adyacente = actual->siguienteArista->verticeAdyacente;
  }
  return adyacente;
}

Vertice* Grafo::SiguienteVerticeAdyacente(Vertice* actual, Vertice* ultimoAdyacente) {
  Vertice* adyacente = nullptr;
  Arista* arista = buscarArista(actual, ultimoAdyacente)->siguienteArista;
  if (arista != nullptr) {
    adyacente = arista->verticeAdyacente;
  }
  return adyacente;
}

int Grafo::NumVertice() {
  int contador = 0;
  Vertice* actual = this->inicio;
  while (!is_end(actual)) {
    ++contador;
    actual = actual->siguiente;
  }
  return contador;
}

// Privado:

Arista* Grafo::buscarArista(Vertice* vertice1, Vertice* vertice2) {
  Arista* actual = vertice1->siguienteArista;
  while (!is_end(actual) && actual->verticeAdyacente != vertice2) {
    actual = actual->siguienteArista;
  }
  return actual;
}

void Grafo::borrarArista(Vertice* vertice1, Vertice* vertice2) {
  if (vertice1->siguienteArista != nullptr) {
    if (vertice1->siguienteArista->verticeAdyacente == vertice2) {
      Arista* anterior = vertice1->siguienteArista;
      vertice1->siguienteArista = vertice1->siguienteArista->siguienteArista;
      delete anterior;
    } else {
      Arista* actual = vertice1->siguienteArista;
      while (!is_end(actual) && actual->siguienteArista->verticeAdyacente != vertice2) {
        actual = actual->siguienteArista;
      }
      Arista* anterior = actual->siguienteArista;
      actual->siguienteArista = actual->siguienteArista->siguienteArista;
      delete anterior;
    }
  }
}
