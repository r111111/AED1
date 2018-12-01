#include "stdlib.h"
#include "stdio.h"
typedef struct pdv TPdv;
typedef struct AreaAtendimento TAreaAtendimento;
typedef struct cliente TCliente;

void inserirPdv(TAreaAtendimento *area,TPdv *pdv);
int qntPdvs(TAreaAtendimento *area);
TPdv *criarPdv(double fa);
TAreaAtendimento *criarAreaAtendimento();
TCliente *criarCliente(double tChegada,double qItens,double tAtendimento, double tipo);
void imprimirPdvs(TAreaAtendimento *areaPdvs);
void addTempos(TAreaAtendimento *a,double t,double x, double y, double z);
void *proxPdvLivre(TAreaAtendimento *caixa);
int caixaTempoMedio(TAreaAtendimento *a);

void *getPdv(int id);
int getPdvFa(TPdv *pdv);
double *getPdvTmaximo (TPdv *pdv);
double *getPdvTmedio (TPdv *pdv);
int *getPdvnclientes(TPdv *pdv);
double *getPdvTtotal(TPdv *pdv);
void setStatusPdv(TPdv *pdv,int i);
double *getPdvTempoUltimoAtendimento(TPdv *pdv);
double *getAreaAtendimentoTempoMedio(TAreaAtendimento *a);


double *getTempoChegadaCliente(TCliente *cl);
int getPdvId(TPdv *pdv);
void *encontrarpdv(TAreaAtendimento *area,int id);
void printstatuspdv(TPdv *pdv);
void setSuspensao(void *pdv,int i);
int getPdvSuspensao(TPdv *pdv);

double *getTempoAtual(TAreaAtendimento *a);
double getAreax(TAreaAtendimento *a);
double getAreay(TAreaAtendimento *a);
double getAreaz(TAreaAtendimento *a);
