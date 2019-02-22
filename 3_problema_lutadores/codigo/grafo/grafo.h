/*

    UNIVERSIDADE FEDERAL DO CEARÁ
    CAMPUS SOBRAL
    ENGENHARIA DA COMPUTAÇÃO

    ALGORITMOS EM GRAFOS 2017.1
    Abner Sousa Nascimento
    374864

*/

#ifndef GRAFO_H_
#define GRAFO_H_

typedef struct aresta Aresta;
typedef struct listaAdj ListaAdj;
typedef struct grafo Grafo;

/* Estrutura para Aresta do grafo */
struct aresta {
    int origem;  // Vértice de onde a Aresta sai
    int destino;  // Vértice para o qual a Aresta vai
    int peso;  // Peso da Aresta
    Aresta* prox;  // Ponteiro para próxima Aresta da lista
};

/* Estrutura para listas de adjacência */
struct listaAdj {
    Aresta* prim;  // Ponteiro para o primeiro nó da lista
};

/* Estrutura para representação dos grafos */
struct grafo {
    int V;  // Número de vértices do grafo;
    int E;  // Número de Arestas do grafo;
    ListaAdj* listaAdj;  // Lista de Adjacências associada ao grafo
};

/* Funções básicas para gerenciamento do grafo */

/* Cria nova aresta com peso de origem a destino */
Aresta* novaAresta(int origem, int destino, int peso);

/* Cria novo grafo com V vértices */
Grafo* novoGrafo(int V);

/* Adiciona aresta direcionada com peso de origem a destino ao grafo g */
void addArestaDir(Grafo* g, int origem, int destino, int peso);

/* Adiciona aresta não direcionada com peso de origem a destino ao grafo g */
void addAresta(Grafo* g, int origem, int destino, int peso);

/* Remove uma aresta do vértice origem a destino do grafo g */
void removeAresta(Grafo* g, int origem, int destino);

/* Auxilia na impressão de um grafo na tela */
void printGrafo(Grafo* g);

/* Auxilia na impressão de uma aresta na tela */
void printAresta(Aresta a);

/* Remove uma lista de adjacências da memória */
void liberaLista(Aresta* noLista);

/* Libera o espaço da memória alocado para um grafo */
void liberaGrafo(Grafo* g);


#endif  // GRAFO_H_
