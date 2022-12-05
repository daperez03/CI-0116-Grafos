#include "BERA.hpp"
#include <iostream>

// Private: 

int BERA::revisarMatriz() {
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
    } else if (contadorAristas == 1 && contadorTotal == 2) {
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
      if (revisarFila(i) && vuelta == 2) {
        cantidadAristasFijas += 2;
      }
    }
  }

  return cantidadAristasFijas;
}

int BERA::calcularPesoActual() {
  int peso = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matriz[i][j] == -1) {
        peso += grafo->Peso(r11.PreImg(i), r11.PreImg(j));
      }
    }
  }
  peso = peso / 2;
  return peso;
}

void BERA::CopiarSolucionBERA() {
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

void BERA::CreacionMatriz() {
  this->matriz.resize(this->n);
  for (int i = 0; i < n; ++i) {
    this->matriz[i].resize(this->n);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      this->matriz[i][j] = 0;
    }
  }

  Vertice* v = this->grafo->PrimerVertice();
  while (v != verticeNulo) {
    Vertice* vAdy = this->grafo->PrimerVerticeAdyacente(v);
    while (vAdy != verticeNulo) {
      int i = this->r11.Img(v);
      int j = this->r11.Img(vAdy);
      this->matriz[i][j] = 1;
      vAdy = this->grafo->SiguienteVerticeAdyacente(v, vAdy);
    }
    v = this->grafo->SiguienteVertice(v);
  }
}

bool BERA::revisarFila(int i) {
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

void BERA::CopiarMatrices(int n, std::vector<std::vector<int>>& matriz
  , std::vector<std::vector<int>>& matrizCopia) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matrizCopia[i][j] = matriz[i][j];
    }
  }
}

int BERA::calculoCotaInferior() {
 
  bool unaAristFija = false;
  bool dosAristasFijas = false;
  int aristaFijaUno = 0;
  int aristaFijaDos = 0;
  int cotaInferior = 0;
  int menor = -1;
  int segundoMenor = -1;
  int peso = 0;
  Vertice* v = grafo->PrimerVertice();
  while (v != verticeNulo) {
    Vertice* vAdy = grafo->PrimerVerticeAdyacente(v);
    while (vAdy != verticeNulo) {
      if (matriz[r11.Img(v)][r11.Img(vAdy)]) {
        if (matriz[r11.Img(v)][r11.Img(vAdy)] > 0) {
          peso = grafo->Peso(v, vAdy);
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
            aristaFijaUno = grafo->Peso(v, vAdy);
            unaAristFija = true;
          } else {
            aristaFijaDos = grafo->Peso(v, vAdy);
            unaAristFija = false;
            dosAristasFijas = true;
          }
        }
      }
      vAdy = grafo->SiguienteVerticeAdyacente(v, vAdy);
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
    v = grafo->SiguienteVertice(v);
    aristaFijaUno = 0;
    unaAristFija = false;
    aristaFijaDos = 0;
    dosAristasFijas = false;
  }

  return cotaInferior;
}

void BERA::CreacionMatrizCopia(std::vector<std::vector<int>>& matrizCopia) {
  matrizCopia.resize(this->n);
  for (int i = 0; i < n; ++i) {
    matrizCopia[i].resize(this->n);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matrizCopia[i][j] = 0;
    }
  }

  Vertice* v = this->grafo->PrimerVertice();
  while (v != verticeNulo) {
    Vertice* vAdy = this->grafo->PrimerVerticeAdyacente(v);
    while (vAdy != verticeNulo) {
      int i = this->r11.Img(v);
      int j = this->r11.Img(vAdy);
      matrizCopia[i][j] = 1;
      vAdy = this->grafo->SiguienteVerticeAdyacente(v, vAdy);
    }
    v = this->grafo->SiguienteVertice(v);
  }
}


// Public:

BERA::BERA(Grafo& grafo) {
  this->grafo = &grafo;
  Vertice* vertice = grafo.PrimerVertice();
  int contador = 0;
  while(vertice != verticeNulo) {
    this->r11.AgregarRelacion(vertice, contador);
    ++contador;
    vertice = grafo.SiguienteVertice(vertice);
  }
  this->n = grafo.NumVertice();
  this->solMejor = new Vertice*[this->n];
  this->solActual = new Vertice*[this->n];
  this->solActual[0] = grafo.PrimerVertice();
  CreacionMatriz();
}

