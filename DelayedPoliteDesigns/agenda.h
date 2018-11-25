#include "stdlib.h"
#include"stdio.h"
#include "lse.neutra.h"
typedef struct agenda TAgenda;
typedef struct evento TEvento;
typedef struct suspensao TSuspensao;
typedef struct finalizacao TFinal;
typedef struct chegada TChegada;
TEvento *criarEvento(double temp, char tip,void *carg);
TAgenda *criarAgenda(int dia,int mes, int ano);
TChegada *criarChegada(int nItens,int tipoChegada,int tempoPag);
TSuspensao *criarSuspensao(int idPdv, int dur);
char tipoDeEvento(TEvento *e);
void agendamento(TAgenda *a,void *evento);
void imprimirAgenda(TAgenda *a);
void imprimirChegada(void *chegada);
void imprimirEvento(void *e);

int comparaEvento(void *evento1, void *evento2);

