#ifdef MATRIZ
#include  "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h" 
#endif

#include <stdio.h>
#include <stdlib.h>


typedef struct No
{
    int  v; 
    struct No *ant; 
}No;


typedef struct Fila
{
    int qtde;
    No *no;
    No *ultimo;
}Fila;

void insereFila(int v, Fila *fila){
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    novoNo->v = v;
    novoNo->ant = NULL;

    if (fila->qtde == 0)
        fila->no = novoNo;
    else
        fila->ultimo->ant = novoNo;
    
    fila->ultimo = novoNo;
    fila->qtde++;
}

int removeFila(Fila *fila){
    No *aux = fila->no;
    int v = aux->v;

    fila->no = aux->ant; 
    free(aux);
    fila->qtde--;

    if(fila->qtde == 0) fila->ultimo = NULL;

    return v;
}

void criaFila(Fila *fila) {
    fila->no = NULL;
    fila->ultimo = NULL;
    fila->qtde = 0;
}

void imprimeComponentes(int tam, int *antecessor, FILE *saida){
    int qnt = 1;
    fprintf(saida,"Componentes Conectados:\n");
    for (int i = 0; i < tam; i++){
        if(antecessor[i] == -1 && qnt > 1) fprintf(saida,"\n"); ;
        if(antecessor[i] == -1) {
            fprintf(saida,"C%d:",qnt);
            qnt++;
        }
        fprintf(saida," %d",i);     
    }
}

void imprimeCaminho(int raiz, int* antecessor, int destino, FILE* saida) {
    if (raiz == destino || antecessor[destino] == -1) {
        fprintf(saida, "%d", destino);
    } else {
        imprimeCaminho(raiz, antecessor, antecessor[destino], saida);
        fprintf(saida, " %d", destino);
    }
}

void imprimeArticulacao(int tam, int *articulacao, FILE *saida) {
    int primeiro_articulado = 1; // Flag para verificar se é o primeiro vértice articulado
    for (int i = 0; i < tam; i++) {
        if (articulacao[i] == 1) {
            if (primeiro_articulado) {
                fprintf(saida, "%d", i);
                primeiro_articulado = 0;
            } else {
                fprintf(saida, " %d", i);
            }
        }
    }
}

void visitaLargura(int i, int *cor, int *antecessor, Grafo *grafo, FILE *saida){
    cor[i] = 1;

    int aux;
    Fila  fila;
    criaFila( &fila );
    insereFila(i, &fila);
    while (fila.qtde > 0)
    {

       aux = removeFila(&fila);
   
       if (!(listaAdjVazia(aux,grafo)))
       {
            Apontador atual = primeiroListaAdj(aux, grafo);
            while(atual > 0)
            {
                int nr = obtemVerticeDestino(atual);

                if(cor[nr] == 0){
                    cor[nr] = 1;
                    fprintf(saida," %d", nr);
                    antecessor[nr] = aux;
                    insereFila(nr,&fila); 
                    
                }

                atual = proxListaAdj(aux, grafo, atual); 
                
            }  
       }
       cor[aux] = -1;
       }
}

void buscaLargura(Grafo * grafo, FILE *saida) {
    int *cor = calloc(obtemNrVertices(grafo), sizeof(int));
    int *antecessor = calloc(obtemNrVertices(grafo), sizeof(int));
    fprintf(saida,"BL:\n");
    for (int i = 0; i < obtemNrVertices(grafo); i++)
    {
        if (cor[i] == 0) 
        {
            if(i == 0) fprintf(saida,"%d",i);
            else fprintf(saida," %d",i);
            antecessor[i] = -1; 
            visitaLargura(i, cor, antecessor, grafo, saida);
        }
    }
    fprintf(saida,"\n\nCaminhos BL: ");

    for (int j = 0; j < obtemNrVertices(grafo); j++) {
        fprintf(saida,"\n");
        imprimeCaminho(0, antecessor, j, saida); 
    }
    
    free(antecessor);
    free(cor);
}

