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

int calcularAltura(Nodo* no) {

	// se foi enviado NULL, quer dizer que o no pai tem altura 0 (-1 +1)
	if(!no) {
		return -1;
	}

	// se o no nao tem filhos, retorna 0 (sua propria altura é 0)
	if(!no->esquerda && !no->direita) {
		return 0;
	}

	int soma_esq = 1 + calcularAltura(no->esquerda);
	int soma_dir = 1 + calcularAltura(no->direita);

	// envia o valor maior de altura da subarvore
	return soma_esq > soma_dir ?  soma_esq :  soma_dir;
}


Nodo* inserirNodo(Nodo* no, int chave) {

	if (no == NULL){
	
        return criarNodo(chave);
    }

	if(chave > no->chave){
	
		no->direita = inserirNodo(no->direita, chave);
		(no->altDireita)++;

	} else {

		no->esquerda = inserirNodo(no->esquerda, chave);
		(no->altEsquerda)++;
	}

	return no;
}

void imprimirArvore(Nodo* no){

	if(!no) {
		return;	
	}

	imprimirArvore(no->esquerda);
	printf("%d %d %d \n", no->chave, no->altEsquerda, no->altDireita);
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

	return x;
}

