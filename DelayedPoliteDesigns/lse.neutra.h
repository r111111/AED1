#include "stdlib.h"
#include "stdio.h"
typedef struct lista TLista;
typedef struct elemento TElemento;
typedef int(*TComparador)(void*,void*);
typedef int(*TCondicao)(void*);
typedef void (*TImpressora)(void*);
void inserirFinalLSE(TLista *l,void *carganova);
void inserirInicioLSE(TLista *l,void *carganova);
void *removerInicioLSE(TLista *l);
TLista *criarLista();
void *removerElemento(TLista *lst, int posicao);
int tamanhoLista(TLista *lst);
void inserirOrdenadoLSE(TLista *lst, void *carganova,TComparador comparador);
void imprimirElemento(TElemento *e);
void imprimirLSE(TLista *lst,TImpressora impressora);
void *temNaLista(TLista *lst,TCondicao cond);

