typedef struct elemento{
  void *carga;
  struct elemento *prox;
}TElemento;

typedef struct lista{
	  int tamanho;
	  TElemento *inicio;
	  TElemento *fim;
	}TLista;
typedef int(*TComparador)(void*,void*);
typedef int(*TCondicao)(void*);
typedef void (*TImpressora)(void*);
void inserirFinalLSE(TLista *l,void *carganova);
void inserirInicioLSE(TLista *l,void *carganova);
void *removerInicioLSE(TLista *l);
TLista *criarLista();
void *removerElemento(TLista *lst, int posicao);
int tamanhoLista(TLista *lst);
void inserirOrdenadoLSE(TLista *lst, void *carganova,TComparador comparador);
void imprimirLSE(TLista *lst,TImpressora impressora);
void *temNaLista(TLista *lst,TCondicao cond);
void *getInicioLSE(TLista *lst);
TElemento *proxElemento(TElemento *e);
int listaVazia(TLista *lst);

