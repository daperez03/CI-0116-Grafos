#include "Grafo.hpp"

void Grafo::Crear() {
  this->ultimo = -1;
}

void Grafo::Destruir() {
  this->ultimo = -1;
}

Vertice* Grafo::AgregarVertice(char etiqueta) {
  ++this->ultimo;
  Vertice* vertice = &this->vertices[this->ultimo];
  this->vertices[this->ultimo].etiqueta = etiqueta;
  this->vertices[this->ultimo].indiceVertice = this->ultimo;
  return vertice;
}

void Grafo::EliminarVertice(Vertice* actual) {
  int indiceVertice = actual->indiceVertice;
  for (int indiceVerticeAdelante = actual->indiceVertice + 1;
    indiceVerticeAdelante <= this->ultimo; ++indiceVertice) {
    this->vertices[indiceVertice] = this->vertices[indiceVerticeAdelante];
  }
  this->ultimo -= 1;
}

void Grafo::ModificarEtiqueta(Vertice* actual, char etiqueta) {
  int indiceVertice = actual->indiceVertice;
  this->vertices[indiceVertice].etiqueta = etiqueta;
}

char Grafo::Etiqueta(Vertice* actual) {
  return this->vertices[actual->indiceVertice].etiqueta;
}

void Grafo::AgregarArista(Vertice* vertice1, Vertice* vertice2, int peso) {
  int indiceVertice1 = vertice1->indiceVertice;
  int indiceVertice2 = vertice2->indiceVertice;
  this->aristas[indiceVertice1][indiceVertice2].existeArista = true;
  this->aristas[indiceVertice1][indiceVertice2].peso = peso;
  this->aristas[indiceVertice2][indiceVertice1].existeArista = true;
  this->aristas[indiceVertice2][indiceVertice1].peso = peso;
}

void Grafo::EliminarArista(Vertice* vertice1, Vertice* vertice2) {
  int indiceVertice1 = vertice1->indiceVertice;
  int indiceVertice2 = vertice2->indiceVertice;
  this->aristas[indiceVertice1][indiceVertice2].existeArista = false;
  this->aristas[indiceVertice2][indiceVertice1].existeArista = false;
}
void Grafo::ModificarPeso(Vertice* vertice1, Vertice* vertice2, int peso) {
  int indiceVertice1 = vertice1->indiceVertice;
  int indiceVertice2 = vertice2->indiceVertice;
  this->aristas[indiceVertice1][indiceVertice2].peso = peso;
}

int Grafo::Peso(Vertice* vertice1, Vertice* vertice2) {
  int indiceVertice1 = vertice1->indiceVertice;
  int indiceVertice2 = vertice2->indiceVertice;
  return (this->aristas[indiceVertice1][indiceVertice2]).peso;
}

Vertice* Grafo::PrimerVertice() {
  Vertice* primerVertice = nullptr;
  if (this->ultimo != -1) {
    primerVertice = &this->vertices[0];
  }
  return primerVertice;
}

Vertice* Grafo::SiguienteVertice(Vertice* actual) {
  Vertice* siguienteVertice = nullptr;
  int indiceVertice = actual->indiceVertice;
  if (indiceVertice < this->ultimo) {
    siguienteVertice =  &this->vertices[indiceVertice + 1];
  }

  return siguienteVertice;
}

Vertice* Grafo::PrimerVerticeAdyacente(Vertice* actual) {
  Vertice* siguienteVertice = nullptr;
  bool salida = false;
  int indiceVertice = actual->indiceVertice;
  for (int indiceArista = 0; indiceArista <= this->ultimo && !salida; 
    ++indiceArista) {
    if (this->aristas[indiceVertice][indiceArista].existeArista) {
      siguienteVertice = &this->vertices[indiceArista];
      salida = true;
    }
  }

  return siguienteVertice;
}

Vertice* Grafo::SiguienteVerticeAdyacente(Vertice* actual
  , Vertice* ultimoAdyacente) {
  Vertice* siguienteVertice = nullptr;
  bool salida = false;
  int indiceVertice = actual->indiceVertice;
  int indiceVerticeAdyacente = ultimoAdyacente->indiceVertice;

  for (int indiceArista = indiceVerticeAdyacente + 1;
    indiceArista <= this->ultimo && !salida; ++indiceArista) {
    if (this->aristas[indiceVertice][indiceArista].existeArista) {
      siguienteVertice = &this->vertices[indiceArista];
      salida = true;
    }
  }

  return siguienteVertice;
}

int Grafo::NumVertice() {
  return this->ultimo + 1;
}

bool Grafo::ExisteArista(Vertice* v, Vertice* vAdy) {
  return (this->aristas[v->indiceVertice][vAdy->indiceVertice]).existeArista;
}
