#include "stdlib.h"
#include"stdio.h"
#include "agenda.h"
#include "lse.neutra.h"
#include "caixa.h"

struct agenda{
  int dia,mes,ano;
  TLista *listaEventos;
};

struct evento{
  double tempoDeInicio;
  char tipo;
  void *carga;
};

struct chegada {
  int nItens,tipoCliente,tempoPag;
};
struct suspensao{
  int nPdv,duracao;
};
struct finalizacao{
  char f;
};

TAgenda *criarAgenda(int d, int m, int a){
  TAgenda *agenda = malloc(sizeof(TAgenda));
  agenda->dia = d;
  agenda->mes = m;
  agenda->ano = a;
  agenda->listaEventos = criarLista();
  return agenda;
};

TEvento *criarEvento(double tempo,char tipo, void *carga){
  TEvento *evento = malloc(sizeof(TEvento));
  evento->tempoDeInicio = tempo;
  evento->tipo = tipo;
  evento->carga = carga;
  return evento;
}

int comparaEvento(void *evento1, void *evento2){
  TEvento *e1 = evento1;
  TEvento *e2 = evento2;
  if(e1->tempoDeInicio < e2->tempoDeInicio){
    return -1;
  }else if (e1->tempoDeInicio > e2->tempoDeInicio){
    return 1;
  }else{
    return 0;
  }
}

TChegada *criarChegada(int nItens,int tipoCliente,int tempoPag){
  TChegada *c = malloc(sizeof(TChegada));
  c->nItens=nItens;
  c->tipoCliente=tipoCliente;
  c->tempoPag=tempoPag;
  return c;
}

TSuspensao *criarSuspensao(int idPdv, int dur){
  TSuspensao *s = malloc(sizeof(TSuspensao));
  s->nPdv=idPdv;
  s->duracao=dur;
  return s;
};

void agendamento(TAgenda *a, void *evento){
  inserirOrdenadoLSE(a->listaEventos,evento,comparaEvento);
}

void imprimirEvento(void *e){
  TEvento *evento = e;
  printf("%c %lf",evento->tipo,evento->tempoDeInicio);
  if(evento->tipo == 'C'){
    TChegada *c = evento->carga;
    printf(" %d %d %d\n",c->nItens,c->tipoCliente,c->tempoPag);
  }
}

void imprimirAgenda(TAgenda *agenda){
  imprimirLSE(agenda->listaEventos,&imprimirEvento);
}

void imprimirChegada(void *c){

}

char tipoDeEvento(TEvento *e){
  return e->tipo;
}

