/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./grafo/grafo.h"
#include "./busca/busca.h"
#include "./questao/questao.h"

int main()
{
    Grafo* g = novoGrafo(7);
    addAresta(g, 0, 1, 5);
    addAresta(g, 1, 2, 9);
    addAresta(g, 2, 0, 2);
    addAresta(g, 0, 3, 7);
    addAresta(g, 3, 4, 20);
    addAresta(g, 4, 5, 8);
    addAresta(g, 5, 6, 2);
    addAresta(g, 6, 3, 1);

    printf("\nGrafo original:\n");
    printGrafo(g);
    
    Grafo* agm = novoGrafo(g->V);
    kruskal(g, agm);
    printf("\nArvore geradora minima:\n");
    printGrafo(agm);
    liberaGrafo(g);
    return 0;
}
