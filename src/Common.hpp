#ifndef COMMONHPP
#define COMMONHPP
#include <set>
#include <vector>

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
    setOfSets.resize(setOfSets.capacity() + 1);
    setOfSets[setOfSets.capacity() - 1].insert(elemento);
  }
  std::set<T>* buscarElemento(T elemento) {
    std::set<T>* conjunto = nullptr;
    for (int i = 0; i < setOfSets.capacity(); ++i) {
      if (setOfSets[i].contains(elemento)) {
        conjunto = &setOfSets[i];
        break;
      }
    }
    return conjunto;
  }
  void unir(std::set<T>* conjunto1, std::set<T>* conjunto2) {
    conjunto1->merge(*conjunto2);
    conjunto2->clear();
  }
};

template <class T>
class Par {
 public:
  Par(T objeto1, T objeto2) : objeto1(objeto1), objeto2(objeto2){}
  T objeto1;
  T objeto2;
  bool operator==(const Par& comparacion) {
    return comparacion.objeto1 == this->objeto1 || comparacion.objeto1 == this->objeto2
      && comparacion.objeto2 == this->objeto1 || comparacion.objeto2 == this->objeto2;
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
