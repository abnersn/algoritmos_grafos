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
#include <string.h>
#include "../grafo/grafo.h"
#include "../fila/fila.h"
#include "../pilha/pilha.h"
#include "./busca.h"

/**
 * @brief      Algoritmo de busca em largura com lista de adjacências.
 *
 * @param      g        Grafo sobre o qual a busca será executada
 * @param      inicial  Vértice a partir do qual a busca se iniciará
 */
Resultado BL_adj(Grafo* g, int inicial){
    printf("Iniciando busca em largura.\n");
    int cor[g->V];
    int pi[g->V];
    int d[g->V];

    Fila* f = novaFila();

    // Laço para definir o estado inicial dos vértices
    for(int i = 0; i < g->V; i++){
        cor[i] = BRANCO;
        pi[i] = -1;
        d[i] = INFINITY;
    }

    cor[inicial] = CINZA;
    pi[inicial] = -1;
    d[inicial] = 0;

    printf("Vertices visitados: ");
    enfileira(f, inicial); // Adiciona o vértice inicial à fila.
    while (!filaVazia(f)){
        int vertice = retira(f)->valor;
        printf("%d, ", vertice);

        Aresta* aux = g->listaAdj[vertice].prim;

        // Laço para percorrer a lista de adjacência de vertice
        while (aux != NULL) {
            if(cor[aux->destino] == BRANCO){
                cor[aux->destino] = CINZA;
                pi[aux->destino] = vertice;
                d[aux->destino] = d[vertice] + 1;
                enfileira(f, aux->destino);
            }
            aux = aux->prox;
        }
        cor[vertice] = PRETO;
    }

    printf("\b\b.\nBusca em largura concluída.\n");
    Resultado resultado = setResultado(d, NULL, pi, cor, g->V);
    return resultado;
}


/**
 * @brief      Algoritmo da busca em profundidade com lista de adjacências.
 *
 * @param      g     Grafo sobre o qual a busca será executada.
 */
Resultado BP_adj(Grafo* g){
    printf("Iniciando busca em profundidade\n");
    int cor[g->V];
    int pi[g->V];
    int d[g->V];
    int f[g->V];

    for(int i = 0; i < g->V; i++){
        cor[i] = BRANCO;
        d[i] = INFINITY;
        f[i] = INFINITY;
        pi[i] = -1;
    }

    int tempo = 0;
    printf("Vertices visitados: ");
    for(int i = 0; i < g->V; i++){
        if (cor[i] == BRANCO) {
            BPV(g, cor, pi, d, f, &tempo, i);
        }
    }
    printf("\b\b.\nBusca em profundidade concluida.\n");
    printStatus(d, pi, cor, g->V);
    printArray(f, "f", g->V);

    Resultado resultado = setResultado(d, f, pi, cor, g->V);
    return resultado;
}


/**
 * @brief      Algoritmo auxiliar para a busca em profundidade
 *             com listas de adjacência.
 *
 * @param      g        Grafo sobre o qual a busca está acontecendo.
 * @param      cor      Vetor que contém as cores dos vértices.
 * @param      pi       Vetor que contém os caminhos.
 * @param      d        Vetor que contém os tempos de descoberta.
 * @param      f        Vetor que contém os tempos de finalização.
 * @param      tempo    Tempo atual (por referência).
 * @param[in]  vertice  Vértice que o algoritmo visitará.
 */
void BPV(Grafo* g, int* cor, int* pi, int* d, int* f, int* tempo, int vertice){
    printf("%d, ", vertice);
    cor[vertice] = CINZA;
    *tempo = *tempo + 1;
    d[vertice] = *tempo;
    Aresta* aux = g->listaAdj[vertice].prim;
    while(aux != NULL) {
        if (cor[aux->destino] == BRANCO){
            pi[aux->destino] = vertice;
            BPV(g, cor, pi, d, f, tempo, aux->destino);
        }
        *tempo = *tempo + 1;
        aux = aux->prox;
    }
    f[vertice] = *tempo;
    cor[vertice] = PRETO;
}

/* Funções auxiliares, apenas para exibição */
void printArray(int* array, char* nomeArray, int tam){
    printf("%s[", nomeArray);
    int isCor = strcmp(nomeArray, "cor") == 0;
    for(int i = 0; i < tam; i++){
        if(isCor){
            switch(array[i]){
                case 0:
                    printf("BRANCO, ");
                break;
                case 1:
                    printf("CINZA, ");
                break;
                case 2:
                    printf("PRETO, ");
                break;
            }
        } else{
            printf("%d, ", array[i]);
        }
    }
    printf("\b\b]\n");
}

void printStatus(int* d, int* pi, int* cor, int tam){
    printArray(cor, "cor", tam);
    printArray(d, "d", tam);
    printArray(pi, "pi", tam);
}

void printResultado(Resultado resultado, int tam){
    printArray(resultado.cor, "cor", tam);
    printArray(resultado.pi, "pi", tam);
    printArray(resultado.d, "d", tam);
}

Resultado setResultado(int* d, int* f, int* pi, int* cor, int tam){
    Resultado resultado;
    resultado.d = (int *) malloc(tam * sizeof(int));
    resultado.f = (int *) malloc(tam * sizeof(int));
    resultado.pi = (int *) malloc(tam * sizeof(int));
    resultado.cor = (int *) malloc(tam * sizeof(int));
    for(int i = 0; i < tam; i++){
        resultado.d[i] = d[i];
        if(f != NULL) resultado.f[i] = f[i];
        resultado.pi[i] = pi[i];
        resultado.cor[i] = cor[i];
    }
    return resultado;
}