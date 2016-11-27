#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/*
CV v			-> Cria um vértice com o identificador v
--------------------------------------------------------------------------------------------------------------
RV v			-> Remove o vértice identificado por v
--------------------------------------------------------------------------------------------------------------
CA a v1 v2 x	-> Cria uma aresta com o identificador a incidindo nos vértices de identificadores v1 e v2. O
                valor armazenado na aresta é um número inteiro especificado por x
				--------------------------------------------------------------------------------------------------------------
RA a			-> Remove a aresta identificada por a
--------------------------------------------------------------------------------------------------------------
TA a x			-> Troca o valor armazenado na aresta de identificador a pelo valor x
--------------------------------------------------------------------------------------------------------------
IG				-> imprime o grafo na tela. Para definir a forma que seu programa deve imprimir o grafo na
				tela, considere um grafo com n vértices, m arestas, identificadores de vértices v1, v2, ...,
				vn, identificadores de arestas a1, a2, ..., am com respectivos valores x1, x2, ..., xm. Assuma
				ainda que ui e wi representam os identificadores dos vértices em que a aresta ai incide,
				sendo extraídos do conjunto {v1, ..., vn}. A saída do comando deve ser a seguinte:
				Qtd de vértices: n
				v1 v2 ... vn
				Qtd de arestas: m
				a1 u1 w1 x1
				a2 u2 w2 x2
				...
				am um wm xm
				Os identificadores de vértices devem ser impressos em ordem crescente: v1 < v2 < ... < vn
				Os identificadores de arestas devem ser impressos em ordem crescente: a1 < a2 < ... < am
				Os identificadores de vértices em que a aresta ai incide devem ser impressos em ordem
				crescente: ui < wi
--------------------------------------------------------------------------------------------------------------
CM v1 v2		-> Determina e imprime o caminho mínimo entre o vértice de identificador v1 e o vértice de
				identificador v2. A saída do comando deve ser a seguinte:
				Custo: c
				Caminho: v1 ... vi vj ... v2
				--------------------------------------------------------------------------------------------------------------
FM				-> Termina a execução do seu programa. Todas as estruturas dinâmicas devem ser
				desalocadas e seu programa deve encerrar.
*/

void carregaAlunos(FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char comando[50];
		char vertice1[50];
		char vertice2[50];
		char aresta[50];
		char valorAresta[50];
		int va = 0;

		while (c != ' ') {
			comando[i] = c;
			i++;
			c = fgetc(fp);
		}
		comando[i] = '\0';
		c = fgetc(fp);
		i = 0;

		if (strcmp(comando, "CV")) {
			while (c != '\n') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			//inserir_vertice(vertice1);
		}

		else if (strcmp(comando, "RV")) {
			while (c != '\n') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			//remover_vertice(vertice1);
		}

		else if (strcmp(comando, "CA")) {
			while (c != ' ') {
				aresta[i] = c;
				i++;
				c = fgetc(fp);
			}
			aresta[i] = '\0';
			c = fgetc(fp);
			i = 0;

			while (c != ' ') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			while (c != ' ') {
				vertice2[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice2[i] = '\0';
			c = fgetc(fp);
			i = 0;

			while (c != '\n') {
				valorAresta[i] = c;
				i++;
				c = fgetc(fp);
			}
			valorAresta[i] = '\0';
			c = fgetc(fp);
			i = 0;

			va = atoi(valorAresta);

			//inserir_aresta (aresta, vertice1, vertice2, va);
		}

		else if (strcmp(comando, "RA")) {
			while (c != '\n') {
				aresta[i] = c;
				i++;
				c = fgetc(fp);
			}
			aresta[i] = '\0';
			c = fgetc(fp);
			i = 0;

			//remover_aresta(aresta);
		}

		else if (strcmp(comando, "TA")) {
			while (c != ' ') {
				aresta[i] = c;
				i++;
				c = fgetc(fp);
			}
			aresta[i] = '\0';
			c = fgetc(fp);
			i = 0;

			while (c != '\n') {
				valorAresta[i] = c;
				i++;
				c = fgetc(fp);
			}
			valorAresta[i] = '\0';
			c = fgetc(fp);
			i = 0;

			va = atoi(valorAresta);

			//atualizar_valor_aresta (aresta, va);
		}

		else if (strcmp(comando, "IG")) {
			//imprimir_grafo();
		}

		else if (strcmp(comando, "CM")) {
			while (c != ' ') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			while (c != ' ') {
				vertice2[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice2[i] = '\0';
			c = fgetc(fp);
			i = 0;

			//caminho_minimo(vertice1, vertice2);
		}

		else if (strcmp(comando, "FM")) {
			//limpar tudo e sair
		}

		c = fgetc(fp);
	}
	fclose(fp);
}

int chamaArquivo(char arquivo[]) {
	char caminho[100];
	strcpy(caminho, "Arquivos\\");
	strcat(caminho, arquivo);
	strcat(caminho, ".txt");

	FILE * fp;
	fp = fopen(caminho, "r");
	if (fp == NULL) {
		printf("\nErro na abertura do arquivo: %s\n", arquivo);
		printf("OBS: Verifique o nome do arquivo\n\n");
		return 1;
	}
	else {
		printf("Carregando ...\n\n");
		carregaAlunos(fp);
	}
}

int main() {
	Lista * l = criar();

	adicionar_vertice(l, 1);
	adicionar_vertice(l, 2);
	adicionar_vertice(l, 3);
	adicionar_vertice(l, 4);
	imprimir(l);

	destruir(l);
	int opcao = 0, menu = 0;
	char comando[50];
	char arquivoCarregado[50];

	while (menu != 1 && menu != 2) {
		printf("================================Menu de opcoes================================\n");
		printf("1\. Carregar de arquivo\n"
			"2\. Interar via prompt\n");
		printf("===============================================================================\n");
		printf("\nQual opcao do menu deseja executar?\n");
		scanf("%d", &menu);
		if (menu == 1) {
			system("cls");
			printf("--------------------------\n"
				"|                        |\n"
				"|   Carregar de arquivo  |\n"
				"|                        |\n"
				"--------------------------\n");
			fflush(stdin);
			printf("Nome do arquivo a ser carregado: ");
			scanf("%s", arquivoCarregado);

			menu = chamaArquivo(arquivoCarregado) == 1 ? 0 : menu;
		}
		else if (menu == 2) {
			while (opcao != 1) {
				gets(comando);
				if (strcmp(comando, "CV")) {
					printf("Criar vertice");
				}

				else if (strcmp(comando, "RV")) {
					printf("Rmover vertice");
				}

				else if (strcmp(comando, "CA")) {
					printf("Criar aresta");
				}

				else if (strcmp(comando, "RA")) {
					printf("Remover aresta");
				}

				else if (strcmp(comando, "TA")) {
					printf("Trocar valor da aresta");
				}

				else if (strcmp(comando, "IG")) {
					printf("Imprimir grafo");
				}

				else if (strcmp(comando, "CM")) {
					printf("Caminho minimo");
				}

				else if (strcmp(comando, "FM")) {
					system("cls");
					printf("\n\n============================");
					printf("A operacao foi encerrada.");
					printf("===========================\n\n");
					opcao = 1;
				}

				else {
					system("cls");
					printf("\n=============================");
					printf("Operacao invalida.");
					printf("================================\n");
				}
			}
		}

		else {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================\n");
		}
	}
	
	//destruir(a);
	system("pause");
}