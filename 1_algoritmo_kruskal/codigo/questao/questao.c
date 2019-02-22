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
 * @brief      Função que implementa o algoritmo de Kruskal, com base na
 *             estrutura UNION-FIND.
 *
 * @param      g     Grafo sobre o qual será calculada a árvore geradora mínima
 * @param      agm   Ponteiro com memória alocada para a agm resultante.
 *
 * @return     Árvore geradora mínima resultante.
 */
Grafo* kruskal(Grafo* g, Grafo* agm){
    int pai[g->V]; // Vetor auxiliar contendo os pais dos vértices no UNION-FIND
    int altura[g->V]; // Vetor auxiliar contendo as alturas.

    /* O laço abaixo realiza o processo de inicialização Make-Set */
    for(int i = 0; i < g->V; i++){
        pai[i] = i; // Os pais de cada vértice são configurados para si mesmos.
        altura[i] = 0; // As alturas dos vértices são zero.
    }

    /* A representação utilizada foi a lista de adjacências. Porém, o código
     * abaixo dispõe as arestas em um vetor, com o auxílio de getArestas.
     * Isso permite a utilização do algoritmo qsort para ordenação dos pesos.
     */
    Aresta arestas[g->E];  // Vetor para armazenar as arestas
    getArestas(g, arestas);  // Transfere arestas do grafo para o vetor
    qsort(arestas, g->E, sizeof(Aresta), compara); // Ordena as arestas com quicksort
    
    /* O laço a seguir percorre o vetor de arestas ordenado e utiliza as funções
     * UNION e FIND para detectar a formação de circuitos. Se um circuito não
     * se formar, a aresta é acrescentada à árvore geradora mínima produzida,
     * conforme determina o algoritmo de Kruskal.
     */
    for(int i = 0; i < g->E; i++){
        int v1 = arestas[i].origem; // Vértice de origem da aresta.
        int v2 = arestas[i].destino; // Vértice de destino da aresta.
        int peso = arestas[i].peso; // Peso da aresta.
        if(FIND(v1, pai, altura) != FIND(v2, pai, altura) && agm->E <= (agm->V - 1)){
            /* Se o resultado dos FINDs for diferente, a aresta pode ser
             * adicionada, pois não forma circuitos.
             */
            addAresta(agm, v1, v2, peso);
            UNION(v1, v2, pai, altura); // Realiza o procedimento de UNION
        }
    }
    return agm;
}


/**
 * @brief      Realiza o procedimento FIND, auxiliar para o algoritmo de
 *             Kruskal.
 *
 * @param[in]  vertice  Vértice que será analisado.
 * @param      pai      Vetor com os representantes de todos os vértices.
 * @param      altura   Vetor com a altura de todos os vértices.
 *
 * @return     Retorna o representante do vértice.
 */
int FIND(int vertice, int* pai, int* altura){
    if(vertice == pai[vertice]){
        return vertice;
    } else {
        return FIND(pai[vertice], pai, altura);
    }
}


/**
 * @brief      Realiza o procedimento UNION, auxiliar para o algoritmo de
 *             Kruskal.
 *
 * @param[in]  vertice1  Primeiro vértice para a união.
 * @param[in]  vertice2  Segundo vértice para a união.
 * @param      pai       Vetor com os representantes de todos os vértices.
 * @param      altura    Vetor com a altura de todos os vértices.
 */
void UNION(int vertice1, int vertice2, int* pai, int* altura){
    int w1 = FIND(vertice1, pai, altura);
    int w2 = FIND(vertice2, pai, altura);

    if (altura[w1] > altura[w2]){
        pai[w2] = w1;
        altura[w1] = altura[w1] + 1;
    } else if (altura[w1] < altura[w2]){
        pai[w1] = w2;
        altura[w2] = altura[w2] + 1;
    } else {
        pai[w1] = w2;
        altura[w1] = altura[w1] + 1;
    }
}

/**
 * @brief      Dispõe as arestas de um grafo na forma de vetor, para facilitar
 *             a ordenação. A função é similar à busca em largura.
 *
 * @param      g        Grafo do qual serão retornadas as arestas.
 * @param      arestas  Vetor para armazenar as arestas.
 */
void getArestas(Grafo* g, Aresta* arestas){
    Fila* fila = novaFila(); // Fila para a busca em largura.
    int* cor[g->V]; // Cores dos vértices
    for(int i = 0; i < g->V; i++){ // Inicialização da busca.
        cor[i] = BRANCO;
    }

    int cont = 0; // Conta quantas arestas já foram adicionadas
    
    enfileira(fila, 0);
    
    while (!filaVazia(fila)){
        int vertice = retira(fila)->valor; // Retira vértice da fila.
        Aresta* aux = g->listaAdj[vertice].prim; // aux é uma aresta que sai do vértice.
        while(aux != NULL){
            if(cor[aux->destino] == BRANCO){
                cor[aux->destino] = CINZA;
                enfileira(fila, aux->destino);
            }
            /* Se a cor do vértice destino da aresta não for preta, significa
             * que ele ainda não foi completamente explorado. Portanto, a aresta
             * ainda não foi visitada e pode ser acrescentada ao vetor.
             * Isso é necessário para evitar que a mesma aresta apareça duas
             * vezes na lista de adjacências.
             */
            if(cor[aux->destino] != PRETO){
                Aresta* aresta = novaAresta(vertice, aux->destino, aux->peso);
                arestas[cont] = *aresta;
                cont++;
            }
            aux = aux->prox; // Prossegue na lista de adjacências.
        }
        cor[vertice] = PRETO;
    }
    return arestas;
}


/**
 * @brief      Função auxiliar para a execução do quick sort.
 *
 * @param      aresta_1  Aresta a ser comparada.
 * @param      aresta_2  Outra aresta a ser comparada.
 *
 * @return     Um número positivo se o peso da aresta 1 for maior que da aresta
 *             2, 0 em caso de igualdade ou um número positivo caso contrário.
 */
int compara(Aresta* aresta_1, Aresta* aresta_2){
    int peso1 = aresta_1->peso;
    int peso2 = aresta_2->peso;
    return peso1 - peso2;
}