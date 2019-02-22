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
    addAresta(g, 0, 1, 1);
    addAresta(g, 0, 2, 1);
    addAresta(g, 1, 3, 1);
    addAresta(g, 1, 4, 1);
    addAresta(g, 1, 5, 1);
    addAresta(g, 4, 6, 1);
    printGrafo(g);
    diametro(g);
    liberaGrafo(g);
    return 0;
}
