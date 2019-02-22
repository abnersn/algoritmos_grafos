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
#include "../grafo/grafo.h"
#include "../fila/fila.h"
#include "../pilha/pilha.h"
#include "../busca/busca.h"
#include "../questao/questao.h"

/**
 * @brief      Algoritmo para calcular o diâmetro de uma árvore com base na
 *             busca em largura.
 *
 * @param      T     Árvore cujo diâmetro será calculado.
 */
void diametro(Grafo* T){
    /* Vetores auxiliares para executar a busca em largura */
    int cor[T->V];
    int d[T->V];

    /* Laço para definir o estado inicial dos vértices */
    for(int i = 0; i < T->V; i++){
        cor[i] = BRANCO;
        d[i] = INFINITY;
    }

    /* Fila da busca em largura */
    Fila* f = novaFila();

    /* Inicialização do primeiro vértice */
    cor[0] = CINZA;
    d[0] = 0;

    /* Vértices extremos do caminho mais longo. Inicialmente seu valor é 
     * negativo, para indicar que são desconhecidos.
     */
    int v1 = -1;
    int v2 = -1;

    /* A seguir, o algoritmo executa uma busca em largura sobre o grafo. O 
     * último vértice visitado é armazenado em v1. Ele é o vértice mais profundo
     * que se pode atingir a partir do vértice 0.
     */
    enfileira(f, 0); // Adiciona vértice 0 à fila.
    while (!filaVazia(f)){
        int vertice = retira(f)->valor; // Retira o vértice da fila
        v1 = vertice; // Atualiza v1
        Aresta* aux = T->listaAdj[vertice].prim; // aux é uma aresta que sai do vértice
        /* Laço para percorrer a lista de adjacência do vertice */
        while (aux != NULL) {
            if(cor[aux->destino] == BRANCO){
                cor[aux->destino] = CINZA;
                d[aux->destino] = d[vertice] + 1;
                enfileira(f, aux->destino);
            }
            aux = aux->prox;
        }
    }
    /* Ao fim do while, v1 terá sido atualizado pela última vez com o último
     * vértice
     */

    /* A segunda busca em largura se iniciará a partir de v1. O vértice mais
     * profundo encontrado nessa busca será armazenado em v2. O caminho mais
     * longo será, portanto, o caminho entre v1 e v2.
     */
    cor[v1] = CINZA;
    d[v1] = 0;

    enfileira(f, v1); // Adiciona vértice 0 à fila.
    while (!filaVazia(f)){
        int vertice = retira(f)->valor; // Retira o vértice da fila
        v2 = vertice;  // Atualiza v2
        Aresta* aux = T->listaAdj[vertice].prim; // aux é uma aresta que sai do vértice
        // Laço para percorrer a lista de adjacência de vertice
        while (aux != NULL) {
            if(cor[aux->destino] == CINZA){
                cor[aux->destino] = BRANCO;
                d[aux->destino] = d[vertice] + 1;
                enfileira(f, aux->destino);
            }
            aux = aux->prox;
        }
    }

    printf("O diametro da arvore e %d, entre os vertices %d e %d\n", d[v2], v1, v2);
}