/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/
#ifndef PILHA_H
#define PILHA_H

/* Implementação básica de pilhas em C */

#include <stdio.h>
#include <stdlib.h>
#include "./pilha.h"

Pilha* novaPilha(){
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->prim = NULL;
    pilha->tam = 0;
    return pilha;
}

void push(Pilha* f, int valor){
    PilhaNo* elemento = (PilhaNo*) malloc(sizeof(PilhaNo));
    elemento->valor = valor;
    elemento->prox = f->prim;
    f->prim = elemento;
    f->tam = f->tam + 1;
}

PilhaNo* pop(Pilha* f){
    if(f-> tam == 0){
        printf("Pilha vazia.");
        return NULL;
    }
    PilhaNo* elemento = f->prim;
    f->prim = f->prim->prox;
    f->tam = f->tam - 1;
    return elemento;
}

void printPilha(Pilha* p){
    PilhaNo* aux = p->prim;
    while(aux != NULL){
        printf("%d\n", aux->valor);
        aux = aux->prox;
    }
}

#endif