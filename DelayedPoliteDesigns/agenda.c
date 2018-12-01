#include "agenda.h"
#include "lse.neutra.h"
#include "stdlib.h"
#include "stdio.h"
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
  int tipoChegada;
  double tempoPag,nItens;
};

struct suspensao{
  int nPdv;
  double duracao;
};

struct finalizacao{
  char f;
};

struct fimatend{
	double marcaDeTempo;
	int idPdv;
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

TChegada *criarChegada(double nItens,int tipoChegada,double tempoPag){
  TChegada *c = malloc(sizeof(TChegada));
  c->nItens=nItens;
  c->tipoChegada=tipoChegada;
  c->tempoPag=tempoPag;
  return c;
}

TSuspensao *criarSuspensao(int idPdv, int dur){
  TSuspensao *s = malloc(sizeof(TSuspensao));
  s->nPdv=idPdv;
  s->duracao=dur;
  return s;
};

TFimAtendimento *criarFimAtendimento(int idPdv){
	TFimAtendimento *FimAtendimento = malloc(sizeof(TFimAtendimento));
	FimAtendimento->idPdv = idPdv;
	return FimAtendimento;
}
void *criarFinalizacao(){
	TFinal *f = malloc(sizeof(TFinal));
	f->f = 'F';
	return f;
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

void agendamento(TAgenda *a, void *evento){
  inserirOrdenadoLSE(a->listaEventos,evento,comparaEvento);
}

void imprimirEvento(void *e){
  TEvento *evento = e;
  printf("tipo do evento: %c marca de tempo: %lf",evento->tipo,evento->tempoDeInicio);
  if(evento->tipo == 'C'){
    TChegada *c = evento->carga;
    printf(" %lf %d %lf\n",c->nItens,c->tipoChegada,c->tempoPag);
  }
}

char tipoDeEvento(TEvento *e){
  return e->tipo;
}

void *getAgendaListaEventos(TAgenda *agenda){
	return agenda->listaEventos;
}

void imprimirAgenda(TAgenda *agenda){
  imprimirLSE(agenda->listaEventos,&imprimirEvento);
}

double *getChegadatpag(TChegada *c){
	return &c->tempoPag;
}

double *getEventoMarcaTempo(TEvento *e){
	return &e->tempoDeInicio;
}

void *getCargaEvento(TEvento *e){
	return e->carga;
}

char getEventoTipo(TEvento *evento){
	return evento->tipo;
}

void *getFimAtendimentoTempo(TFimAtendimento *fimatend){
	return &fimatend->marcaDeTempo;
}
int getFimAtendimentoidPdv(TFimAtendimento *fimatend){
	return fimatend->idPdv;
}

void *desenfileirarAgenda(TAgenda *agenda){
	return removerInicioLSE(agenda->listaEventos);
}

int getSusPdvIdv(TSuspensao *s){
	return s->nPdv;
}


double getSuspensaoDuracao(TSuspensao *s){
	return s->duracao;
}


double *getnIntensCliente(TChegada *cl){
	return &cl->nItens;
}

int *getTipoCliente(TChegada *cl){
	return &cl->tipoChegada;
}




