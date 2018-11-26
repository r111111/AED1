#include "caixa.h"

struct pdv{
  double tempoMedio,tempoMaximo,tempoTotal,tempoUltimoAtendmiento;
  int fa,id,livre,nClientes;
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
  pdv->nClientes = 0;
  pdv->tempoTotal = 0;
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
//pdv->
void* proxPdvLivre(TAreaAtendimento *caixa){
   return temNaLista(caixa->listaPdvs,&pdvLivre);
}

int caixaTempoMedio(TAreaAtendimento *a){
	return a->tempoMedio;
}

int getPdvFa(TPdv *pdv){
	return pdv->fa;
}

double *getPdvTmedio (TPdv *pdv){
	return &pdv->tempoMedio;
}

double *getPdvTmaximo (TPdv *pdv){
	return &pdv->tempoMaximo;
}

int *getPdvnclientes(TPdv *pdv){
	return &pdv->nClientes;
}

double *getPdvTtotal(TPdv *pdv){
	return &pdv->tempoTotal;
}

void setStatusPdv(TPdv *pdv,int i){
	pdv->livre = i;
}
double *getPdvTempoUltimoAtendimento(TPdv *pdv){

}