BERA::~BERA() {
  delete this->solMejor;
  delete this->solActual;
}

void BERA::CircuitoHamiltonBERA(Vertice* v) {
  bool sePodo = false;

  DDvisitados.Agregar(v);
  
  int cotaInferiorLadoIzq = 0;
  int cotaInferiorLadoDer = 0;

  Vertice* vAdy = grafo->PrimerVerticeAdyacente(v);
  if (revisarMatriz() != (n * 2)) {
    while (vAdy != verticeNulo) {
      int ii = r11.Img(v);
      int j = r11.Img(vAdy);
      if (matriz[ii][j] &&
        DDvisitados.Pertenece(vAdy) == DDvisitados.NotFound()) {
        matriz[ii][j] = -1;
        matriz[j][ii] = -1;
        cotaInferiorLadoIzq = calculoCotaInferior();
        matriz[ii][j] = 0;
        matriz[j][ii] = 0;
        cotaInferiorLadoDer = calculoCotaInferior();
      
        if (cotaInferiorLadoIzq < cotaInferiorLadoDer &&
          cotaInferiorLadoIzq < pesoMejorCamino) {
          std::vector<std::vector<int>> matrizCopia;
          CreacionMatrizCopia(matrizCopia);
          CopiarMatrices(n, matriz, matrizCopia);
          matriz[ii][j] = -1;
          matriz[j][ii] = -1;
  
          // Antes de cambiar la matriz guardar una copia
  
          if (revisarFila(ii)) {
            pesoCaminoActual += grafo->Peso(v, vAdy);
            if (revisarMatriz() == (n * 2)) {
              pesoCaminoActual = calcularPesoActual();
              if (pesoMejorCamino > pesoCaminoActual +
                grafo->Peso(vAdy, solActual[0])) {
                pesoMejorCamino = pesoCaminoActual;
                sePodo = true;
                encontreSolucion = true;
                CopiarSolucionBERA();
              }
            } else {
              CircuitoHamiltonBERA(grafo->SiguienteVertice(v));
              sePodo = true;
              if (pesoMejorCamino > cotaInferiorLadoDer) {
                 sePodo = false;
                // Matriz muy modificada, hay que revertir los cambios !!
                CopiarMatrices(n, matrizCopia, matriz);
                matriz[ii][j] = 0;
                matriz[j][ii] = 0;
                revisarMatriz();
              }
            }
          } else {
            revisarMatriz();
            pesoCaminoActual += grafo->Peso(v, vAdy);
          }
        } else if (cotaInferiorLadoDer < pesoMejorCamino) {
          std::vector<std::vector<int>> matrizCopia;
          CreacionMatrizCopia(matrizCopia);
          CopiarMatrices(n, matriz, matrizCopia);
          matriz[ii][j] = 0;
          matriz[j][ii] = 0;
          if (revisarFila(ii)) {
            pesoCaminoActual += grafo->Peso(v, vAdy);
            if (revisarMatriz() == (n * 2)) {
              pesoCaminoActual = calcularPesoActual();
              if (pesoMejorCamino > pesoCaminoActual +
                grafo->Peso(vAdy, solActual[0])) {
                pesoMejorCamino = pesoCaminoActual;
                sePodo = true;
                encontreSolucion = true;
                CopiarSolucionBERA();
              }
            } else {
              CircuitoHamiltonBERA(grafo->SiguienteVertice(v));
               sePodo = true;
              if (pesoMejorCamino > cotaInferiorLadoIzq) {
                sePodo = false;
                CopiarMatrices(n, matrizCopia, matriz);
                matriz[ii][j] = -1;
                matriz[j][ii] = -1;
                revisarMatriz();
              }
            }
          } else {
            revisarMatriz();
            pesoCaminoActual += grafo->Peso(v, vAdy);
          }
        }
      }
  
      if (!sePodo) {
        vAdy = grafo->SiguienteVerticeAdyacente(v, vAdy);
      } else {
        vAdy = verticeNulo;
      }
    }
  } else {
    pesoCaminoActual = calcularPesoActual();
    if (pesoMejorCamino > pesoCaminoActual +
      grafo->Peso(vAdy, solActual[0])) {
      pesoMejorCamino = pesoCaminoActual;
      sePodo = true;
      encontreSolucion = true;
      CopiarSolucionBERA();
    }
  }
}
