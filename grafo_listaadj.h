#include <stdbool.h>
#include <stdlib.h>

typedef int Peso;

typedef struct Aresta
{
    int v;
    Peso peso;
    struct Aresta *prox; 
}Aresta;

typedef Aresta* Apontador;

typedef struct{
    int NumVertice;
    int NumAresta;
    Apontador *matriz; 

}Grafo;

bool inicializaGrafo(Grafo *grafo, int v);

int obtemNrVertices(Grafo* grafo);

int obtemNrArestas(Grafo* grafo);

void insereAresta(int v1, int v2, Peso peso, Grafo *grafo);

bool existeAresta(int v1, int v2, Grafo *grafo);

void removeAresta(int v1, int v2, Grafo *grafo);

bool listaAdjVazia(int  v, Grafo *grafo);

Apontador primeiroListaAdj(int  v, Grafo *grafo);

Apontador proxListaAdj(int v, Grafo *grafo,  Apontador atual);

int obtemVerticeDestino(Apontador v);

void liberaGrafo(Grafo *grafo);

void imprimeGrafo(Grafo *grafo);