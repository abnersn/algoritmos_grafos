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
 * @brief      Resolve o problema dos lutadores por meio de uma modelagem
 *             baseada em grafos. O problema consiste em encontrar dois
 *             subconjuntos de lutadores de modo que os lutadores de um
 *             subconjunto só possam competir com os do outro. O algoritmo
 *             se baseia na busca em largura.
 *
 * @param      g     Grafo que representa os lutadores.
 */
void bonsEMaus(Grafo* g){
    /* O caráter dos lutadores é armazenado em um vetor, com a seguinte
     * representação:
     * 1 => Mau sujeito.
     * 0 => Bom sujeito.
     */
    int carater[g->V];

    /* Vetores para execução da busca em largura. */
    int cor[g->V];
    int pi[g->V];
    int d[g->V];

    Fila* f = novaFila();

    /* Laço para definir o estado inicial dos vértices */
    for(int i = 0; i < g->V; i++){
        carater[i] = 0; // Inicialmente todos são bons sujeitos
        cor[i] = BRANCO;
        pi[i] = -1;
        d[i] = INFINITY;
    }

    /* Definição do primeiro vértice */
    cor[0] = CINZA;
    pi[0] = -1;
    d[0] = 0;

    /* O laço a seguir percorre todos os vértices do grafo para realizar a 
     * classificação.
     */
    for (int i = 0; i < g->V; i++){
        Aresta* aux = g->listaAdj[i].prim; // Aux é uma aresta que sai do vértice i

        /* Laço para percorrer a lista de adjacência de i */
        while (aux != NULL) {
            if(cor[aux->destino] == BRANCO){
                /* O caráter dos vértices adjacentes corresponde ao oposto 
                 * do caráter do vértice atual. Isso faz com que um par de
                 * lutadores sejam sempre de caráters opostos.
                 */
                carater[aux->destino] = !carater[i];
                cor[aux->destino] = CINZA;
                pi[aux->destino] = i;
                d[aux->destino] = d[i] + 1;
                enfileira(f, aux->destino);
            } else if (carater[aux->destino] == carater[i]){
                /* Caso o vértice encontre outro com o caráter já definido e 
                 * idêntico ao seu, não é possível encontrar uma divisão adequada
                 * para os lutadores.
                 */
                printf("Náo eh possivel dividir os bons e maus sujeitos.\n");
                return;
            }
            aux = aux->prox;
        }
        cor[i] = PRETO;
    }

    printf("Os bons e maus sujeitos foram divididos:\n");
    printArray(carater, "carater", g->V);
}