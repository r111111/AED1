#include "stdlib.h"
#include "stdio.h"
#include "lse.neutra.h"
#include "agenda.h"
#include "caixa.h"
struct elemento{
  void *carga;
  struct elemento *prox;
};

struct lista{
  int tamanho;
  TElemento *inicio;
  TElemento *fim;
};

TLista *criarLista(){
  TLista *lst = malloc(sizeof(TLista));
  lst->tamanho = 0;
  lst->inicio = NULL;
  lst->fim = NULL;
  return lst;
};

void inserirFinalLSE(TLista *lst,void *carganova){
  TElemento *e = malloc(sizeof(TElemento));
  e->carga = carganova;
  e->prox = NULL;
  if(lst->inicio == NULL){
    lst->inicio = e;
    lst->fim =e;
    lst->tamanho++;
  }else{
    lst->fim->prox = e;
    lst->fim = e;
    lst->tamanho++;
  }
}

void inserirInicioLSE(TLista *lst,void *carganova){
  if(lst->inicio ==NULL){
    inserirFinalLSE(lst,carganova);
  }else{
    TElemento *e = malloc(sizeof(TElemento));
    e->carga = carganova;
    e->prox = lst->inicio;
    lst->inicio = e;
    lst->tamanho++;
  }
}

void *removerInicioLSE(TLista *lst){
  void *carga= NULL;
  if(lst->inicio ==NULL){
    printf("Lista vazia\n");
  }else{
    carga = lst->inicio->carga;
    TElemento *prim = lst->inicio;
    if(lst->inicio == lst->fim){
      lst->fim = NULL;
    }
    lst->inicio = prim->prox; 
    free(prim);
  }
  return carga;
}

void *removerElemento(TLista *lst,int posicao){
  void *carga ;
  if(posicao > lst->tamanho-1){
    carga = NULL;
    printf("Lista Vazia");
  }else if(posicao == 0){
    carga = removerInicioLSE(lst);
  }else{
     int i;
    TElemento *anterior = lst->inicio;
    TElemento *walker = anterior->prox;
    for(i=1;i<posicao;i++){
     anterior = anterior->prox;
      walker = walker->prox;
    } 
    carga = walker->carga;  
    anterior->prox = walker->prox;
    free(walker);
  }
  return carga;
}

int tamanhoLista(TLista *lst){
  return lst->tamanho;
}

void inserirOrdenadoLSE(TLista *lst, void *carganova, TComparador compara){
  
    void *novacarga = carganova;
    if(lst->inicio == NULL){
      inserirFinalLSE(lst, carganova);
    }else{
      TElemento *walker = lst->inicio->prox;
      TElemento *anterior = lst->inicio;
      while(walker !=NULL && compara(walker->carga,novacarga)==-1){
        walker = walker->prox;
        anterior = anterior->prox;
      }
      TElemento *novoElemOrdenado = malloc(sizeof(TElemento));
      novoElemOrdenado->carga = novacarga;
      anterior->prox = novoElemOrdenado; 
      novoElemOrdenado->prox = walker;
    }
}

void imprimirLSE(TLista *lst,TImpressora impressora){
  if (lst->inicio == NULL){
      printf("Lista Vazia\n");
  }else{
    TElemento *caminhador=lst->inicio;
    while(caminhador != NULL){
      impressora(caminhador->carga);
      caminhador = caminhador->prox;
    }
 } 
}

void* temNaLista(TLista *lst,TCondicao cond){
  int i=0;
  TElemento *caminhador = lst->inicio;
    while(caminhador!=NULL){
      if(cond(caminhador->carga)){
       break;
      }else{
        caminhador=caminhador->prox;
        i++;
      }
    }
  return caminhador->carga;
}


//fa das operadoras = fa*tempoMedio

//tempo de atendimento = fa*qntProdutos + tempoPagamentoCliente

//enfileirar e caixaLivre()
//contabilizar tempo medio de permanecia na area