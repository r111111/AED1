
typedef struct agenda TAgenda;
typedef struct evento TEvento;
typedef struct suspensao TSuspensao;
typedef struct finalizacao TFinal;
typedef struct chegada TChegada;
typedef struct fimatend TFimAtendimento;
TEvento *criarEvento(double temp, char tip,void *carg);
TAgenda *criarAgenda(int dia,int mes, int ano);
TChegada *criarChegada(double nItens,int tipoChegada,double tempoPag);
TSuspensao *criarSuspensao(int idPdv, int dur);
TFimAtendimento *criarFimAtendimento();
char tipoDeEvento(TEvento *e);
void agendamento(TAgenda *a,void *evento);
void imprimirAgenda(TAgenda *a);
void imprimirChegada(void *chegada);
void imprimirEvento(void *e);
int comparaEvento(void *evento1, void *evento2);

double *getChegadatpag(TChegada *c);

double *getEventoMarcaTempo(TEvento *e);
void *getCargaEvento(TEvento *e);
char getEventoTipo(TEvento *evento);
void *getAgendaListaEventos(TAgenda *agenda);

void *desenfileirarAgenda(TAgenda *agenda);

void *getFimAtendimentoTempo(TFimAtendimento *fimatend);
int getFimAtendimentoidPdv(TFimAtendimento *fimatend);

int getSusPdvIdv(TSuspensao *s);
double getSuspensaoDuracao(TSuspensao *s);

void *criarFinalizacao();
double *getnIntensCliente(TChegada *cl);

int *getTipoCliente(TChegada *cl);
