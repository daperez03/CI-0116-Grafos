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
  , unsigned int& pesoMejorCamino, Vertice* v, Grafo& grafo
  , std::vector<std::vector<int>>& matriz, R11<Vertice*, int>& r11);


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

  CircuitoHamiltonBERA(n, solActual, solMejor, DDvisitados, pesoCaminoActual
    , pesoMejorCamino, grafo.PrimerVertice(), grafo, matriz, r11);
  

  std::cout << "Matriz final" << std::endl;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      std::cout << matriz[i][j] << "  ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < n; ++i) {
    std::cout << grafo.Etiqueta(solMejor[i]) << "->";
  }
  std::cout << grafo.Etiqueta(solMejor[0]) << std::endl;
  std::cout << "Peso: " << pesoMejorCamino << std::endl;
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

bool revisarFila(std::vector<std::vector<int>>& matriz, int i) {
  bool completa = false;
  int contador = 0;
  int contadorTotal = 0;
  for (int j = 0; j < matriz[i].size(); ++j) {
    if (matriz[i][j] == -1) {
      ++contador;
      ++contadorTotal;
    } else if (matriz[i][j] == 1) {
      ++contadorTotal;
    }
  }

  if (contador == 2) {
    completa = true;
    for (int j = 0; j < matriz[i].size(); ++j) {
      if (matriz[i][j] != -1) {
        matriz[i][j] = 0;
        matriz[j][i] = 0;
      }
    }
  } else if (contadorTotal == 2) {
    completa = true;
    for (int j = 0; j < matriz[i].size(); ++j) {
      if (matriz[i][j] == 1) {
        matriz[i][j] = -1;
        matriz[j][i] = -1;
      }
    }
  }
  return completa;
}

int revisarMatriz(std::vector<std::vector<int>>& matriz, int n) {
  int cantidadAristasFijas = 0;
  for (int i = 0; i < n; ++i) {
    int contadorAristas = 0;
    int contadorTotal = 0;
    for (int j = 0; j < n; ++j) {
      if (matriz[i][j] == 1) {
        ++contadorAristas;
        ++contadorTotal;
      } else if(matriz[i][j] != 0) {
        ++contadorTotal;
      }
    }

    if (contadorAristas == 2 && contadorTotal == contadorAristas) {
      for (int j = 0; j < matriz[i].size(); ++j) {
        if (matriz[i][j] == 1) {
          matriz[i][j] = -1;
          matriz[j][i] = -1;
        }
      }
    }
  }
  for (int vuelta = 1; vuelta <= 2; ++vuelta) {
    for (int i = 0; i < n; ++i) {
      if (revisarFila(matriz, i) && vuelta == 2) {
        cantidadAristasFijas += 2;
      }
    }
  }

  return cantidadAristasFijas;
}

int calcularPesoActual(std::vector<std::vector<int>>& matriz, int n
  , R11<Vertice*, int>& r11, Grafo& grafo) {
  int peso = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matriz[i][j] == -1) {
        peso += grafo.Peso(r11.PreImg(i), r11.PreImg(j));
      }
    }
  }
  peso = peso / 2;
  return peso;
}

void CopiarSolucionBERA(int n, std::vector<std::vector<int>>& matriz
  , Vertice** solMejor, R11<Vertice*, int>& r11) {
  Diccionario<Vertice*> DDvisitados;

  solMejor[0] = r11.PreImg(0);
  DDvisitados.Agregar(solMejor[0]);
  int contador = 1;
  int siguienteVertice = 0;
  while (contador < n) {
    for (int j = 0; j < n; ++j) {
      if (matriz[siguienteVertice][j] == -1 &&
        DDvisitados.Pertenece(r11.PreImg(j)) == DDvisitados.NotFound()) {
        DDvisitados.Agregar(r11.PreImg(j));
        solMejor[contador] = r11.PreImg(j);
        siguienteVertice = j;
        j = n;
        ++contador;
      }
    }
  }
}

void CopiarMatrices(int n, std::vector<std::vector<int>>& matriz
  , std::vector<std::vector<int>>& matrizCopia) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matrizCopia[i][j] = matriz[i][j];
    }
  }
}

