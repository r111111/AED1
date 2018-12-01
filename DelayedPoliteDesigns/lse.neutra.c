#include "lse.neutra.h"
#include "stdlib.h"
#include "stdio.h"



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
  void *carga = NULL;
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
  lst->tamanho--;
  return carga;
}

// ERRRRRRO
void *getInicioLSE(TLista *lst){
	return lst->inicio;
}
void *removerElemento(TLista *lst,int posicao){
  void *carga = NULL ;
  printf("\nposicao do pdv: %d",posicao);
  if(posicao > lst->tamanho-1){
    carga = NULL;
    printf("Lista Vazia removerElemento, tamanho da lista: %d,posicao = %d",lst->tamanho,posicao);
  }else if(posicao == 0){
    return lst->inicio->carga;
  }else{
	  printf("\nposicao do pdv: %d,tamanho da lista: %d",posicao,lst->tamanho);
     int i;
    TElemento *anterior = lst->inicio;
    TElemento *walker = lst->inicio->prox;
    if(lst->inicio->prox==NULL){
       	printf("walker NULLLL");
       }
    for(i=1;i<posicao;i++){
    	printf("aklfjaçsld");
     anterior = anterior->prox;
      walker = walker->prox;
    } 
    carga = walker->carga;  
  }
  if(carga==NULL){
	printf("pdv NULLLLL");
  };
  printf("\nposicao do pdv: %d",posicao);
  return carga;
}

int tamanhoLista(TLista *lst){
  return lst->tamanho;
}

void inserirOrdenadoLSE(TLista *lst, void *carganova, TComparador compara){
    void *novacarga = carganova;
    TElemento *novoElemOrdenado = malloc(sizeof(TElemento));
    if(lst->inicio == NULL){
      inserirFinalLSE(lst, carganova);
    }else{
      TElemento *anterior = lst->inicio;
      TElemento *walker = lst->inicio->prox;
      if(walker == NULL){
    	  if(compara(novacarga,anterior->carga)>=0){
    		  inserirFinalLSE(lst,novacarga);
    	  }else{
   		  	  inserirInicioLSE(lst,novacarga);
      	  }
      }else{
    	  while(walker !=NULL && compara(novacarga,walker->carga)>0){
    	        walker = walker->prox;
    	        anterior = anterior->prox;
    	   }
    	  	 novoElemOrdenado->carga = novacarga;
    	     if(walker== NULL){
    	     	 inserirFinalLSE(lst, novacarga);
    	     }else{
    	    		 anterior->prox = novoElemOrdenado;
    	    		 novoElemOrdenado->prox = walker;
    	     }
    }

     lst->tamanho++;
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
       return caminhador->carga;
      }else{
        caminhador=caminhador->prox;
        i++;
      }
    }
    if(caminhador == NULL){
    	printf("\nproxPdvLivre devia ser igual a null\n");
    }
  return caminhador;
}

TElemento *proxElemento(TElemento *e){
	return e->prox;
}

int listaVazia(TLista *lst){
	if(lst->inicio == NULL){
		return 1;
	}else{
		return 0;
	}
}
//fa das operadoras = fa*tempoMedio

//tempo de atendimento = fa*qntProdutos + tempoPagamentoCliente

//enfileirar e caixaLivre()
//contabilizar tempo medio de permanecia na area
