#include "Grafo.hpp"
#include <iostream>
#include <vector>
#include "../BERA.hpp"

void CircuitoHamiltonBEP(const int n, Vertice** solActual, Vertice** solMejor
  , Diccionario<Vertice*>& DDvisitados, int& pesoCaminoActual
  , unsigned int& pesoMejorCamino, int i, Grafo& grafo);

void CircuitoHamilton(Grafo& grafo, R11<Vertice*, int>& r11);

Vertice* buscarVertice(Grafo& grafo, char etiqueta) {
  Vertice* vertice = grafo.PrimerVertice();
  bool salida = false;

  while (vertice != verticeNulo && !salida) {
    if (grafo.Etiqueta(vertice) == etiqueta) {
      salida = true;
    } else {
      vertice = grafo.SiguienteVertice(vertice);
    }
  }

  return vertice;
}

void AgregarAristaLibre(char etiquetaV, char etiquetaVAdy
  , int peso, Grafo& grafo) {
  Vertice* vertice = buscarVertice(grafo, etiquetaV);
  Vertice* verticeAdy = buscarVertice(grafo, etiquetaVAdy);
  grafo.AgregarArista(vertice, verticeAdy, peso);
}


int main() {
  Grafo grafo;
  grafo.Crear();
  grafo.AgregarVertice('a');
  grafo.AgregarVertice('b');
  grafo.AgregarVertice('c');
  grafo.AgregarVertice('d');
  grafo.AgregarVertice('e');
  R11<Vertice*, int> r11;
  
  AgregarAristaLibre('a', 'b', 7, grafo);
  AgregarAristaLibre('a', 'c', 6, grafo);
  AgregarAristaLibre('a', 'd', 4, grafo);
  AgregarAristaLibre('a', 'e', 5, grafo);

  AgregarAristaLibre('b', 'c', 9, grafo);
  AgregarAristaLibre('b', 'd', 3, grafo);
  AgregarAristaLibre('b', 'e', 8, grafo);
  
  AgregarAristaLibre('c', 'd', 2, grafo);
  AgregarAristaLibre('c', 'e', 11, grafo);

  AgregarAristaLibre('d', 'e', 10, grafo);

  /*
  AgregarAristaLibre('a', 'b', 1, grafo);
  AgregarAristaLibre('b', 'c', 1, grafo);
  AgregarAristaLibre('c', 'd', 1, grafo);
  AgregarAristaLibre('d', 'e', 1, grafo);
  AgregarAristaLibre('e', 'a', 1, grafo);
  */

  CircuitoHamilton(grafo, r11);

  return 0;
}

void CircuitoHamilton(Grafo& grafo, R11<Vertice*, int>& r11) {
  // Arreglos de las soluciones
  int n = grafo.NumVertice();
  Vertice* solActual[n];
  Vertice* solMejor[n];
  solActual[0] = grafo.PrimerVertice();

  // Enteros de los pesos
  int pesoCaminoActual = 0;
  unsigned int pesoMejorCamino = -1;

  // Llamado del algoritmo recursivo
  #if 0
  CircuitoHamiltonBEP(n, solActual, solMejor, DDvisitados, pesoCaminoActual
    , pesoMejorCamino, 2, grafo);
  #endif
  
  #if 1
  BERA bera(grafo);

  bera.CircuitoHamiltonBERA(grafo.PrimerVertice());
  
  if (bera.encontreSolucion) {
    std::cout << "Peso: " << bera.pesoMejorCamino << std::endl;
  #endif
    for (int i = 0; i < n; ++i) {
      std::cout << grafo.Etiqueta(bera.solMejor[i]) << "->";
    }
    std::cout << grafo.Etiqueta(bera.solMejor[0]) << std::endl;
  } else {
    std::cout << "No hay solucion" << std::endl;
  }
}

void CopiarSolucion(int n, Vertice** solActual, Vertice** solMejor) {
  for (int i = 0; i < n; ++i) {
    solMejor[i] = solActual[i];
  }
}

void CircuitoHamiltonBEP(const int n, Vertice** solActual, Vertice** solMejor
  , Diccionario<Vertice*>& DDvisitados, int& pesoCaminoActual
  , unsigned int& pesoMejorCamino, int i, Grafo& grafo) {
  Vertice* vAdy = grafo.PrimerVerticeAdyacente(solActual[i - 2]);
  DDvisitados.Agregar(solActual[i - 2]);
  while (vAdy != verticeNulo) {
    if (DDvisitados.Pertenece(vAdy) == DDvisitados.NotFound()) {
      solActual[i - 1] = vAdy;
      pesoCaminoActual += grafo.Peso(solActual[i - 2], vAdy);
      if (i == n) {
        if (grafo.ExisteArista(vAdy, solActual[0])) {
          if (pesoMejorCamino > pesoCaminoActual +
            grafo.Peso(vAdy, solActual[0])) {
            pesoMejorCamino = pesoCaminoActual + grafo.Peso(vAdy, solActual[0]);
            CopiarSolucion(n, solActual, solMejor);
          }
        }
      } else {
        CircuitoHamiltonBEP(n, solActual, solMejor , DDvisitados
          , pesoCaminoActual ,pesoMejorCamino ,i + 1,grafo);
      }
      DDvisitados.Sacar(vAdy);
      pesoCaminoActual -= grafo.Peso(solActual[i - 2], vAdy);
    }
    vAdy = grafo.SiguienteVerticeAdyacente(solActual[i - 2], vAdy);
  }
}
