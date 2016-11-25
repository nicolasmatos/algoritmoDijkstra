typedef struct lista Lista;

Lista * criar();
void destruir(Lista * l);
void limpar(Lista * l);
void imprimir(Lista * l);

int tamanho(Lista * l);
int esta_vazia(Lista * l);
int ler_pos(Lista * l, int p);
int primeiro(Lista * l);
int ultimo(Lista * l);
int buscar(Lista * l, int v);

void escrever_pos(Lista * l, int p, int v);
void inserir_pos(Lista * l, int p, int v);
void inserir_primeiro(Lista * l, int v);
void inserir_ultimo(Lista * l, int v);
int remover_pos(Lista * l, int p);
int remover_primeiro(Lista * l);
int remover_ultimo(Lista * l);
void remover(Lista * l, int v);

void remover_todos(Lista * l, int v);

void adicionar_vertice(Lista * l, int v);
void adicionar_verticeAdj(Lista * l, int v);
void adicionar_aresta(Lista * l, int vOri, int vDest);
