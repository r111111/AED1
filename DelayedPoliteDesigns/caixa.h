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
void* proxPdvLivre();
