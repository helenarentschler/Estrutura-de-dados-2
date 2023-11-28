#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento {

	int chave;
	struct Elemento* prox;
	
} Elemento;

int main() {

	int qntComparacoes = 0;
	int posicoes = 5;
	
	Elemento* tabelaListas = (Elemento*) malloc(sizeof(Elemento*) * posicoes);


	return 0;
}

void imprimirTabelaListas(Elemento* tabela, int posicoes, FILE* arquivo) {

	
	for( int i = 0; i < posicoes; i++ ) {

		//aponta para o primeiro registro Elemento
		Elemento* aux = tabela + i;

		fprintf(arquivo, "\nEndereço: %d\n", i);
		
		while(aux) {
		
			fprintf(arquivo, "chave: %d\n", aux->chave);
			aux = aux->prox;
		}
		
	}
}

void inicializarTabela(Elemento* tabela, int posicoes) {

	Elemento aux;
	aux.prox = NULL;
	
	for( int i = 0; i < posicoes; i++ ) {

		*(tabela + i) = aux;		
	}
}

void inserirElemento(int chave, Elemento* tabela, int posicoes, int* qnt) {
	
	int end = chave % posicoes;	

	Elemento* aux = tabela + end;

	Elemento* novo = malloc(sizeof(Elemento));
	novo->chave = chave;
	novo->prox = NULL;

	if(!aux->prox) {
		
	}

	while(aux->prox) {
		aux = aux->prox;
	}	
	
	aux->prox = novo;

	(*qnt)++;
}