void visitaProfundidade(int i, int *tempo, int *cor, int *antecessor, int *tdesc, int *low, int *articulacao, Grafo *grafo, FILE *saida) {
    cor[i] = 1;
    int filhos = 0; 
    tdesc[i] = low[i] = ++(*tempo);
    fprintf(saida, "%d", i);

    if (!listaAdjVazia(i, grafo)) {
        Apontador atual = primeiroListaAdj(i, grafo);

        while (atual > 0) {
            int nr = obtemVerticeDestino(atual);
            if (cor[nr] == 0) {
                fprintf(saida," ");
                filhos++;
                antecessor[nr] = i;
                visitaProfundidade(nr, tempo, cor, antecessor, tdesc, low, articulacao, grafo, saida);
                low[i] = (low[i] < low[nr]) ? low[i] : low[nr];
                
                // Verifica se i é um vértice de articulação
                if ((antecessor[i] == -1 && filhos > 1) || (antecessor[i] != -1 && low[nr] >= tdesc[i])) {
                    articulacao[i] = 1; 
                }
            } else if (nr != antecessor[i]) {
                low[i] = (low[i] < tdesc[nr]) ? low[i] : tdesc[nr];
            }

            atual = proxListaAdj(i, grafo, atual);
        }
        
    }

    cor[i] = -1;
}

void buscaProfundidade(Grafo* grafo, FILE *saida){
    int *cor = calloc(obtemNrVertices(grafo), sizeof(int));
    int *antecessor = calloc(obtemNrVertices(grafo), sizeof(int));
    int *tdesc = calloc(obtemNrVertices(grafo), sizeof(int));
    int *low = calloc(obtemNrVertices(grafo), sizeof(int));
    int *articulacao = calloc(obtemNrVertices(grafo), sizeof(int));
    int tempo = 0;
    fprintf(saida,"BP:\n");
    for (int i = 0; i < obtemNrVertices(grafo); i++)
    {
        if(cor[i] == 0) {
            antecessor[i] = -1;
            if(i > 0) fprintf(saida," ");
            visitaProfundidade(i, &tempo,cor, antecessor, tdesc, low, articulacao, grafo, saida);
        }
    }

    fprintf(saida,"\n\nCaminhos BP:");
    for (int j = 0; j < obtemNrVertices(grafo); j++) {
        fprintf(saida,"\n");
        imprimeCaminho(0, antecessor, j, saida); 
    }

    fprintf(saida,"\n\n");
    imprimeComponentes(obtemNrVertices(grafo), antecessor,saida);
    
    fprintf(saida,"\n\nVertices de articulacao:\n");
    imprimeArticulacao(obtemNrVertices(grafo), articulacao, saida);
    
    fprintf(saida,"\n");

    free(antecessor);
    free(articulacao);
    free(tdesc);
    free(low);
    free(cor);
}

int main(int argc, char *argv[]) {

    FILE *arquivo = fopen(argv[1],"r");
    FILE *saida = fopen(argv[2], "w+");

    if (arquivo == NULL || saida  == NULL){
        fprintf(stderr, "Não foi possível abrir os arquivos\n");
        return -1;
    }
 
    int v, a; 
    fscanf(arquivo,"%d %d",&v, &a);
    
    Grafo  grafo;
    inicializaGrafo(&grafo,v);

    //Leitura do arquivo  

    while (!feof(arquivo)) {

       int v1, v2, peso;

       fscanf(arquivo,"%d %d %d ",&v1, &v2, &peso);
       insereAresta(v1,v2,peso,&grafo);
    }

    buscaLargura(&grafo,saida);
    fprintf(saida,"\n\n");
    buscaProfundidade(&grafo,saida);
    liberaGrafo(&grafo);

    fclose(arquivo);
    return 0;
}

