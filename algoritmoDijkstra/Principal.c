#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void carregaAlunos(Grafo * g, FILE * fp) {
	int i = 0;
	char c = fgetc(fp);

	while (c != EOF) {
		char comando[50];
		char vertice1[50];
		char vertice2[50];
		char aresta[50];
		char valorAresta[50];
		int va = 0;

		while (c != ' ' && c != '\n') {
			comando[i] = c;
			i++;
			c = fgetc(fp);
		}
		comando[i] = '\0';
		c = fgetc(fp);
		i = 0;
		
		if (!strcmp(comando, "CV")) {
			while (c != '\n') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			inserir_vertice(g, vertice1);
		}

		else if (!strcmp(comando, "RV")) {
			while (c != '\n') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			remover_vertice_rep(g, vertice1);
		}

		else if (!strcmp(comando, "CA")) {
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

			inserir_aresta_rep (g, aresta, vertice1, vertice2, va);
		}

		else if (!strcmp(comando, "RA")) {
			while (c != '\n') {
				aresta[i] = c;
				i++;
				c = fgetc(fp);
			}
			aresta[i] = '\0';
			c = fgetc(fp);
			i = 0;

			remover_aresta_rep(g, aresta);
		}

		else if (!strcmp(comando, "TA")) {
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

			atualizar_valor_aresta (g, aresta, va);
		}

		else if (!strcmp(comando, "IG")) {
			imprimir_grafo(g);
		}

		else if (!strcmp(comando, "CM")) {
			while (c != ' ') {
				vertice1[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice1[i] = '\0';
			c = fgetc(fp);
			i = 0;

			while (c != '\n') {
				vertice2[i] = c;
				i++;
				c = fgetc(fp);
			}
			vertice2[i] = '\0';
			c = fgetc(fp);
			i = 0;

			caminho_minimo_rep(g, vertice1, vertice2);
		}

		else if (!strcmp(comando, "FM")) {
			//limpar tudo e sair
		}

		//c = fgetc(fp);
	}
	fclose(fp);
}

int chamaArquivo(Grafo * g, char arquivo[]) {
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
		carregaAlunos(g, fp);
	}
}

int main() {
	Grafo * g = criar_grafo();

	int opcao = 0, opcao2 = 0, menu = 0;
	char comando[50];
	char arquivoCarregado[50];

	while (menu != 3) {
		printf("================================Menu de opcoes================================\n");
		printf("1\. Carregar de arquivo\n"
			   "2\. Interar via prompt\n"
		       "3\. Finalizar\n");
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

			menu = chamaArquivo(g, arquivoCarregado) == 1 ? 0 : menu;
		}
		else if (menu == 2) {
			while (opcao != 8) {
				printf("================================Menu de opcoes================================\n");
				printf("1\. Criar vertice\n"
					   "2\. Remover vertice\n"
					   "3\. Criar aresta\n"
					   "4\. Remover aresta\n"
					   "5\. Trocar valor aresta\n"
					   "6\. Imprimir grafo\n"
					   "7\. Caminho minimo\n"
					   "8\. Finalizar\n");
				printf("===============================================================================\n");
				printf("\nQual opcao do menu deseja executar?\n");
				scanf("%d", &opcao2);
				if (opcao2 == 1) {
					char vertice1[50];
					printf("Vertice: ");
					scanf("%s", &vertice1);
					inserir_vertice(g, vertice1);
				}

				else if (opcao2 == 2) {
					char vertice1[50];
					printf("Vertice: ");
					scanf("%s", &vertice1);
					remover_vertice_rep(g, vertice1);
				}

				else if (opcao2 == 3) {
					char aresta[50];
					char vertice1[50];
					char vertice2[50];
					int va;
					printf("Aresta: ");
					scanf("%s", &aresta);

					printf("Vertice 1: ");
					scanf("%s", &vertice1);

					printf("Vertice 2: ");
					scanf("%s", &vertice2);

					printf("Valor da aresta: ");
					scanf("%d", &va);
					inserir_aresta_rep(g, aresta, vertice1, vertice2, va);
				}

				else if (opcao2 == 4) {
					char aresta[50];
					printf("Aresta: ");
					remover_aresta_rep(g, aresta);
				}

				else if (opcao2 == 5) {
					char aresta[50];
					int va;
					printf("Aresta: ");
					scanf("%s", &aresta);

					printf("Valor da aresta: ");
					scanf("%d", &va);
					atualizar_valor_aresta(g, aresta, va);
				}

				else if (opcao2 == 6) {
					imprimir_grafo(g);
				}

				else if (opcao2 == 7) {
					char vertice1[50];
					char vertice2[50];

					printf("Vertice 1: ");
					scanf("%s", &vertice1);

					printf("Vertice 2: ");
					scanf("%s", &vertice2);

					caminho_minimo_rep(g, vertice1, vertice2);
				}

				else if (opcao2 == 8) {
					system("cls");
					printf("\n\n============================");
					printf("A operacao foi encerrada.");
					printf("===========================\n\n");
					//encerrar(g);
				}

				else {
					system("cls");
					printf("\n=============================");
					printf("Operacao invalida.");
					printf("================================\n");
				}
			}
		}
		else if (menu == 3) {
			system("cls");
			printf("\n\n============================");
			printf("A operacao foi encerrada.");
			printf("===========================\n\n");
			//encerrar(g);
		}
		
		else {
			system("cls");
			printf("\n=============================");
			printf("Operacao invalida.");
			printf("================================\n");
		}
	}
	
	system("pause");
}