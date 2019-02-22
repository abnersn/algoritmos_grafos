/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/

#ifndef FILA_H_
#define FILA_H_

/* Implementação básica de fila em C */

typedef struct fila Fila;
typedef struct filaNo FilaNo;

struct filaNo{
    int valor;
    FilaNo* prox;
};

struct fila{
    int tam;
    FilaNo* prim;
};

Fila* novaFila();

void enfileira(Fila* f, int valor);

FilaNo* retira(Fila* f);

int filaVazia(Fila* f);

void libera(Fila* f);

#endif  // FILA_H_