#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	int chave;
	struct No* direita;
	struct No* esquerda;
	struct No* pai;
} Nodo;

Nodo* criarNodo(int chave) {

	Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));

	if(nodo) {

		nodo->chave = chave;
		nodo->esquerda = NULL;
		nodo->direita = NULL;
		nodo->pai = NULL;
	} 
}

int encontrarNivel(Nodo* no, Nodo* aux, int nivel) {

	if (no->chave == aux->chave) {
		
		return nivel;
	}

	if(aux == NULL) {

		return -1;
	}

	int nivelEsquerda = encontrarNivel(no, aux->esquerda, nivel + 1);
	int nivelDireita = encontrarNivel(no, aux->direita, nivel + 1);
}

int main() {

	Nodo* raiz = criarNodo(0);

	raiz->direita = criarNodo(1);
	raiz->esquerda = criarNodo(2);
	raiz->esquerda->direita = criarNodo(3);

	int nivel = encontrarNivel(raiz->esquerda->direita, raiz, 0);

	return 0;
}