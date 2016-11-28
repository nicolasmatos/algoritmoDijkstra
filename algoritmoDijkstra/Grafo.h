typedef struct lista Lista;
typedef struct grafo Grafo;
typedef struct vertice Vertice;
typedef struct aresta Aresta;

Lista * criar();
Grafo * criar_grafo();
void destruir(Lista * l);
void limpar(Lista * l);
void imprimir(Lista * l);

int tamanho(Lista * l);
int esta_vazia(Lista * l);
int buscar(Lista * l, Vertice * v);

Vertice * remover(Lista * l, Vertice * v);

void inserir_vertice(Grafo * g, char rep[50]);
void adicionar_vertice(Lista * l, Vertice * v);
void adicionar_vertice_primeiro(Lista * l, Vertice * v);
void adicionar_aresta(Lista * l, Aresta * a);
void inserir_aresta_rep(Grafo * g, char rep[50], char v1O[50], char v2O[50], int v);
void remover_aresta_rep(char rep[50]);
void remover_vertice_rep(char rep[50]);
void atualizar_valor_aresta(Grafo * g, char rep[50], int v);
void caminho_minimo_rep(Grafo * g, char origem[50], char destino[50]);