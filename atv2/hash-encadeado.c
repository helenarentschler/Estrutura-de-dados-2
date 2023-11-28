#include <stdio.h>
#include <stdlib.h>

#include "hash-encadeada.h"

void inicializarTabelaE(Encad* tabela) {

	for(int i = 0; i < 100; i++ ) {
		(tabela + i)->chave = 0;
        (tabela + i)->proximo = NULL;
	}
}

void imprimirTabelaE(Encad* tabela, FILE* arquivo, int qntComparacoes) {

	fprintf(arquivo, "Quantidade de comparaçoes na busca: %d\n", qntComparacoes);
	
	for( int i = 0; i < 100; i++ ) {
        
        Encad* n = (tabela + i)->proximo;

		while(n){
            fprintf(arquivo, "posicao: %d - chave: %d\n", i, (n)->chave);
            n = n->proximo;
        }   
	}
}

void inserirElementoE(int chave, Encad* tabela) {
	
	int end = chave % 100;
	
    Encad* auxiliar = (Encad*) malloc(sizeof(Encad));

    if(auxiliar){
        auxiliar->chave = chave;
        auxiliar->proximo = (tabela + end)->proximo;
        (tabela+end)->proximo = auxiliar;
    }
}

int buscarElementoE(int chave, Encad* tabela, int* qntComparacoes) {
	
	int end = chave % 100;
    Encad* aux = (tabela + end);
	
	while (aux->proximo) {

		(*qntComparacoes)++;
		
        if(aux->chave == chave){
            printf("Elemento encontrado.\n");
            return 0;
        }
        aux = aux->proximo;
	}
    printf("Elemento não encontrado.\n");
	return -1;	
}