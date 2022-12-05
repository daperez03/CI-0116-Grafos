#include "Menu.hpp"

Vertice* buscarVertice(Grafo& grafo, char etiqueta) {
  Vertice* vertice = grafo.PrimerVertice();
  bool salida = false;

  while (vertice != nullptr && !salida) {
    if (grafo.Etiqueta(vertice) == etiqueta) {
      salida = true;
    } else {
      vertice = grafo.SiguienteVertice(vertice);
    }
  }

  return vertice;
}

void Crear(Grafo& grafo) {
  grafo.Crear();
  output("Grafo creado");
  output();
}

void Destruir(Grafo& grafo) {
  grafo.Crear();
  output("Grafo destruido");
  output();
}

void AgregarVertice(Grafo& grafo) {
  char etiqueta;
  input<char>("Digite su etiqueta", etiqueta);
  grafo.AgregarVertice(etiqueta);
  output("Vertice agregado");
  output();
}

void EliminarVerice(Grafo& grafo) {
  char etiqueta;
  input<char>("Indique el vertice que desea eliminar", etiqueta);
  grafo.EliminarVertice(buscarVertice(grafo, etiqueta));
  output("Vertice eliminado");
  output();
}

void ModificarEtiqueta(Grafo& grafo) {
  char etiqueta;
  input<char>("Indique el vertice que desea modificar", etiqueta);
  char nuevaEtiqueta;
  input<char>("Indique la nueva etiqueta", nuevaEtiqueta);
  grafo.ModificarEtiqueta(buscarVertice(grafo, etiqueta), nuevaEtiqueta);
  output("Etiqueta modificada");
  output();
}

void Etiqueta(Grafo& grafo) {
  char etiqueta;
  input<char>("?", etiqueta);
  output();
}

void AgregarArista(Grafo& grafo) {
  char vertice1;
  char vertice2;
  int peso;
  input<char>("Indique el primer vertice de conexion  de la arista", vertice1);
  input<char>("Indique el segundo vertice de conexion  de la arista", vertice2);
  input<int>("Indique el peso de la arista", peso);
  grafo.AgregarArista(buscarVertice(grafo, vertice1), buscarVertice(grafo, vertice2), peso);
  output("Arista agregada");
  output();
}

void EliminarArista(Grafo& grafo) {
  char vertice1;
  char vertice2;
  input<char>("Indique el primer vertice de conexion de la arista", vertice1);
  input<char>("Indique el segundo vertice de conexion  de la arista", vertice2);
  grafo.EliminarArista(buscarVertice(grafo, vertice1), buscarVertice(grafo, vertice2));
  output("Arista eliminada");
  output();
}

void ModificarPeso(Grafo& grafo) {
  char vertice1;
  char vertice2;
  int peso;
  input<char>("Indique el primer vertice de conexion  de la arista", vertice1);
  input<char>("Indique el segundo vertice de conexion  de la arista", vertice2);
  input<int>("Indique el nuevo peso de la arista", peso);
  grafo.ModificarPeso(buscarVertice(grafo, vertice1), buscarVertice(grafo, vertice2), peso);
  output("Peso modificado");
  output();
}

void Peso(Grafo& grafo) {
  char vertice1;
  char vertice2;
  input<char>("Indique el primer vertice de conexion  de la arista", vertice1);
  input<char>("Indique el segundo vertice de conexion  de la arista", vertice2);
  int peso = grafo.Peso(buscarVertice(grafo, vertice1), buscarVertice(grafo, vertice2));
  output<int>(peso, "Peso");
  output();
}

void PrimerVertice(Grafo& grafo) {
  Vertice* vertice = grafo.PrimerVertice();
  output("Primer vertice", grafo, vertice);
  output();
}


void SiguienteVertice(Grafo& grafo) {
  char etiqueta;
  input<char>("Indique el vertice anterior", etiqueta);
  Vertice* siguiente = grafo.SiguienteVertice(buscarVertice(grafo, etiqueta));
  output("Siguiente vertice", grafo, siguiente);
  output();
}

void PrimerVerticeAdyacente(Grafo& grafo) {
  char etiqueta;
  input<char>("Indique el vertice principal", etiqueta);
  Vertice* adyacente = grafo.PrimerVerticeAdyacente(buscarVertice(grafo, etiqueta));
  output("Primer vertice adyacente", grafo, adyacente);
  output();
}

void SiguienteVerticeAdyacente(Grafo& grafo) {
  char vertice;
  char ultimoAdyacente;
  input<char>("Indique el vertice principal", vertice);
  input<char>("Indique el ultimo vertice adyacente", ultimoAdyacente);
  Vertice* siguienteAdyacente = grafo.SiguienteVerticeAdyacente(buscarVertice(grafo, vertice), buscarVertice(grafo, ultimoAdyacente));
  output("Siguiente vertice adyacente", grafo, siguienteAdyacente);
  output();
}

void NumeroVertices(Grafo& grafo) {
  output<int>(grafo.NumVertice(), "Numero de Vertices");
  output();
}

