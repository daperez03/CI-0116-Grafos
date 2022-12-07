#ifndef COMMONHPP
#define COMMONHPP
#include <set>
#include <vector>
#include "Grafo.hpp"

class Vertice;

typedef struct {
  Vertice* salida;
  Vertice* llegada;
  int peso;
} AristaKruskal;

class OrderOfPriority {
 public:
  OrderOfPriority() = default;
  bool operator() (const AristaKruskal& arista1, const AristaKruskal& arista2) const {
    return arista1.peso > arista1.peso;
  }
};

template <class T>
class ConjuntoDeConjuntos {
 private:
  std::vector<std::set<T>> setOfSets;
 public:
  void AgregarSubConjunto(T elemento) {
    std::set<T> nuevo;
    nuevo.insert(elemento);
    setOfSets.push_back(nuevo);
  }

  int buscarElemento(T elemento) {
    int identificador = -1;
    auto notFound = setOfSets[0].end();

    for (int i = 0; i < this->setOfSets.capacity(); ++i) {
      auto itSet = this->setOfSets[i].find(elemento);
      if (itSet != notFound) {
        identificador = i;
        break;
      }
    }
    return identificador;
  }

  void unir(int identificador1, int identificador2) {
    this->setOfSets[identificador1].merge(setOfSets[identificador2]);
    this->setOfSets[identificador2].clear();
  }

  void agregarElemento(int identificador, T elemento) {
    this->setOfSets[identificador].insert(elemento);
  }

  void borrarElemento(int identificador, T elemento) {
    this->setOfSets[identificador].erase(elemento);
  }

  bool disjuntos(int identificador, std::set<T> conjunto1) {
    bool esDisjunto = false;
    if (this->setOfSets.size() > identificador) {
      std::set<T> conjunto2 = this->setOfSets[identificador];
      conjunto1.merge(conjunto2);
      esDisjunto = conjunto2.size() == 0;
    } else {
      esDisjunto = true;
    }
    return esDisjunto;
  }

  int count() {
    return this->setOfSets.size();
  }

  int emptySets() {
    int emptySets = 0;
    for (int i = 0; i < setOfSets.capacity(); ++i) {
      if(this->setOfSets[i].empty()) ++emptySets;
    }
    return emptySets;
  }
};

template <class T>
class Par {
 public:
  Par(T objeto1, T objeto2) : objeto1(objeto1), objeto2(objeto2){}
  T objeto1;
  T objeto2;
  bool operator==(const Par& comparacion) {
    return comparacion.objeto1 == this->objeto2
      && comparacion.objeto2 == this->objeto1;
  }
};

template <class T>
bool Existe(std::vector<T> vector, T objeto) {
  for (int i = 0; i < vector.capacity(); ++i) {
    if (vector[i] == objeto) {
      return true;
    }
  }
  return false;
}

#endif
