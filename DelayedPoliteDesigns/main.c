#include "stdio.h"
#include "stdlib.h"
#include "caixa.h"
#include "agenda.h"
#include "fila.h"
#include "atendimentos.h"
#include "lse.neutra.h"

int clienteAtendido(double tempoFila,double tempoAtend,TChegada *c,TAreaAtendimento *a){
	if(*getTipoCliente(c) == 2){
		if(tempoFila+tempoAtend<=getAreax(a)){
			return 1;
		}
	}else if(*getTipoCliente(c) == 3){
		if(tempoFila<=getAreay(a) && tempoAtend<=getAreaz(a)){
			return 1;
		}
	}else if(*getTipoCliente(c) == 1){
		return 1;
	}
	return 0;
}
void executarEvento(TAgenda *agenda,TEvento *evento,TAreaAtendimento *area,TFila *filaClientes){
	if(getEventoTipo(evento)=='C'){ //evento de chegada/atendimento
		TChegada *c = getCargaEvento(evento);
		printf("///////////////////////////////////////////////////////////////////\n");
		printf("\n Dentro de executar evento chegada");
		printf("\nIMPRESSÃO DA LISTA DE PDVS nnnn para cada evento exeutado\n");
		imprimirPdvs(area);
		TPdv *pdv = proxPdvLivre(area);
		double tempoAtendimento = *(getChegadatpag(c))*(*getnIntensCliente(c))+getPdvFa(pdv);
		printf("\nTempo de Atendimento = %lf, quantidade de intens: %lf",tempoAtendimento,*(getnIntensCliente(c)));
		double *pdvTultimoatend = getPdvTempoUltimoAtendimento(pdv);
		double tempoNaFila;
		if(*pdvTultimoatend==0 || listaVazia(getAgendaListaEventos(agenda))){
			printf("\nTempo na fila é 0");
			tempoNaFila =0;
		}else{
			tempoNaFila = *(pdvTultimoatend) - *(getEventoMarcaTempo(evento));
		}
		double horarioFimAtendimento = *(getEventoMarcaTempo(evento))+tempoAtendimento+tempoNaFila;
		printf("\nHORARIO DE FIM DE ATENDIMENTO: %lf",horarioFimAtendimento);

		if(clienteAtendido(tempoNaFila, tempoAtendimento, c, area)){
			printf("\nTEMPO ATUAL DENTRO DE EXECUCAO EVENTO CHEGADA: %lf",*getTempoAtual(area));
			horarioFimAtendimento = *(getEventoMarcaTempo(evento))+tempoAtendimento;
			TFimAtendimento *finalAtendimento = criarFimAtendimento(getPdvId(pdv));
			TEvento *eventoFimAtendimento = criarEvento(horarioFimAtendimento, 'X',finalAtendimento);
			agendamento(agenda, eventoFimAtendimento);
			printf("\npdvultimoatend: %lf,horariofimAtendimento: %lf",*pdvTultimoatend,horarioFimAtendimento);
			printf("\n///////////////////////////////////////////////////////////////////");

			*getEventoMarcaTempo(evento)+= tempoNaFila;
			setStatusPdv(pdv,0);
			double *tmaximo = getPdvTmaximo(pdv);
			double *ttotal = getPdvTtotal(pdv);
			if(tempoAtendimento > *tmaximo){
				*tmaximo = tempoAtendimento;
			}
			*ttotal += tempoAtendimento;
			*pdvTultimoatend = (*getEventoMarcaTempo(evento))+tempoAtendimento;
			////Cliente permanece ou não pro atendimento
			*getPdvnclientes(pdv)+=1;
		}else{
			printf("cliente não atendido");
		}
	}else if(getEventoTipo(evento)=='X'){//evento de finalizacao de atendimento{
		TFimAtendimento *finalAtendimento = getCargaEvento(evento);

		TEvento *eventoChegada = NULL;

		if(!filaVazia(filaClientes)){
			eventoChegada = desenfileirar(filaClientes);

			TFimAtendimento *fm = getCargaEvento(evento);
			TPdv *pdv = encontrarpdv(area, getFimAtendimentoidPdv(fm));
			setStatusPdv(pdv, 1);
			printstatuspdv(pdv);
			executarEvento(agenda,eventoChegada,area,filaClientes);
		}else{
			printf("\n Dentro de executar evento fimAtendimento 4");
			TFimAtendimento *fm = getCargaEvento(evento);
			TPdv *pdv = encontrarpdv(area, getFimAtendimentoidPdv(fm));
			setStatusPdv(pdv, 1);
		}
	}else if(getEventoTipo(evento)=='S'){
		TSuspensao *s = getCargaEvento(evento);
		TPdv *pdv = encontrarpdv(area,getSusPdvIdv(s));
		if(getPdvSuspensao(pdv)){
			setSuspensao(pdv, 1);
		}else{
			setSuspensao(pdv, 1);
			*getEventoMarcaTempo(evento)+=getSuspensaoDuracao(s);
			agendamento(agenda, evento);
		}
		printf("///////////////////////////////////////////////////////////////////\n");
		printf("IMPRIMIR AGENDA COM NOVA SUSPENSAO");
		imprimirAgenda(agenda);
		printf("\n///////////////////////////////////////////////////////////////////");

	}else{
		printf("executarEvento Falhou");
	}
}

