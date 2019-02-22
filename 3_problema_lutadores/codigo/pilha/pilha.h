/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/

#ifndef PILHA_H_
#define PILHA_H_

/* Implementação básica de pilha em C */

typedef struct pilha Pilha;
typedef struct pilhaNo PilhaNo;

struct pilhaNo{
    int valor;
    PilhaNo* prox;
};

struct pilha{
    int tam;
    PilhaNo* prim;
};

Pilha* novaPilha();

void push(Pilha* f, int valor);

PilhaNo* pop(Pilha* f);

void printPilha(Pilha* p);

#endif PILHA_H_
