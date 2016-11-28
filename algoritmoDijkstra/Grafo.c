#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "Dijkstra.h"

typedef struct no No;
typedef struct vertice Vertice;
typedef struct aresta Aresta;

struct aresta {
	char rep[50];
	int peso;
};

struct vertice {
	char rep[50];
	Vertice * pred;
	int cv;
	Lista * vizinhos;
};

struct no {
	Vertice * v;
	Aresta * a;
	No * prox;
};

struct lista {
	int tam;
	No * ini, * fim;
};

struct grafo {
	Lista * v;
	Lista * visitados;
	Lista * prioridades;
};

Lista * criar() {
	Lista * l = (Lista *)malloc(sizeof(Lista));
	l->ini = NULL;
	l->fim = NULL;
	l->tam = 0;
	return l;
}

Grafo * criar_grafo() {
	Grafo * g = (Grafo *)malloc(sizeof(Grafo));
	g->v = criar ();
	g->visitados = criar();
	g->prioridades = criar();

	return g;
}

void destruir(Lista * l) {
	if (l != NULL) {
		limpar(l);
		free(l);
	}
}

void limpar(Lista * l) {
	No * aux = l->ini;
	while (aux != NULL) {
		No * aux2 = aux;
		aux = aux->prox;
		free(aux2);
	}
	l->ini = NULL;
	l->fim = NULL;
	l->tam = 0;
}

void imprimir(Lista * l) {
	No * aux = l->ini;
	printf("[ ");
	while (aux != NULL) {
		printf("%s ", aux->v->rep);
		aux = aux->prox;
	}
	printf("]\n");
}

int tamanho(Lista * l) {
	return l->tam;
}

int esta_vazia(Lista * l) {
	return tamanho(l) == 0;
}

int buscar(Lista * l, Vertice * v) {
	int i, p = 0;
	No * aux = l->ini;

	for (i = 0; i < tamanho(l); i++) {
		if (aux == NULL || !strcmp(aux->v->rep, v->rep)) {
			i = tamanho(l);
		}
		p++;
	}

	return aux != NULL ? p - 1 : -1;
}

void inserir_pos_vertice(Lista * l, int p, Vertice * v) {
	int i;
	No * aux = l->ini;
	No * aux2;
	if (p < 0 || p > tamanho(l)) {
		printf("Posicao invalida!\n");
		return;
	}
	aux2 = (No *)malloc(sizeof(No));
	aux2->v = v;
	aux2->a = NULL;
	aux2->prox = NULL;

	if (p > 0 && p < l->tam) {
		for (i = 0; i < p - 1; i++) {
			aux = aux->prox;
		}
		aux2->prox = aux->prox;
		aux->prox = aux2;
	}
	else {
		if (p == 0) {
			aux2->prox = l->ini;
			l->ini = aux2;
		}
		if (p == l->tam) {
			if (l->fim != NULL) {
				l->fim->prox = aux2;
			}
			l->fim = aux2;
		}
	}
	l->tam++;
}

void adicionar_vertice(Lista * l, Vertice * v) {
	inserir_pos_vertice(l, tamanho(l), v);
}

void inserir_vertice(Grafo * g, char rep[50]) {
	Vertice * v = (Vertice *)malloc(sizeof(Vertice));
	Vertice * vp = (Vertice *)malloc(sizeof(Vertice));
	strcpy(v->rep, rep);
	v->cv = INT_MAX;
	v->pred = NULL;
	v->vizinhos = criar();

	strcpy(vp->rep, rep);
	vp->cv = INT_MAX;
	vp->pred = NULL;
	vp->vizinhos = criar();

	adicionar_vertice(g->v, v);
	adicionar_vertice(g->prioridades, vp);
}

void inserir_pos_aresta(Lista * l, int p, Aresta * a) {
	int i;
	No * aux = l->ini;

	if (p < 0 || p > tamanho(l)) {
		printf("Posicao invalida!\n");
		return;
	}

	for (i = 0; i < p - 1; i++) {
		aux = aux->prox;
	}
	aux->a = a;
}

void adicionar_aresta(Lista * l, Aresta * a) {
	inserir_pos_aresta(l, tamanho(l), a);
}

void inserir_aresta(char rep[50], Vertice * v1, Vertice * v2, int v) {
	Aresta * a = (Aresta *)malloc(sizeof(Aresta));
	
	strcpy(a->rep, rep);
	adicionar_vertice(v1->vizinhos, v2);
	adicionar_vertice(v2->vizinhos, v1);
	a->peso = v;

	adicionar_aresta(v1->vizinhos, a);
	adicionar_aresta(v2->vizinhos, a);
}

void inserir_aresta_rep(Grafo * g, char rep[50], char v1O[50], char v2O[50], int v) {
	int i;
	No * aux = g->v->ini;
	Vertice * v1 = NULL;
	Vertice * v2 = NULL;
	for (i = 0; i < tamanho(g->v); i++) {
		if (!strcmp(aux->v->rep, v1O)) {
			v1 = aux->v;
			i = tamanho(g->v);
		}

		aux = aux->prox;
	}
	aux = g->v->ini;
	for (i = 0; i < tamanho(g->v); i++) {
		if (!strcmp(aux->v->rep, v2O)) {
			v2 = aux->v;
			i = tamanho(g->v);
		}

		aux = aux->prox;
	}

	inserir_aresta(rep, v1, v2, v);
}

