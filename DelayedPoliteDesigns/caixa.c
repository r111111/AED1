#include "caixa.h"

struct pdv{
  double tempoMedio,tempoMaximo;
  int fa,id,livre;
};

struct AreaAtendimento{
  TLista *listaPdvs;
  double tempoMedio,x,y,z;
};

TPdv *criarPdv(int fa){
  TPdv *pdv = malloc(sizeof(TPdv));
  pdv->tempoMaximo = pdv->tempoMedio = 0;
  pdv->livre = 1;
  pdv->fa = fa;
  return pdv;
}

TAreaAtendimento *criarAreaAtendimento(){
  TAreaAtendimento *a = malloc(sizeof(TAreaAtendimento));
  a->listaPdvs = criarLista();
  return a;
}

void inserirPdv(TAreaAtendimento *area,TPdv *pdv){
  pdv->id = tamanhoLista(area->listaPdvs)+1;
  inserirFinalLSE(area->listaPdvs, pdv);
}

int qntPdvs(TAreaAtendimento *area){
  return tamanhoLista(area->listaPdvs);
}

void imprimirPdv(void *carga){
  TPdv *pdv = carga;
  printf("%d %lf %lf %d\n",pdv->id,pdv->tempoMedio,pdv->tempoMaximo,pdv->fa);
}

void imprimirPdvs(TAreaAtendimento *areaPdvs){
  imprimirLSE(areaPdvs->listaPdvs, &imprimirPdv);
}

void addTempos(TAreaAtendimento *a,double t,double x, double y, double z){
  a->tempoMedio = t;
  a->x =x;
  a->z=z;
  a->y = y;
}

int pdvLivre(void *carga){
  TPdv *pdv = carga;
  if(pdv->livre){
    return pdv->id;
  }else{
    return 0;
  }
}

void* proxPdvLivre(TAreaAtendimento *caixa){
   return temNaLista(caixa->listaPdvs,&pdvLivre);
}