void Dijkstra(Grafo& grafo) {
  char vertice;
  input<char>("Indique el vertice de menor costo que desea hallar", vertice);
  output();
  output("\t\t\tDijkstra");
  Vertice* v = buscarVertice(grafo, vertice);
  std::map<Vertice*, Vertice*> solucion;
  Dijkstra(grafo, v, solucion);
  outputDijkstra(grafo, v, solucion);
  output();
}

void Floyd(Grafo& grafo) {
  output("\t\t\tFloyd");
  std::vector<Vertice*> vertices;
  Matriz(Vertice*) solucion;
  Floyd(grafo, solucion, vertices);
  outputFloyd(grafo, solucion, vertices);
  output();
}

void N_VecesDijkstra(Grafo& grafo) {
  output("\t\t\tN veces Dijkstra");
  std::map<Vertice*, std::map<Vertice*, Vertice*>> solucion;
  N_VecesDijkstra(grafo, solucion);
  outputN_VecesDijkstra(grafo, solucion);
}

void Prim(Grafo& grafo) {
  output("\t\t\tPrim");
  std::map<Vertice*, Vertice*> solucion;
  Prim(grafo, solucion);
  outputPrim(grafo, solucion);
  output();
}

void Kruskal(Grafo& grafo) {
  output("\t\t\tKruskal");
  std::vector<AristaKruskal> solucion;
  Kruskal(grafo, solucion);
  outputKruskal(grafo, solucion);
  output();
}

void CHMC_BEP(Grafo& grafo) {
  output("\t\t\tEncontrar el Circuito de Hamilton de Menor Costo(BEP)");
}

void ColorearGrafo(Grafo& grafo) {
  output("\t\t\tColorear Grafo");
  ConjuntoDeConjuntos<Vertice*> solucion;
  ColorearGrafo(grafo, solucion);
  outputColorearGrafo(grafo, solucion);
}

void CHMC_BERA(Grafo& grafo) {
  output("\t\t\ttEncontrar el Circuito de Hamilton de Menor Costo(BERA)");
}

void responderUsuario(int opcion, Grafo& grafo) {
  if (opcion == 1) Crear(grafo);
  if (opcion == 2) Destruir(grafo);
  if (opcion == 3) AgregarVertice(grafo);
  if (opcion == 4) EliminarVerice(grafo);
  if (opcion == 5) ModificarEtiqueta(grafo);
  if (opcion == 6) Etiqueta(grafo);
  if (opcion == 7) AgregarArista(grafo);
  if (opcion == 8) EliminarArista(grafo);
  if (opcion == 9) ModificarPeso(grafo);
  if (opcion == 10) Peso(grafo);
  if (opcion == 11) PrimerVertice(grafo);
  if (opcion == 12) SiguienteVertice(grafo);
  if (opcion == 13) PrimerVerticeAdyacente(grafo);
  if (opcion == 14) SiguienteVerticeAdyacente(grafo);
  if (opcion == 15) NumeroVertices(grafo);
  if (opcion == 16) Dijkstra(grafo);
  if (opcion == 17) Floyd(grafo);
  if (opcion == 18) N_VecesDijkstra(grafo);
  if (opcion == 19) Prim(grafo);
  if (opcion == 20) Kruskal(grafo);
  if (opcion == 21) CHMC_BEP(grafo);
  if (opcion == 22) ColorearGrafo(grafo);
  if (opcion == 23) CHMC_BERA(grafo);
  if (opcion == 24) clearTerminal();
  if (opcion == 25) clearTerminal();
}

int main() {
  clearTerminal();
  int lista = 1;
  int opcion = -1;
  Grafo grafo;
  while (opcion != lista - 1 && !std::cin.eof( )) {
    lista = 1;
    output("\t\t\tMenu del Grafo");
    output("\nOperadores Basicos:");
    output("Crear", lista);
    output("Destruir", lista);
    output("Agregar vertice", lista);
    output("Eliminar vertice", lista);
    output("Modificar etiqueta", lista);
    output("Etiqueta", lista);
    output("Agregar arista", lista);
    output("Eliminar arista", lista);
    output("Modificar peso", lista);
    output("Peso", lista);
    output("Primer vertice", lista);
    output("Siguiente vertice", lista);
    output("Primer vertice adyacente", lista);
    output("Siguiente vertice adyacente", lista);
    output("Numero de vertices", lista);
    output("\nAlgoritmos:");
    output("Dijkstra", lista);
    output("Floyd", lista);
    output("N veces Dijkstra", lista);
    output("Prim", lista);
    output("Kruskal", lista);
    output("Circuito de Hamilton de Menor Costo con BEP", lista);
    output("Colorear un grafo", lista);
    output("Circuito de Hamilton de Menor Costo con BERA", lista);
    output("\nOtros:");
    output("Limpiar termina", lista);
    output("Salir", lista);
    input<int>("Digite su opcion", opcion);
    responderUsuario(opcion, grafo);
  }
}