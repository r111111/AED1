#include "caixa.h"
#include "lse.neutra.h"
struct pdv{
  double tempoMedio,tempoMaximo,tempoTotal,tempoUltimoAtendmiento,fa;
  int id,livre,nClientes,suspensaoMarcada;
};

struct AreaAtendimento{
  TLista *listaPdvs;
  double tempoMedio,x,y,z;
  double tempoAtual;
};

struct cliente{
	double tempoChegada,qntItens,tempoAtendimento;
	double tipo;
};

TPdv *criarPdv(double fa){
  TPdv *pdv = malloc(sizeof(TPdv));
  pdv->tempoMaximo = pdv->tempoMedio = 0;
  pdv->livre = 1;
  pdv->fa = fa;
  pdv->nClientes = 0;
  pdv->tempoTotal = 0;
  pdv->suspensaoMarcada=0;
  pdv->tempoUltimoAtendmiento=0;
  return pdv;
}

TCliente *criarCliente(double tChegada,double qItens,double tAtendimento,double tipo){
	TCliente *cl = malloc(sizeof(TCliente));
	cl->tempoChegada = tChegada;
	cl->qntItens = qItens;
	cl->tempoAtendimento = tAtendimento;
	cl->tipo = tipo;
	return cl;
}

TAreaAtendimento *criarAreaAtendimento(){
  TAreaAtendimento *a = malloc(sizeof(TAreaAtendimento));
  a->listaPdvs = criarLista();
  a->tempoAtual=0;
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
  printf("%d tmmaximo:%lf fa:%lf livre:%d nClientes:%d\n",pdv->id,pdv->tempoMaximo,pdv->fa,pdv->livre,pdv->nClientes);
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

void setStatusPdv(TPdv *pdv,int i){
	*(&pdv->livre) = i;

}

int caixaTempoMedio(TAreaAtendimento *a){
	return a->tempoMedio;
}

void *getPdv(int id){
	return NULL;
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


double *getPdvTempoUltimoAtendimento(TPdv *pdv){
	return &pdv->tempoUltimoAtendmiento;
}

int getPdvId(TPdv *pdv){
	return pdv->id;
}



double *getTempoChegadaCliente(TCliente *cl){
	return &cl->tipo;
}

double *getAreaAtendimentoTempoMedio(TAreaAtendimento *a){
	return &a->tempoMedio;
}

void *encontrarpdv(TAreaAtendimento *area,int id){
	printf("\nencontrarpdv");
	return removerElemento(area->listaPdvs,id-1);
}

void printstatuspdv(TPdv *pdv){
	printf("%d",pdv->livre);
}

void setSuspensao(void *pdv,int i){
	TPdv *pdv1 = pdv;
	*(&pdv1->suspensaoMarcada) = i;
}

int getPdvSuspensao(TPdv *pdv){
	return pdv->suspensaoMarcada;
}

double *getTempoAtual(TAreaAtendimento *a){
	return &a->tempoAtual;
}
double getAreax(TAreaAtendimento *a){
	return a->x;
}
double getAreay(TAreaAtendimento *a){
	return a->y;
}
double getAreaz(TAreaAtendimento *a){
	return a->z;
}


