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
void recalcularAlturas(Nodo* raiz);
Nodo* inserirNodo(Nodo* no, int chave);
void imprimirArvore(Nodo* no, FILE* saida);
Nodo* buscarNodo(Nodo* no, int chave, int* qntComparacoes);
void verificarDesbalanceamentos(Nodo* raiz, Nodo** no);
Nodo* balancear(Nodo* x);
void imprimir(Nodo* no);
