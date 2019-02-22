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
#include "./fila.h"

Fila* novaFila(){
    Fila* filaAlocada = (Fila*) malloc(sizeof(Fila));
    filaAlocada->prim = NULL;
    filaAlocada->tam = 0;
    return filaAlocada;
}

void enfileira(Fila* f, int valor){
    FilaNo* no = (FilaNo*) malloc(sizeof(FilaNo));
    no->valor = valor;
    no->prox = NULL;
    if(f->prim == NULL){
        f->prim = no;
    } else {
        FilaNo* aux = f->prim;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    f->tam++;
}

FilaNo* retira(Fila* f){
    if(f-> tam == 0){
        printf("Fila vazia.");
        return NULL;
    }
    FilaNo* prim = f->prim;
    f->prim = f->prim->prox;
    f->tam--;
    return prim;
}

int filaVazia(Fila* f){
    return f->tam == 0;
}
