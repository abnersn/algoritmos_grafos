/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/
#ifndef QUESTAO_H
#define QUESTAO_H

int ehCompleto(Grafo* g);

int ehConexo(Grafo* g);

Grafo* grafoAleatorio(int V, float p);

void getArestas(Grafo* g, Aresta* arestas);

int compara(Aresta* aresta_1, Aresta* aresta_2);

void diametro(g);

int BL_mod(Grafo* T, int v);

Grafo* kruskal(Grafo* g, Grafo* agm);

#endif // QUESTAO_H