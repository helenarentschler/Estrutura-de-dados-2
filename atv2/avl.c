#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int maximo(int a, int b) {

	return a > b ? a : b;
}

int calcularAltura(Nodo* raiz) {

	if(!raiz) {
		return -1;
	}

	return 1 + maximo(calcularAltura(raiz->direita), calcularAltura(raiz->esquerda)) ;
}

void recalcularAlturas(Nodo* raiz) {

	if(!raiz) {
		return;	
	}

	raiz->altDireita = 1 + calcularAltura(raiz->direita);
	raiz->altEsquerda = 1 + calcularAltura(raiz->esquerda);

	recalcularAlturas(raiz->esquerda);
	recalcularAlturas(raiz->direita);
}

Nodo* criarNodo(int chave){

	Nodo* novo = (Nodo*) malloc(sizeof(Nodo));

	if(novo) {
		novo->chave = chave;
		novo->altEsquerda = 0;
		novo->altDireita = 0;
		novo->esquerda = NULL;
		novo->direita = NULL;
	}

	return novo;
}


Nodo* inserirNodo(Nodo* no, int chave) {

	if (no == NULL){
	
        return criarNodo(chave);
    }

	if(chave > no->chave){
	
		no->direita = inserirNodo(no->direita, chave);

	} else {

		no->esquerda = inserirNodo(no->esquerda, chave);
	}

	return no;
}

void imprimirArvore(Nodo* no, FILE* saida){

	if(!no) {
		return;	
	}

	imprimirArvore(no->esquerda, saida);
	fprintf(saida,"Chave:%d | Alt esq: %d | Alt dir: %d \n", no->chave, no->altEsquerda, no->altDireita);
	imprimirArvore(no->direita, saida);
}

void imprimir(Nodo* no) {

	if(!no) {
		return;	
	}

	imprimir(no->esquerda);
	printf("Chave:%d | Alt esq: %d | Alt dir: %d \n", no->chave, no->altEsquerda, no->altDireita);
	imprimir(no->direita);
}

// param: raiz, chave para busca
Nodo* buscarNodo(Nodo* no, int chave, int* qntComparacoes) {

	(*qntComparacoes)++;

	if(no == NULL) {
		return NULL;
	}
	
	if(no->chave == chave) {
		return no;
	}
	
	if(chave > no->chave){

		return buscarNodo(no->direita, chave, qntComparacoes);
		
	} else {
		
		return buscarNodo(no->esquerda, chave,qntComparacoes);
	}
}

Nodo* rotacionarEsquerda(Nodo* x){

	//rotacionando

	Nodo* y = x->direita;
	Nodo* aux = y->esquerda;
	x->direita = aux;
	y->esquerda = x;

	//ajuste de alturas

	//atualiza altura direita do x de acordo com o novo filho a direita (aux)
	if(aux == NULL) {

		x->altDireita = 0;
			
	} else if(aux->altDireita > aux->altEsquerda) {

		x->altDireita = aux->altDireita + 1;

	} else {

		x->altDireita = aux->altEsquerda + 1;	
	}

	//atualiza altura esquerda do y de acordo com o novo filho a esquerda (x)
	if(x->altDireita > x->altEsquerda) {

		y->altEsquerda = x->altDireita + 1;

	} else {

		x->altEsquerda = x->altEsquerda + 1;	
	}

	//retorna nova raiz (y)
	return y;
}

Nodo* rotacionarDireita(Nodo* x){

	//rotacionando
	Nodo* y = x->esquerda;
	Nodo* aux = y->direita;
	x->esquerda = aux;
	y->direita = x;

	//ajuste de alturas

	//atualiza altura esquerda do x de acordo com o novo filho a esquerda (aux)
	if(aux == NULL) {
	
		x->altEsquerda = 0;
				
	} else if(aux->altDireita > aux->altEsquerda) {

		x->altEsquerda = aux->altDireita + 1;

	} else {

		x->altEsquerda = aux->altEsquerda + 1;	
	}

	//atualiza altura direita do y de acordo com o novo filho a diteira (x)
	if(x->altDireita > x->altEsquerda) {

		y->altDireita = x->altDireita + 1;

	} else {

		x->altDireita = x->altEsquerda + 1;	
	}

	//retorna nova raiz (y)
	return y;
}


void verificarDesbalanceamentos(Nodo* raiz, Nodo** no) {

	if(!*no){
		return;
	}
	
	verificarDesbalanceamentos(raiz, &(*no)->esquerda);
	verificarDesbalanceamentos(raiz, &(*no)->direita);

	int fb = (*no)->altDireita - (*no)->altEsquerda;
	
	if(abs(fb) == 2) {
		*no = balancear(*no);			
		recalcularAlturas(raiz);
	}
}


Nodo* balancear(Nodo* x) {

	if(!x) {
		return x;
	}
	
	int fbX = x->altDireita - x->altEsquerda;

	//rotaçao para esquerda	
	if(fbX == 2) {

		//raiz da subarvore desbalanceada (direita)
		Nodo* y = x->direita;

		int fbY = y->altDireita - y->altEsquerda;
		
		if(fbY >= 0) {
			//rotaçao simples
			x = rotacionarEsquerda(x);

		} else {
			//rotaçao dupla
			x->direita = rotacionarDireita(y);
			x = rotacionarEsquerda(x);	
		}
	}
	
	//rotaçao para direita
	if(fbX == -2) {
	
		//raiz da subarvore desbalanceada (esquerda)
		Nodo* y = x->esquerda;

		int fbY = y->altDireita - y->altEsquerda;

		if(fbY <= 0) {
			//rotaçao simples
			x = rotacionarDireita(x);
			
		} else {
			//rotaçao dupla
			x->esquerda = rotacionarEsquerda(y);	
			x = rotacionarDireita(x);	
		}
	}

	return x;
}

