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
#include "./grafo.h"

/* Funções básicas para gerenciamento do grafo */

Aresta* novaAresta(int origem, int destino, int peso){
    Aresta* novoNo = (Aresta*) malloc(sizeof(Aresta));
    novoNo->origem = origem;
    novoNo->destino = destino;
    novoNo->peso = peso;
    novoNo->prox = NULL;
    return novoNo;
}

/**
 * @brief      Cria um novo grafo vazio.
 *
 * @param[in]  V     Número de vértices a serem criados.
 *
 * @return     Ponteiro para o grafo na memória.
 */
Grafo* novoGrafo(int V){
    Grafo* novoGrafo = (Grafo*) malloc(sizeof(Grafo));
    novoGrafo->V = V;
    novoGrafo->E = 0;
    novoGrafo->listaAdj = (ListaAdj*) malloc(V * sizeof(ListaAdj));
    for(int i = 0; i < V; i++){
        novoGrafo->listaAdj->prim = NULL;
    }
    return novoGrafo;
}

/**
 * @brief      Adiciona uma nova Aresta direcionada ao grafo.
 *
 * @param      g        Grafo ao qual a Aresta será adicionada.
 * @param[in]  origem   Vértice de origem.
 * @param[in]  destino  Vértice de destino.
 * @param[in]  peso     Peso da Aresta.
 */
void addArestaDir(Grafo* g, int origem, int destino, int peso){
    Aresta* novoNo = novaAresta(origem, destino, peso);
    novoNo->prox = g->listaAdj[origem].prim;
    g->listaAdj[origem].prim = (Aresta*) novoNo;
    g->E = g->E + 1;
}


/**
 * @brief      Adiciona uma Aresta não direcionada ao grafo por meio de
 *             duas arestas direcionadas em sentidos opostos.
 *
 * @param      g         Grafo ao qual a Aresta será adicionada.
 * @param[in]  origem  Um dos extremos ao qual a Aresta será ligada.
 * @param[in]  destino  Outro extremo da Aresta.
 * @param[in]  peso      Peso da Aresta.
 */
void addAresta(Grafo* g, int origem, int destino, int peso){
    addArestaDir(g, origem, destino, peso);
    addArestaDir(g, destino, origem, peso);
    g->E = g->E - 1;  // O contador de arestas incrementará duas vezes
}


/**
 * @brief      Remove uma Aresta do grafo.
 *
 * @param      g        Grafo do qual a Aresta será removida.
 * @param[in]  origem   Vértice de origem.
 * @param[in]  destino  Vértice de destino.
 */
void removeAresta(Grafo* g, int origem, int destino){
    Aresta* aux = g->listaAdj[origem].prim;
    if(aux->destino == destino){
        g->listaAdj[origem].prim = aux->prox;
        free(aux);
        return;
    }
    while(aux->prox != NULL){
        if(aux->prox->origem == destino){
            Aresta* aux2 = aux->prox->prox;
            free(aux->prox);
            aux->prox = aux2;
            return;
        }
    }
}

/**
 * @brief      Libera espaço na memória alocado por uma lista.
 *
 * @param      noLista  Nó da Lista a ser liberada.
 */
void liberaLista(Aresta* noLista){
    if(noLista->prox == NULL){
        free(noLista);
    } else {
        liberaLista(noLista->prox);
    }
}

/**
 * @brief      Libera espaçõ na memória alocado para um grafo.
 *
 * @param      g     Grafo a ser liberado.
 */
void liberaGrafo(Grafo* g){
    for(int i = 0; i < g->V; i++){
        liberaLista(g->listaAdj[i].prim);
    }
    free(g);
}

/**
 * @brief      Imprime um grafo na forma de lista de adjacência.
 *
 * @param      g     Grafo a ser impresso.
 */
void printGrafo(Grafo* g){
    printf("==== LISTA DE ADJACENCIA ====\n");
    for(int i = 0; i < g->V; i++){
        printf("vertice %d: ", i);
        Aresta* aux = g->listaAdj[i].prim;
        while (aux != NULL){
            printf("%d -> ", aux->destino);
            aux = aux->prox;
        }
        printf("||\n");
    }
}

/**
 * @brief      Função auxiliar para imprimir uma aresta.
 *
 * @param[in]  a     Aresta a ser impressa.
 */
void printAresta(Aresta a){
    int origem = a.origem;
    int destino = a.destino;
    int peso = a.peso; 
    printf("Aresta (%d, %d) peso %d.\n", origem, destino, peso);
}