#ifndef _BERA_HPP_
#define _BERA_HPP_

#include "Diccionario.hpp"
#include "RII.hpp"
#include "Grafo.hpp"
#include <vector>

class BERA {
 private:
   Grafo* grafo;
   R11<Vertice*, int> r11;
   int n;
   Vertice** solActual;
   std::vector<std::vector<int>> matriz;
   int pesoCaminoActual = 0;
   Diccionario<Vertice*> DDvisitados;

   int calculoCotaInferior();

   void CreacionMatriz();

    int revisarMatriz();

    int calcularPesoActual();
    
    void CopiarSolucionBERA();
    
    bool revisarFila(int);

    void CopiarMatrices(int, std::vector<std::vector<int>>&
      , std::vector<std::vector<int>>&);

    void CreacionMatrizCopia(std::vector<std::vector<int>>&);

 public:
   Vertice** solMejor;
   unsigned int pesoMejorCamino = -1;
   bool encontreSolucion = false;

   BERA(Grafo&);

   ~BERA();

   void CircuitoHamiltonBERA(Vertice*);
};

#endif