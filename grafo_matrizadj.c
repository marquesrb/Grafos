#include <stdio.h>
#include "grafo_matrizadj.h"

bool inicializaGrafo(Grafo *grafo, int v){
    if( (v > MAX) || (v <= 0) ){
        fprintf(stderr, "Erro no inicializaGrafo: Numero de vertice inválido\n");
        return false;
    }

    grafo->numVertice = v;
    grafo->numAresta = 0;
    for (int i = 0; i < grafo->numVertice; i++)
    {
        for (int j = 0; j < grafo->numVertice; j++)
        {
            grafo->matriz[i][j] = AN;
        }
    }
    return true;
}

bool verificaValidadeVertice(int v, Grafo *grafo){
    if(v >= grafo->numVertice){
        fprintf(stderr,"Erro na funcao verificavalidetemvertice");
        return false;
    }
    if(v < 0){
        fprintf(stderr,"Numero do vertice negativo!");
        return false;
    }
    return true;
}

void  insereAresta(int v1, int v2, int peso, Grafo *grafo){
    if(!existeAresta(v1,v2,grafo)){
    grafo->matriz[v1][v2] = peso;
    grafo->matriz[v2][v1] = peso;
    grafo->numAresta++;
    }
}

int obtemNrVertices(Grafo* grafo){
    return grafo->numVertice;
}

int obtemNrAresta(Grafo* grafo){
    return grafo->numAresta;
}

bool existeAresta(int v1, int v2, Grafo *grafo){
    if (grafo->matriz[v1][v2] != AN)
    {
        return true;
    }

    return false;
}

void removeAresta(int v1, int v2, Grafo *grafo){
    grafo->matriz[v1][v2] = AN;
    grafo->matriz[v2][v1] = AN;
    grafo->numAresta--;
}

void imprimeGrafo(Grafo *grafo){
    printf("Vertices: %d\n", grafo->numVertice);
    printf("Arestas: %d\n", grafo->numAresta);
    for (int i = 0; i < grafo->numVertice; i++){    
        for (int j = 0; j < grafo->numVertice; j++){
            if (grafo->matriz[i][j] != AN)
                printf("%d->%d=%d \n", i, j, grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

bool listaAdjVazia(int v, Grafo *grafo){
    for (int i = 0; i < grafo->numVertice; i++)
    {
        if(grafo->matriz[v][i] != AN) return false;
    }
    
    return true;
}

Apontador proxListaAdj(int v, Grafo *grafo, Apontador u){
    if(!verificaValidadeVertice(v,grafo)) return AN;

    u++;
    while((u < grafo->numVertice) && (grafo->matriz[v][u] == AN))
    u++;
    if(u >= grafo->numVertice){
        return AN;
    }
    return u;
}

Apontador primeiroListaAdj(int v, Grafo *grafo){
     return proxListaAdj(v, grafo, 0);
}

int obtemVerticeDestino(Apontador v){
    return v;
}    
void liberaGrafo(Grafo *grafo){}
