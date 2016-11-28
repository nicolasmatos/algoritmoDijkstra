#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dijkstra.h"
#include "Grafo.h"
#include "Grafo.c"


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