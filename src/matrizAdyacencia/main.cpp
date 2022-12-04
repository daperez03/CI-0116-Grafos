#include "Grafo.hpp"
#include <iostream>
#include <vector>
#include "RII.hpp"
#include "Diccionario.hpp"

#define verticeNulo nullptr

void CircuitoHamiltonBEP(const int n, Vertice** solActual, Vertice** solMejor
  , Diccionario<Vertice*>& DDvisitados, int& pesoCaminoActual
  , unsigned int& pesoMejorCamino, int i, Grafo& grafo);

void CreacionMatriz(Grafo& grafo, R11<Vertice*, int>& r11
  , std::vector<std::vector<int>>& matriz, const int n);

void CircuitoHamilton(Grafo& grafo, R11<Vertice*, int>& r11);

int calculoCotaInferior(Grafo& grafo, std::vector<std::vector<int>>& matriz,
  R11<Vertice*, int>& r11);

void CircuitoHamiltonBERA(const int n, Vertice** solActual, Vertice** solMejor
  , Diccionario<Vertice*>& DDvisitados, int& pesoCaminoActual
  , unsigned int& pesoMejorCamino, int i, Grafo& grafo);


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

  Vertice* vertice = grafo.PrimerVertice();
  int contador = 0;
  while(vertice != verticeNulo) {
    r11.AgregarRelacion(vertice, contador);
    ++contador;
    vertice = grafo.SiguienteVertice(vertice);
  }

  AgregarAristaLibre('a', 'b', 15, grafo);
  AgregarAristaLibre('a', 'c', 1, grafo);
  AgregarAristaLibre('a', 'd', 7, grafo);
  AgregarAristaLibre('a', 'e', 10, grafo);

  AgregarAristaLibre('b', 'c', 3, grafo);
  AgregarAristaLibre('b', 'd', 12, grafo);
  AgregarAristaLibre('b', 'e', 8, grafo);
  
  AgregarAristaLibre('c', 'd', 4, grafo);
  AgregarAristaLibre('c', 'e', 9, grafo);

  AgregarAristaLibre('d', 'e', 5, grafo);
  
  Vertice* vAdy = grafo.PrimerVerticeAdyacente(buscarVertice(grafo, 'a'));
  std::cout << grafo.Etiqueta(vAdy) << std::endl;
  Diccionario<Vertice*> DDvisitados;
  if (DDvisitados.Pertenece(buscarVertice(grafo, 'a')) ==
    DDvisitados.NotFound()) {
    std::cout << "Funciono" << std::endl;
  }

  CircuitoHamilton(grafo, r11);

  return 0;
}

typedef struct nodo {
  int cotaInferior = 0;
} Nodo_t;

void CircuitoHamilton(Grafo& grafo, R11<Vertice*, int>& r11) {
  // Arreglos de las soluciones
  int n = grafo.NumVertice();
  Vertice* solActual[n];
  Vertice* solMejor[n];
  solActual[0] = grafo.PrimerVertice();

  // Enteros de los pesos
  int pesoCaminoActual = 0;
  unsigned int pesoMejorCamino = -1;

  // Creacion de los diccionarios
  Diccionario<Vertice*> DDvisitados;

  // Llamado del algoritmo recursivo
  #if 0
  CircuitoHamiltonBEP(n, solActual, solMejor, DDvisitados, pesoCaminoActual
    , pesoMejorCamino, 2, grafo);
  #endif

  std::vector<std::vector<int>> matriz;
  CreacionMatriz(grafo, r11, matriz, n);
  std::cout << calculoCotaInferior(grafo, matriz, r11) << std::endl;

  // CircuitoHamiltonBERA(n, solActual, solMejor, DDvisitados, pesoCaminoActual
  //   , pesoMejorCamino, 2, grafo);

  /*
  for (int i = 0; i < n; ++i) {
    std::cout << grafo.Etiqueta(solMejor[i]) << "->";
  }
  std::cout << grafo.Etiqueta(solMejor[0]) << std::endl;
  std::cout << "Peso: " << pesoMejorCamino << std::endl;
  */
}

void CreacionMatriz(Grafo& grafo, R11<Vertice*, int>& r11
  , std::vector<std::vector<int>>& matriz, const int n) {
  matriz.resize(n);
  for (int i = 0; i < n; ++i) {
    matriz[i].resize(n);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matriz[i][j] = 0;
    }
  }

  Vertice* v = grafo.PrimerVertice();
  while (v != verticeNulo) {
    Vertice* vAdy = grafo.PrimerVerticeAdyacente(v);
    while (vAdy != verticeNulo) {
      int i = r11.Img(v);
      int j = r11.Img(vAdy);
      matriz[i][j] = 1;
      vAdy = grafo.SiguienteVerticeAdyacente(v, vAdy);
    }
    v = grafo.SiguienteVertice(v);
  }
}

/*
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
*/

/*
void CircuitoHamiltonBERA(const int n, Vertice** solActual, Vertice** solMejor
  , Diccionario<Vertice*>& DDvisitados, int& pesoCaminoActual
  , unsigned int& pesoMejorCamino, int i, Grafo& grafo) {
    std::cout << "Calcular cota inferior" << std::endl;
    int cotaInferior = primeraCotaInferior(grafo);

    std::cout << cotaInferior << std::endl;
}
*/

int calculoCotaInferior(Grafo& grafo, std::vector<std::vector<int>>& matriz,
  R11<Vertice*, int>& r11) {
  bool unaAristFija = false;
  bool dosAristasFijas = false;
  int aristaFijaUno = 0;
  int aristaFijaDos = 0;
  int cotaInferior = 0;
  unsigned int menor = -1;
  unsigned int segundoMenor = -1;
  Vertice* v = grafo.PrimerVertice();
  while (v != verticeNulo) {
    Vertice* vAdy = grafo.PrimerVerticeAdyacente(v);
    while (vAdy != verticeNulo) {
      if (matriz[r11.Img(v)][r11.Img(vAdy)]) {
        if (matriz[r11.Img(v)][r11.Img(vAdy)] > 0) {
          if (grafo.Peso(v, vAdy) < menor) {
            menor = grafo.Peso(v, vAdy);
          } else if (grafo.Peso(v, vAdy) < segundoMenor) {
            segundoMenor = grafo.Peso(v, vAdy);
          }
        } else {
          if (!unaAristFija) {
            aristaFijaUno = grafo.Peso(v, vAdy);
            unaAristFija = true;
          } else {
            aristaFijaDos = grafo.Peso(v, vAdy);
            dosAristasFijas = true;
          }
        }
      }
      vAdy = grafo.SiguienteVerticeAdyacente(v, vAdy);
    }
    if (!unaAristFija) {
      cotaInferior += (menor + segundoMenor);
    } else {
      if (unaAristFija) {
        cotaInferior += (menor + aristaFijaUno);
      } else {
        cotaInferior += (aristaFijaUno + aristaFijaDos);
      }
    }
    menor = -1;
    segundoMenor = -1;
    v = grafo.SiguienteVertice(v);
    aristaFijaUno = 0;
    unaAristFija = false;
    aristaFijaDos = 0;
    dosAristasFijas = false;
  }

  return cotaInferior;
}