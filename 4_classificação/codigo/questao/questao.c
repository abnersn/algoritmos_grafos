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
 * @brief      Classifica um grafo em completo, conexo ou árvore.
 *
 * @param      g     Grafo a ser classificado.
 */
void classifica(Grafo* g){

    /* Um grafo G = (V, E) é completo se, e somente se,
     * |E| = (|V| * (|V| - 1))/2.
     * O trecho de código abaixo verifica essa propriedade.
     */
    int numArestas = (g->V * (g->V - 1)) / 2;
    if (g->E == numArestas){
        printf("O grafo eh completo.\n");
        return;
    }

    /* Se o grafo não for completo, então uma busca em largura permite tanto
     * identificar ciclos quanto verificar se o grafo é conexo. O restante da
     * função efetua uma busca em largura sobre o grafo.
     */
    int cor[g->V];
    int pi[g->V];

    int temCiclos = 0; // Flag para indicar se o grafo tem ciclos.
    int ehConexo = 1;  // Flag para indicar se o grafo é conexo. 

    Fila* f = novaFila();

    /* Laço para definir o estado inicial dos vértices */
    for(int i = 0; i < g->V; i++){
        cor[i] = BRANCO; // Cor BRANCO indica vértice não explorado
        pi[i] = -1; // Indica que os caminhos ainda não foram definidos.
    }

    cor[0] = CINZA;
    pi[0] = -1;

    enfileira(f, 0); // Adiciona primeiro vértice à fila.

    /* O laço abaixo executa sobre a fila associada à busca em largura. */
    while (!filaVazia(f)){
        int vertice = retira(f)->valor; // Retira primeiro vértice da fila.

        /* Laço para percorrer a lista de adjacências do vértice. */
        Aresta* aux = g->listaAdj[vertice].prim; // aux é uma aresta que sai do vértice
        while (aux != NULL) {
            /* Procedimento normal da busca em largura. */
            if(cor[aux->destino] == BRANCO){
                cor[aux->destino] = CINZA;
                pi[aux->destino] = vertice;
                enfileira(f, aux->destino);
            } else if (aux->destino != pi[vertice]){
                /* Se o algoritmo encontrar um vértice não BRANCO que não seja
                 * o pai do vértice, é porque
                 * existem ciclos */
                temCiclos = 1;
            }
            aux = aux->prox; // Próxima aresta da lista de adjacências
        }
        cor[vertice] = PRETO; // Pinta vertice de preto para indicar fim da exploração.
    }

    /* Se, ao fim da busca em largura, ainda houver vértices brancos, é porque
     * não foi possível alcançá-los. Logo, há uma desconexão no grafo. O laço
     * abaixo verifica isso.
     */ 
    for (int i = 0; i < g->V; i++){
        if(cor[i] == BRANCO){
            ehConexo = 0; // Indica que o grafo não é conexo.
        }
    }

    /* O código abaixo imprime o resultado. Se o grafo for conexo e acíclico,
     * então é uma árvore. Se for conexo, mas não for acíclico, então é apenas uma
     * árvore simples. Caso contrário, o grafo não atende nenhuma das
     * classificações
     */
    if(ehConexo){
        if(!temCiclos){
            printf("O grafo e uma arvore.\n");
            return;
        }
        printf("O grafo e conexo.\n");
        return;
    }
    printf("O grafo não e completo, nem conexo, nem arvore.\n");
    return;
}
