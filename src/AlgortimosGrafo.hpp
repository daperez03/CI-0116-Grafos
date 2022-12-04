#ifndef ALGORITMOSGRAFO_HPP
#define ALGORITMOSGRAFO_HPP

#include <vector>
#include <queue>
#include <map>

#include "Common.hpp"

#define Matriz(x) std::vector<std::vector<x>>
#define infinito -1

void Dijkstra(Grafo& grafo, Vertice* vertice, std::map<Vertice*, Vertice*>& solucion);
void Floyd(Grafo& grafo, Matriz(Vertice*)& conexiones
, std::vector<Vertice*>& vertices);
void N_VecesDijkstra(Grafo& grafo, std::map<Vertice*, std::map<Vertice*, Vertice*>>& solucion);
void Prim(Grafo& grafo, std::map<Vertice*, Vertice*>& solucion);
bool Kruskal(Grafo& grafo, std::vector<AristaKruskal>& solMejor);
void ColorearGrafo(Grafo& grafo, ConjuntoDeConjuntos<Vertice*>& solucion);

#endif