void CircuitoHamiltonBERA(const int n, Vertice** solActual, Vertice** solMejor
  , Diccionario<Vertice*>& DDvisitados, int& pesoCaminoActual
  , unsigned int& pesoMejorCamino, Vertice* v, Grafo& grafo
  , std::vector<std::vector<int>>& matriz, R11<Vertice*, int>& r11) {
  bool sePodo = false;

  DDvisitados.Agregar(v);
  
  int cotaInferiorLadoIzq = 0;
  int cotaInferiorLadoDer = 0;

  Vertice* vAdy = grafo.PrimerVerticeAdyacente(v);
  while (vAdy != verticeNulo) {
    int ii = r11.Img(v);
    int j = r11.Img(vAdy);
    if (matriz[ii][j] &&
      DDvisitados.Pertenece(vAdy) == DDvisitados.NotFound()) {
      matriz[ii][j] = -1;
      matriz[j][ii] = -1;
      cotaInferiorLadoIzq = calculoCotaInferior(grafo, matriz, r11);
      matriz[ii][j] = 0;
      matriz[j][ii] = 0;
      cotaInferiorLadoDer = calculoCotaInferior(grafo, matriz, r11);
    
      if (cotaInferiorLadoIzq < cotaInferiorLadoDer &&
        cotaInferiorLadoIzq < pesoMejorCamino) {
        std::vector<std::vector<int>> matrizCopia;
        CreacionMatriz(grafo, r11, matrizCopia, n);
        CopiarMatrices(n, matriz, matrizCopia);
        matriz[ii][j] = -1;
        matriz[j][ii] = -1;

        // Antes de cambiar la matriz guardar una copia

        if (revisarFila(matriz, ii)) {
          pesoCaminoActual += grafo.Peso(v, vAdy);
          if (revisarMatriz(matriz, n) == (n * 2)) {
            pesoCaminoActual = calcularPesoActual(matriz, n, r11, grafo);
            if (pesoMejorCamino > pesoCaminoActual +
              grafo.Peso(vAdy, solActual[0])) {
              pesoMejorCamino = pesoCaminoActual;
              sePodo = true;
              CopiarSolucionBERA(n, matriz, solMejor, r11);
            }
          } else {
            CircuitoHamiltonBERA(n, solActual, solMejor, DDvisitados
              , pesoCaminoActual , pesoMejorCamino
              , grafo.SiguienteVertice(v), grafo, matriz, r11);
            sePodo = true;
            if (pesoMejorCamino > cotaInferiorLadoDer) {
               sePodo = false;
              // Matriz muy modificada, hay que revertir los cambios !!
              CopiarMatrices(n, matrizCopia, matriz);
              matriz[ii][j] = 0;
              matriz[j][ii] = 0;
              revisarMatriz(matriz, n);
            }
          }
        } else {
          revisarMatriz(matriz, n);
          pesoCaminoActual += grafo.Peso(v, vAdy);
        }
      } else if (cotaInferiorLadoDer < pesoMejorCamino) {
        std::vector<std::vector<int>> matrizCopia;
        CreacionMatriz(grafo, r11, matrizCopia, n);
        CopiarMatrices(n, matriz, matrizCopia);
        matriz[ii][j] = 0;
        matriz[j][ii] = 0;
        if (revisarFila(matriz, ii)) {
          pesoCaminoActual += grafo.Peso(v, vAdy);
          if (revisarMatriz(matriz, n) == (n * 2)) {
            pesoCaminoActual = calcularPesoActual(matriz, n, r11, grafo);
            if (pesoMejorCamino > pesoCaminoActual +
              grafo.Peso(vAdy, solActual[0])) {
              pesoMejorCamino = pesoCaminoActual;
              sePodo = true;
              CopiarSolucionBERA(n, matriz, solMejor, r11);
            }
          } else {
            CircuitoHamiltonBERA(n, solActual, solMejor, DDvisitados
              , pesoCaminoActual , pesoMejorCamino,
              grafo.SiguienteVertice(v), grafo, matriz, r11);
              sePodo = true;
            if (pesoMejorCamino > cotaInferiorLadoIzq) {
              sePodo = false;
              CopiarMatrices(n, matrizCopia, matriz);
              matriz[ii][j] = -1;
              matriz[j][ii] = -1;
              revisarMatriz(matriz, n);
            }
          }
        } else {
          revisarMatriz(matriz, n);
          pesoCaminoActual += grafo.Peso(v, vAdy);
        }
      }
    }

    if (!sePodo) {
      vAdy = grafo.SiguienteVerticeAdyacente(v, vAdy);
    } else {
      vAdy = verticeNulo;
    }
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

int calculoCotaInferior(Grafo& grafo, std::vector<std::vector<int>>& matriz,
  R11<Vertice*, int>& r11) {
 
  bool unaAristFija = false;
  bool dosAristasFijas = false;
  int aristaFijaUno = 0;
  int aristaFijaDos = 0;
  int cotaInferior = 0;
  int menor = -1;
  int segundoMenor = -1;
  int peso = 0;
  Vertice* v = grafo.PrimerVertice();
  while (v != verticeNulo) {
    Vertice* vAdy = grafo.PrimerVerticeAdyacente(v);
    while (vAdy != verticeNulo) {
      if (matriz[r11.Img(v)][r11.Img(vAdy)]) {
        if (matriz[r11.Img(v)][r11.Img(vAdy)] > 0) {
          peso = grafo.Peso(v, vAdy);
          if (menor == -1 || peso < menor) {
            if (menor != -1) {
              segundoMenor = menor;
              menor = peso;
            } else {
              menor = peso;
            }
          } else if (segundoMenor == -1 || peso < segundoMenor) {
            segundoMenor = peso;
          }
        } else {
          if (!unaAristFija) {
            aristaFijaUno = grafo.Peso(v, vAdy);
            unaAristFija = true;
          } else {
            aristaFijaDos = grafo.Peso(v, vAdy);
            unaAristFija = false;
            dosAristasFijas = true;
          }
        }
      }
      vAdy = grafo.SiguienteVerticeAdyacente(v, vAdy);
    }

    if (!unaAristFija && !dosAristasFijas) {
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
