#include "stdlib.h"
#include "stdio.h"
#include "lse.neutra.h"
typedef struct pdv TPdv;
typedef struct AreaAtendimento TAreaAtendimento;
void inserirPdv(TAreaAtendimento *area,TPdv *pdv);
int qntPdvs(TAreaAtendimento *area);
TPdv *criarPdv(int fa);
TAreaAtendimento *criarAreaAtendimento();
void imprimirPdvs(TAreaAtendimento *areaPdvs);
void addTempos(TAreaAtendimento *a,double t,double x, double y, double z);
void *proxPdvLivre(TAreaAtendimento *caixa);
int caixaTempoMedio(TAreaAtendimento *a);
int getPdvFa(TPdv *pdv);
double *getPdvTmaximo (TPdv *pdv);
double *getPdvTmedio (TPdv *pdv);
int *getPdvnclientes(TPdv *pdv);
double *getPdvTtotal(TPdv *pdv);
void setStatusPdv(TPdv *pdv,int i);
double *getPdvTempoUltimpAtendimento(TPdv *pdv);
