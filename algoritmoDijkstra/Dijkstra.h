typedef struct grafo Grafo;
typedef struct vertice Vertice;

Grafo * caminho_minimo(Grafo * g, Vertice * origem, Vertice * destino);
void processa_irmaos(Vertice * v);