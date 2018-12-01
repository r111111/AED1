#include "fila.h"
#include "lse.neutra.h"
#include "stdlib.h"
#include "stdio.h"
struct fila{
  int tamanho;
  TLista *lista;
};


TFila *criarFila(){
  TFila *fila = malloc(sizeof(TFila));
  fila->tamanho =0;
  fila->lista = criarLista();
  return fila;
}

void *desenfileirar(TFila *fila){
	TLista *inicio =  removerInicioLSE(fila->lista);
	return inicio;
}

void enfileirar (TFila *fila, void *carga){
	inserirFinalLSE(fila->lista,carga);
}

int filaVazia(TFila *fila){
	return listaVazia(fila->lista);
}
void *getFilaLista(TFila *fila){
	return fila->lista;
};


