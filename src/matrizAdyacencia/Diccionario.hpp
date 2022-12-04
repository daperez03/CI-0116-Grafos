#ifndef _DICCIONARIO_H_
#define _DICCIONARIO_H_
#include <map>
#include <iterator>

template <class Elemento, class Other = int>
class Diccionario {
 private:
   std::map<Elemento, int> diccionario;
   Other contador = 0;
 public:
   Diccionario() = default;
   ~Diccionario() = default;

   void Agregar(Elemento elemento) {
     diccionario.insert({elemento, contador});
     ++contador;
   }

   auto Pertenece(Elemento key) {
     return diccionario.find(key);
   }

   void Sacar(Elemento key) {
     diccionario.erase(key);
   }

   auto NotFound() {
     return diccionario.end();
   }
};

#endif