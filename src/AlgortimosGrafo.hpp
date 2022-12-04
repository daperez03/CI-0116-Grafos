#ifndef ALGORITMOSGRAFO_HPP
#define ALGORITMOSGRAFO_HPP

#include <vector>
#include <queue>
#include <map>

#include "Common.hpp"

#define Matriz(x) std::vector<std::vector<x>>
#define infinito -1

void Floyd (Grafo& grafo, Matriz(Vertice*)& conexiones
, std::vector<Vertice*>& vertices);
bool Kruskal (Grafo& grafo, std::vector<AristaKruskal>& solMejor);
void ColorearGrafo(Grafo& grafo, ConjuntoDeConjuntos<Vertice*>& solucion);

#endif