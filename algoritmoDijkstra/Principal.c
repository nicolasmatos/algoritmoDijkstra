#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(int argc, char *argv[]) {

	Lista * l = criar();

	adicionar_vertice(l, 1);
	adicionar_vertice(l, 2);
	adicionar_vertice(l, 3);
	adicionar_vertice(l, 4);
	imprimir(l);

	destruir(l);

	system("pause");
	return 0;
}