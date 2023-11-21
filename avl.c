#include <stdio.h>
#include <stdlib.h>

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
void imprimirArvore(Nodo* no);
Nodo* buscarNodo(Nodo* no, int chave);
Nodo* balancear(Nodo* x);

int main() {

	Nodo* raiz = NULL;

	raiz = inserirNodo(raiz, 90);
	raiz = balancear(raiz);
	raiz = inserirNodo(raiz, 30);
	raiz = balancear(raiz);	
	raiz = inserirNodo(raiz, 80);
	raiz = balancear(raiz);	
	raiz = inserirNodo(raiz, 10);
	raiz = balancear(raiz);
	raiz = inserirNodo(raiz, 100);
	raiz = balancear(raiz);

	imprimirArvore(raiz); 
	
	return 0;
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

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para calcular e atribuir as alturas à esquerda e à direita para todos os nós da árvore
void calcularAlturas(Nodo* nodo) {
    if (nodo != NULL) {
        calcularAlturas(nodo->esquerda); // Calcula as alturas à esquerda da subárvore esquerda
        calcularAlturas(nodo->direita);  // Calcula as alturas à direita da subárvore direita

        // Calcula as alturas à esquerda e à direita para o nó atual
        nodo->altEsquerda = (nodo->esquerda != NULL) ? max(nodo->esquerda->altEsquerda, nodo->esquerda->altDireita) + 1 : 0;
        nodo->altDireita = (nodo->direita != NULL) ? max(nodo->direita->altEsquerda, nodo->direita->altDireita) + 1 : 0;
    }
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

void imprimirArvore(Nodo* no){

	if(!no) {
		return;	
	}

	imprimirArvore(no->esquerda);
	printf("at %d %d %d \n", no->chave, no->altEsquerda, no->altDireita);
	imprimirArvore(no->direita);
}

// param: raiz, chave para busca
Nodo* buscarNodo(Nodo* no, int chave) {

	if(no == NULL) {
		return NULL;
	}
	
	if(no->chave == chave) {
		return no;
	}

	if(chave > no->chave){

		return buscarNodo(no->direita, chave);
		
	} else {
		
		return buscarNodo(no->esquerda, chave);
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
	if(aux->altDireita > aux->altEsquerda) {

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
	if(aux->altDireita > aux->altEsquerda) {

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

Nodo* balancear(Nodo* x) {

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
			y = rotacionarDireita(y);
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
			y = rotacionarEsquerda(y);	
			x = rotacionarDireita(x);	
		}
	}

	calcularAlturas(x);

	return x;
}

