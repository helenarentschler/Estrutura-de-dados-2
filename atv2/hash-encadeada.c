#include <stdio.h>
#include <stdlib.h>

#include "hash-encadeada.h"

void inicializarTabelaE(Encad* tabela, int posicoes) {

	for(int i = 0; i < posicoes; i++ ) {
		(tabela + i)->chave = -1;
        (tabela + i)->proximo = NULL;
	}
}

void imprimirTabelaE(Encad* tabela, FILE* arquivo, int qntComparacoes, int posicoes) {

	fprintf(arquivo, "Quantidade de comparaçoes na busca: %d\n", qntComparacoes);
	
	for( int i = 0; i < posicoes; i++ ) {
        
        Encad* n = (tabela + i)->proximo;

		while(n){
            fprintf(arquivo, "posicao: %d - chave: %d\n", i, (n)->chave);
            n = n->proximo;
        }   
	}
}

void inserirElementoE(int chave, Encad* tabela, int posicoes) {
	
	int end = chave % posicoes;
	
    Encad* auxiliar = (Encad*) malloc(sizeof(Encad));

    if(auxiliar){
        auxiliar->chave = chave;
        auxiliar->proximo = (tabela + end)->proximo;
        (tabela+end)->proximo = auxiliar;
    }
}

int buscarElementoE(int chave, Encad* tabela, int* qntComparacoes, int posicoes) {
	
	int end = chave % posicoes;
    Encad* aux = (tabela + end);
	
	while (aux->proximo) {

		(*qntComparacoes)++;
		
        if(aux->chave == chave){
            return 0;
        }
        aux = aux->proximo;
	}
	return -1;	
}