#include <stdio.h>

typedef struct No {

	int chave;
	int altEsquerda;
	int altDireita;
	struct No* esquerda;
	struct No* direita;
} Nodo;

Nodo* criarNodo(int chave);
int calcularAltura(Nodo* no);
Nodo* inserirNodo(Nodo* no, int chave);
void imprimirArvore(Nodo* no, FILE* saida);
Nodo* buscarNodo(Nodo* no, int chave, int* qntComparacoes);
Nodo* balancear(Nodo* x);