void remover_aresta_rep(Grafo * g, char rep[50]) {
	int i, j;
	No * aux = g->v->ini;
	No * aux1 = NULL;
	Aresta * a = NULL;
	Vertice * v1 = NULL, *v2 = NULL;

	int ctrl = 0;

	for (i = 0; i < tamanho(g->v); i++) {

		aux1 = aux->v->vizinhos->ini;
		int x = tamanho(aux->v->vizinhos);
		for (j = 0; j < x; j++) {
			if (!strcmp(aux1->a->rep, rep)) {
				a = aux1->a;
				aux1->a = NULL;
				j = tamanho(aux1->v->vizinhos);
				ctrl++;
				if (ctrl == 1) v1 = aux1->v;
				else if (ctrl == 2) v2 = aux1->v;
			}

			aux1 = aux1->prox;
		}

		aux = aux->prox;
	}
	remover(v1->vizinhos, v2);
	remover(v2->vizinhos, v1);

	free(a);
}

void remover_vertice_rep(Grafo * g, char rep[50]) {
	int i, j;
	No * aux = g->v->ini;
	No * aux1 = NULL;
	Vertice * v = NULL;
	for (i = 0; i < tamanho(g->v); i++) {
		if (!strcmp(aux->v->rep, rep)) {
			v = aux->v;
			aux1 = aux->v->vizinhos->ini;

			int x = tamanho(aux->v->vizinhos);

			for (j = 0; j < x; j++) {
				remover_aresta_rep(g, aux1->a->rep);
				aux1 = aux->v->vizinhos->ini;
			}
			i = tamanho(g->v);
		}
		aux = aux->prox;
	}
	remover(g->v, v);

	free(v);
}

Vertice * remover_pos(Lista * l, int p) {
	int i;
	No * aux = l->ini;
	No * aux2;
	if (p < 0 || p >= tamanho(l)) {
		printf("Posicao invalida!\n");
		return;
	}
	if (p > 0) {
		for (i = 0; i < p - 1; i++) {
			aux = aux->prox;
		}
		aux2 = aux->prox;
		aux->prox = aux2->prox;
	}
	else {
		aux = NULL;
		aux2 = l->ini;
		l->ini = aux2->prox;
	}
	if (p == l->tam - 1) {
		l->fim = aux;
	}

	Vertice * v = aux2->v;
	free(aux2);
	l->tam--;
	return v;
}

Vertice * remover(Lista * l, Vertice * v) {
	int p = buscar(l, v);
	if (p != -1) {
		return remover_pos(l, p);
	}
}

void imprimir_grafo(Grafo * g) {
	int i, j;
	No * aux = g->v->ini;
	No * aux1 = NULL;
	printf("------------------------\n");
	for (i = 0; i < tamanho(g->v); i++) {
		printf("Vertice: %s\n", aux->v->rep);
		aux1 = aux->v->vizinhos->ini;
		for (j = 0; j < tamanho(aux->v->vizinhos); j++) {
			printf("	Vizinhos: %s \n", aux1->v->rep);
			printf("	Arestas: %s->%d \n", aux1->a != NULL ? aux1->a->rep : "", aux1->a != NULL ? aux1->a->peso : "");
			aux1 = aux1->prox;
		}
		aux = aux->prox;
		printf("------------------------\n\n");
	}
	
}

//Dijkstra

Vertice * buscar_menor_vp(Grafo * g) {
	int i;
	No * aux = g->prioridades->ini->prox;
	Vertice * menor = g->prioridades->ini->v;

	for (i = 0; i < tamanho(g->prioridades); i++) {
		if (aux->prox != NULL) {
			if (aux->v->cv < menor->cv) {
				menor = aux->v;
			}
			aux = aux->prox;
		}
	}

	return menor;
}

Vertice * buscar_vp(Grafo * g, Vertice * v) {
	int i;
	No * aux = g->prioridades->ini;
	for (i = 0; i < tamanho(g->prioridades); i++) {
		if (strcmp(aux->v->rep, v->rep)) {
			return aux->v;
		}
		aux = aux->prox;
	}
	return NULL;
}

void processa_irmaos(Grafo * g, Vertice * v) {
	Vertice * vp = NULL;
	No * aux = v->vizinhos->ini;
	int i;
	for (i = 0; i < tamanho(v->vizinhos); i++) {
		int chave = aux->v->cv;
		int peso = aux->a->peso;
		vp = buscar_vp(g, aux->v);
		if (chave != INT_MAX) {
			if (v->cv + peso < chave) {
				aux->v->cv = v->cv + peso;
				aux->v->pred = v;
				vp->cv = v->cv + peso;
				vp->pred = v;
			}
		}
		else {
			aux->v->cv = v->cv + peso;
			aux->v->pred = v;
			vp->cv = v->cv + peso;
			vp->pred = v;
		}
		aux = aux->prox;
	}
}

Grafo * caminho_minimo(Grafo * g, No * origem, No * destino) {
	Vertice * menor;
	Vertice * vp;
	No * aux = origem;
	aux->v->cv = 0;

	while (!strcmp(aux->v->rep, destino->v->rep)) {
		processa_irmaos(g, aux->v);
		menor = buscar_menor_vp(g);
		adicionar_vertice(g->visitados, aux->v);
		vp = buscar_vp(g, aux->v);
		remover(g->prioridades, vp);
		aux->v = menor;
	}
}