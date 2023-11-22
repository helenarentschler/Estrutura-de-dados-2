#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

Hash* calcularCarga(Hash* tabela, int* qnt, int* posicoes) {

	double div = (double) (*qnt) / (double) (*posicoes);

	if( div >= 0.7 ) {
		
		Hash* novaTabela = (Hash *) malloc(sizeof(Hash) * (*posicoes) * 2);
	
		if(novaTabela) {
		
			int qntPosicoesAntiga = *posicoes;
			
			(*posicoes) *= 2;
			*qnt = 0;

			inicializarTabela(novaTabela, *posicoes);
			
			for( int i = 0; i < qntPosicoesAntiga; i++ ) {
				
				if((tabela + i)->status != 'L') {
				
					inserirElemento((tabela + i)->chave, novaTabela, *posicoes, qnt);
				}
			}

			free(tabela);
	
			return novaTabela;
			
		} else {
		
			printf("Sem espaço em memoria\n");

			return NULL;
		}
				
	}

	return tabela;
}

//incializa tabela com status L para todas as posiçoes
void inicializarTabela(Hash* tabela, int posicoes) {

	for( int i = 0; i < posicoes; i++ ) {
		(tabela + i)->status = 'L';
	}
}

void imprimirTabela(Hash* tabela, int posicoes, FILE* arquivo, int qntComparacoes) {

	fprintf(arquivo, "Quantidade de comparaçoes na busca: %d\n", qntComparacoes);
	
	for( int i = 0; i < posicoes; i++ ) {
		fprintf(arquivo, "chave: %d, status: %c\n", (tabela + i)->chave, (tabela + i)->status);
	}
}

int inserirElemento(int chave, Hash* tabela, int posicoes, int* qnt) {
	
	int i = 0;
	int endInicial = chave % posicoes;
	int end = endInicial;
	
	while ( (tabela + end)->status == 'O' && i < posicoes ) {
		
		i++;	
		end = (endInicial + i) % posicoes;
	}

	if( (tabela + end)->status != 'O' ) {

		(tabela + end)->chave = chave;
		(tabela + end)->status = 'O';	
		(*qnt)++;
		
		return end;	
	}

	return -1;
}

int buscarElemento(int chave, Hash* tabela, int posicoes, int* qntComparacoes) {
	
	int i = 0;
	int endInicial = chave % posicoes;
	int end = endInicial;
	
	while (i < posicoes) {

		(*qntComparacoes)++;
		
		if((tabela + end)->status == 'L') {
			return -1;
		}
		
		if((tabela + end)->chave == chave) {
			return end;
		}
		
		i++;	
		
		end = (endInicial + i) % posicoes;
	}

	return -1;	
}
