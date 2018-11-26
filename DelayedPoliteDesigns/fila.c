#include "fila.h"

#include "stdlib.h"
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
  return removerInicioLSE(fila->lista);
}

