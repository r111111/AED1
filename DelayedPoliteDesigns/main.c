#include "stdio.h"
#include "stdlib.h"
#include "caixa.h"
#include "lse.neutra.h"
#include "agenda.h"

void preencherAreaAtendimento(TAreaAtendimento *area){
  int qntPdvsVelha,qntPdvsAtual;
  int *faVelha,*faAtual;
  int i;
  double tempoMedio,x,y,z;
  printf("holy shit");
  scanf("%d",&qntPdvsVelha);
  faVelha = malloc(sizeof(int)*qntPdvsVelha);
  for(i=0;i<qntPdvsVelha;i++){
    printf("\nLendo pdv %d",i);
    scanf("%d",&faVelha[i]);
  }
  scanf("%d",&qntPdvsAtual);
  faAtual = malloc(sizeof(int)*qntPdvsAtual);
  for(i=0;i<qntPdvsAtual;i++){
    scanf("%d",&faAtual[i]);
  }
  scanf("%lf%lf%lf%lf",&tempoMedio,&x,&y,&z);
  for(i=0;i<qntPdvsVelha;i++){
    TPdv *pdv = criarPdv(tempoMedio*faVelha[i]);
    inserirPdv(area, pdv);
  }
  for(i=0;i<qntPdvsAtual;i++){
    TPdv *pdv = criarPdv(tempoMedio*faAtual[i]);
    inserirPdv(area, pdv);
  }
  addTempos(area, tempoMedio,x,y,z);
  imprimirPdvs(area);
}

void lerEventos(TAgenda *agenda,TAreaAtendimento *caixa){
  char tipo;
  int marcaDeTempo,ultimoCaixaLivre;
  printf("LE\n");
  scanf(" %c",&tipo);
  while(tipo != 'F'){
    TEvento *evento;
    if(tipo == 'C'){
      int tempoDeChegada,tipoCliente,qntItens,tempoPagamento;
      scanf("%d%d%d%d",&tempoDeChegada,&qntItens,&tipoCliente,&tempoPagamento);
      TChegada *c= criarChegada(qntItens, tipoCliente, tempoPagamento);
      //passarTempo();
      evento = criarEvento(tempoDeChegada, tipo,c);
    }else if(tipo == 'S'){
      
   }else{
      printf("Tipo Inválido");
    }
  scanf(" %c",&tipo);
  }
  imprimirAgenda(agenda);
}
int main() {
  printf("aaa");
}
