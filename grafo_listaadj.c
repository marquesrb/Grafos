#include <stdio.h>
#include "grafo_listaadj.h"

#define VERTICE_INVALIDO NULL

bool inicializaGrafo(Grafo *grafo, int v){
    if(v <= 0){
        fprintf(stderr, "Erro na chamada de InicializaGrafo");
        return false;
    }
    grafo->NumVertice = v;
    if(!(grafo->matriz = (Aresta**) calloc(v, sizeof(Aresta*)))){
        fprintf(stderr, "Erro na alocacao de memoria na funcao InicalizaGrafo");
        return false;
    }
    grafo->NumAresta = 0;
    return true;
}

int obtemNrVertices(Grafo* grafo){
    return grafo->NumVertice;
}

int obtemNrArestas(Grafo *grafo){
    return grafo->NumAresta;
}

void insereAresta(int v1, int v2, Peso peso, Grafo *grafo){
    Apontador p1,p2;
    
    if(!(p1 = (Apontador) calloc(1,sizeof(Aresta)))){
        fprintf(stderr,"Erro na alocacao da aresta");
        exit(1);
    }

    p1->v = v2; 
    p1->peso = peso;
    p1->prox = grafo->matriz[v1];
    grafo->matriz[v1] = p1;
    grafo->NumAresta++;

    if(!(p2 = (Apontador) calloc(1,sizeof(Aresta)))){
        fprintf(stderr,"Erro na alocacao da aresta");
        exit(1);
    }
    p2->v = v1;
    p2->peso = peso; 
    p2->prox = grafo->matriz[v2];
    grafo->matriz[v2] = p2;
    grafo->NumAresta++;
}

bool existeAresta(int v1, int v2, Grafo *grafo){
    Apontador p = grafo->matriz[v1];
    while( (p != NULL) && (p->v != v2 )) {
        p = p->prox;
    }
    if(p  == NULL ) return false;
    return true;
}

bool listaAdjVazia(int  v, Grafo *grafo){
    return grafo->matriz[v] == NULL;
}

Apontador primeiroListaAdj(int  v, Grafo *grafo){
    return grafo->matriz[v];
}

Apontador proxListaAdj(int v, Grafo *grafo, Apontador atual){ 
    if(atual == NULL) return VERTICE_INVALIDO;
    return atual->prox;
}

void removeAresta(int v1, int v2, Grafo *grafo){
    Apontador q, ant;
    q = grafo->matriz[v1];
    ant = NULL;
    while((q!=NULL)&&(q->v != v2)){
        ant = q;
        q = q->prox;
    }
    if(q==NULL) return; 
    else{
        if(ant == NULL) grafo->matriz[v1]=q->prox;
        else             ant->prox=q->prox;          
        free(q);                                  
		--grafo->NumAresta;
    }
}

int obtemVerticeDestino(Apontador u){
    return u->v;
}

void imprimeGrafo(Grafo* grafo){
    for (int i = 0; i < grafo->NumVertice; i++)
    {
        printf("%d ", i);
        Apontador p = grafo->matriz[i];
        while(p != NULL){
        printf("-> %d ", p->v);
        p = p->prox;
        }
        printf("\n");
    }
    
    }
        
void liberaGrafo(Grafo *grafo){
    Apontador p;

    for (int i = 0; i < grafo->NumVertice; i++){
        while((p = grafo->matriz[i]) != NULL){
            grafo->matriz[i] = p->prox;
            p->prox = NULL;
            free(p);
        }
    }
    grafo->NumVertice = 0;
    free(grafo->matriz);
    grafo->matriz = NULL;   
}