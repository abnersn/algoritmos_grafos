/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/
#ifndef BUSCA_H_
#define BUSCA_H_

#define BRANCO 0
#define CINZA 1
#define PRETO 2

typedef struct resultado Resultado;

// Estrutura para armazenar o resultado
struct resultado
{
    int* cor;
    int* pi;
    int* f;
    int* d;
};

Resultado BL_adj(Grafo* g, int inicial);

Resultado BP_adj(Grafo* g);

void BPV(Grafo* g, int* cor, int* pi, int* d, int* f, int* tempo, int origem);

/* Funções auxiliares, apenas para exibição */
void printArray(int* array, char* nomeArray, int tam);

void printStatus(int* d, int* pi, int* cor, int tam);

void printResultado(Resultado resultado, int tam);

Resultado setResultado(int* d, int* f, int* pi, int* cor, int tam);

#endif  // BUSCA_H_
