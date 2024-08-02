#include <stdbool.h>

#define MAX 100
#define AN -1

typedef struct{
    int matriz[MAX][MAX];
    int numAresta;
    int numVertice;
} Grafo;

typedef int Apontador;

bool inicializaGrafo(Grafo *grafo, int v);

bool verificaValidadeVertice(int v, Grafo *grafo);

int obtemNrVertices(Grafo* grafo);

int obtemNrArestas(Grafo* grafo);

void insereAresta(int v1, int v2, int peso, Grafo *grafo);

bool existeAresta(int v1, int v2, Grafo *grafo);

void removeAresta(int v1, int v2, Grafo *grafo);

bool listaAdjVazia(int v, Grafo *grafo);

Apontador primeiroListaAdj(int v, Grafo *grafo);

Apontador proxListaAdj(int v, Grafo *grafo, Apontador u);

int obtemVerticeDestino(Apontador v); 

void liberaGrafo(Grafo *grafo);

void imprimeGrafo(Grafo *grafo);