void avancarAgenda(TAgenda *agenda,double novoTempo,TAreaAtendimento *area,TFila *filaClientes){
	TLista *listaAgenda = getAgendaListaEventos(agenda);
	if(novoTempo<0){
		printf("\n\nESVAZIANDO AGENDA");
		TElemento *caminhador =getInicioLSE(listaAgenda);
		TEvento *evento = NULL;
		TLista *listagenda = getAgendaListaEventos(agenda);
		double tempoEvento=0;
		if(caminhador!=NULL){
			evento = caminhador->carga;
			tempoEvento = *(getEventoMarcaTempo(evento));
		}
		while(caminhador!=NULL){
			executarEvento(agenda, evento, area, filaClientes);
			desenfileirarAgenda(agenda);
			caminhador =getInicioLSE(listaAgenda);
			if(caminhador!=NULL){
				evento = caminhador->carga;
				tempoEvento = *getEventoMarcaTempo(evento);
			}
		}
		return;
	}else{
	if(listaAgenda->tamanho==0){

	}else{
		TElemento *caminhador =getInicioLSE(listaAgenda);
		TEvento *evento = NULL;
		double tempoEvento=0;
		if(caminhador !=NULL){
			evento = caminhador->carga;
			tempoEvento = *(getEventoMarcaTempo(evento));
		}

		while(caminhador!=NULL && tempoEvento<=novoTempo){

			executarEvento(agenda, evento, area, filaClientes);
			desenfileirarAgenda(agenda);
			caminhador =getInicioLSE(listaAgenda);
			if(caminhador!=NULL){
				evento = caminhador->carga;
				tempoEvento = *getEventoMarcaTempo(evento);
			}
			printf("///////////////////////////////////////////////////////////////////\n");
			printf("\nAvançando agenda, NÃO ESVAZIANDO:");
			printf("\nIMPRESSÃO DA AGENDA\n");
			    imprimirAgenda(agenda);
			    printf("\nIMPRESSÃO DA FILA DE CLIENTES\n");
			    TLista *listaa = getFilaLista(filaClientes);
			    imprimirLSE(listaa,&imprimirEvento);
			    printf("\nIMPRESSÃO DA LISTA DE PDVS nnnn para cada evento exeutado\n");
			    imprimirPdvs(area);
			    printf("\n///////////////////////////////////////////////////////////////////");
		}
	}
}

}


void preencherAreaAtendimento(TAreaAtendimento *area){
  int qntPdvsVelha,qntPdvsAtual;
  int *faVelha,*faAtual;
  int i;
  double tempoMedio,x,y,z;
  fscanf(arquivo,"%d",&qntPdvsVelha);
  faVelha = malloc(sizeof(int)*qntPdvsVelha);
  for(i=0;i<qntPdvsVelha;i++){
    printf("\nLendo pdv %d\n",i);
    fscanf(arquivo,"%d",&faVelha[i]);
  }
  fscanf(arquivo,"%d",&qntPdvsAtual);
  faAtual = malloc(sizeof(int)*qntPdvsAtual);
  for(i=0;i<qntPdvsAtual;i++){
    fscanf(arquivo,"%d",&faAtual[i]);
  }
  fscanf(arquivo,"%lf%lf%lf%lf",&tempoMedio,&x,&y,&z);
  for(i=0;i<qntPdvsVelha;i++){
    TPdv *pdv = criarPdv(tempoMedio*faVelha[i]/10.0);
    inserirPdv(area, pdv);
  }
  for(i=0;i<qntPdvsAtual;i++){
    TPdv *pdv = criarPdv(tempoMedio*faAtual[i]/10.0);
    inserirPdv(area, pdv);
  }
  addTempos(area, tempoMedio,x,y,z);
  imprimirPdvs(area);
}

