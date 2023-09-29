#include <stdio.h>
#include <stdlib.h>

typedef struct No {

	int chave;
	int altEsquerda;
	int altDireita;
	struct No* esquerda;
	struct No* direita;
} Nodo;


Nodo* criarNodo(int chave){

	Nodo* novo = (Nodo*) malloc(sizeof(Nodo));

	if(novo) {
		novo->chave = chave;
		novo->fatorB = 0;
		novo->esquerda = NULL;
		novo->direita = NULL;
		novo->pai = NULL;
	}

	return novo;
}

//recalcular alturar na volta da recursao
Nodo* inserirNodo(Nodo* no, int chave) {

	//nodo nulo, retorna endereço para novo nodo criado
	if (no == NULL){
        return criarNodo(chave);
    }

	//se a chave enviada for maior que o nodo
	if(chave > no->chave){
		//nodo->direita recebe chamada recursiva
		no->direita = inserirNodo(no->direita, chave);
		//recursao resolvida: define o pai do novo nodo
		no->direita->pai = no;
	} else {
		//o mesmo para a esquerda
		no->esquerda = inserirNodo(no->esquerda, chave);	
		no->esquerda->pai = no;
	}

	//retorna o nodo para as execuçoes anteriores, ja que o nodo na execuçao posterior
	//é sempre o filho da anterior
	return no;
}

void imprimirArvore(Nodo* no){

	if(!no) {
		return;	
	}

	imprimirArvore(no->esquerda);
	printf("Chave: %d ---", no->chave);
	imprimirArvore(no->direita);
}

// param: raiz, chave para busca
Nodo* buscarNodo(Nodo* no, int chave) {

	if(no->chave == chave) {
		return no;
	}

	if(chave > no->chave){

		if(!no->direita) {
			return NULL;
		}

		buscarNodo(no->direita, chave);
		
	} else {

		if(!no->esquerda) {
			return NULL;
		}
		
		buscarNodo(no->esquerda, chave);
	}
}


int main() {

	Nodo* arvore = criarNodo(10);
	
	int op, chave;

	while(op != 5) {

		printf("Escreva a opçao desejada: \n");
		printf("1 - Inserçao\n");
		printf("2 - Busca \n");
		printf("3 - Remoçao \n");
		printf("4 - Imprimir arvore \n");
		printf("5 - Sair \n");
		
		scanf("%d", &op);

		switch(op) {
			case 1:
				printf("Chave para inserir: ");
				scanf("%d", &chave);
				inserirNodo(arvore, chave);
				calcularFatorB(arvore);
			break;
			case 2:
				printf("Chave para buscar: ");
				scanf("%d", &chave);
				Nodo* achado = buscarNodo(arvore, chave);

				if(achado) {
					printf("endereço: %p", achado);
				} else {
					printf("nao foi encontrado");
				}
			break;
			case 3:
				printf("Chave para remover: ");
				scanf("%d", &chave);
				removerNodo(&arvore, chave);
			break;
			case 4:
				imprimirArvore(arvore);
			break;
			case 5:
				printf("saindo...");
			break;
		}
	}
	
	return 0;
}