void lerEventos(TAgenda *agenda,TAreaAtendimento *caixa,TFila *filaClientes){
  char tipo;
  fscanf(arquivo," %c",&tipo);
  while(tipo != 'F'){
    TEvento *eventoNovaChegada;
    if(tipo == 'C'){
    	printf("\nLendo Chegada\n");
      double tempoDeChegada,tipoCliente,qntItens,tempoPagamento;
      fscanf(arquivo,"%lf%lf%lf%lf",&tempoDeChegada,&qntItens,&tipoCliente,&tempoPagamento);
      *(getTempoAtual(caixa))= tempoDeChegada;
      printf("\nTEMPO ATUAL E TEMPO DE CHEGADA : %lf",*getTempoAtual(caixa));
      avancarAgenda(agenda,tempoDeChegada,caixa,filaClientes);
      TChegada *c= criarChegada(qntItens, tipoCliente, tempoPagamento/10.0);
      eventoNovaChegada = criarEvento(tempoDeChegada, tipo,c);
      TPdv *pdvLivre = proxPdvLivre(caixa);
      if(filaVazia(filaClientes)){
    	  if(pdvLivre!=NULL){
    		  executarEvento(agenda,eventoNovaChegada,caixa,NULL);
    	  }else{
    		  enfileirar(filaClientes,eventoNovaChegada);
    	  }
      }else{
    	  enfileirar(filaClientes,eventoNovaChegada);
      }
    }else if(tipo == 'S'){
    	printf("\nLendo Suspensao\n");
    	int idPdv;
    	double tempoInicio,durMin;
    	TEvento *eventoSuspensao;
    	TSuspensao *s;
    	fscanf(arquivo,"%lf%d%lf",&tempoInicio,&idPdv,&durMin);
    	avancarAgenda(agenda,tempoInicio,caixa,filaClientes);
    	printf("tempoatual: %lf",tempoInicio);
    	*(getTempoAtual(caixa))= tempoInicio;
    	printf("tempoatual: %lf",tempoInicio);
    	printf("\nTEMPO ATUAL : %lf",*getTempoAtual(caixa));
    	s=criarSuspensao(idPdv, durMin*60);
    	eventoSuspensao = criarEvento(tempoInicio, tipo, s);

    	executarEvento(agenda, eventoSuspensao, caixa, filaClientes);
    }else{
      printf("Tipo Inválido");
    }
  fscanf(arquivo," %c",&tipo);
  }
  printf("///////////////////////////////////////////////////////////////////");
  printf("\n\n\nESCAZIAR AGENDA E IMPRIMIR FINAL\n");
  avancarAgenda(agenda, -1, caixa, filaClientes);
  printf("\nTEMPO ATUAL : %lf",*getTempoAtual(caixa));
  printf("\nIMPRESSÃO DA AGENDA\n");
  imprimirAgenda(agenda);
  printf("\nIMPRESSÃO DA FILA DE CLIENTES\n");
  while(!filaVazia(filaClientes)){
	  TEvento *eventoCliente = desenfileirar(filaClientes);
	  imprimirEvento(eventoCliente);
  }
  printf("\nIMPRESSÃO DA LISTA DE PDVS nnnn\n");
  imprimirPdvs(caixa);
  printf("///////////////////////////////////////////////////////////////////");
}



int main() {
	FILE *arquivo;

	arquivo= fopen("text.txt","rt");

	setvbuf(stdout, 0, _IONBF, 0);
  TAgenda *agenda = criarAgenda(01,01,01);
  TAreaAtendimento *areaAtendimento = criarAreaAtendimento();
  TFila *filaClientes = criarFila();
  preencherAreaAtendimento(areaAtendimento);
  lerEventos(agenda,areaAtendimento, filaClientes);
  printf("%lf",17.5+1);

  fclose(arquivo);
  return 0;
}
