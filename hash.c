#include <stdio.h>
#include <stdlib.h>

typedef struct Hash {
	int chave;
	char status;
} Hash;

int inserirElemento(int chave, Hash* tabela, int posicoes, int* qnt);
void imprimirTabela(Hash* tabela, int posicoes);
void inicializarTabela(Hash* tabela, int posicoes);
int buscarElemento(int chave, Hash* tabela, int posicoes);
Hash* calcularCarga(Hash* tabela, int* qnt, int* posicoes);

int main(){

	int posicoes = 8;
	int qnt = 0;
	//tabela hash de 100 posiçoes
	Hash* tabela = (Hash*) malloc(sizeof(Hash) * posicoes);	

	inicializarTabela(tabela, posicoes);
	
	inserirElemento( 16, tabela, posicoes, &qnt);
	tabela = calcularCarga(tabela, &qnt, &posicoes);
	inserirElemento( 23, tabela, posicoes, &qnt);
	tabela = calcularCarga(tabela, &qnt, &posicoes);
	inserirElemento( 41, tabela, posicoes, &qnt);
	tabela = calcularCarga(tabela, &qnt, &posicoes);
	inserirElemento( 25, tabela, posicoes, &qnt);
	tabela = calcularCarga(tabela, &qnt, &posicoes);
	inserirElemento( 39, tabela, posicoes, &qnt);
	tabela = calcularCarga(tabela, &qnt, &posicoes);
	inserirElemento( 90, tabela, posicoes, &qnt);
	tabela = calcularCarga(tabela, &qnt, &posicoes);

	imprimirTabela(tabela, posicoes);

	printf("qnt: %d\n", qnt);
	printf("%d\n", buscarElemento(39, tabela, posicoes));
	printf("%d", buscarElemento(60, tabela, posicoes));
	
	return 0;
}

Hash* calcularCarga(Hash* tabela, int* qnt, int* posicoes) {

	double div = (double) (*qnt) / (double) (*posicoes);
	printf("%f", div);
	if( div >= 0.7 ) {
		
		Hash* novaTabela = (Hash *) malloc(sizeof(Hash) * (*posicoes) * 2);
	
		if(novaTabela) {
		
			int posicoesAntiga = *posicoes;
			
			(*posicoes) *= 2;
			*qnt = 0;

			inicializarTabela(novaTabela, *posicoes);
			
			for( int i = 0; i < posicoesAntiga; i++ ) {
				
				if((tabela + i)->status != 'L') {
				
					inserirElemento((tabela + i)->chave, novaTabela, *posicoes, qnt);
				}
			}

			free(tabela);
	
			return  novaTabela;
			
		} else {
		
			printf("Sem espaço em memoria\n");

			return NULL;
		}
				
	}

	return tabela;
}

void inicializarTabela(Hash* tabela, int posicoes) {

	for( int i = 0; i < posicoes; i++ ) {
		(tabela + i)->status = 'L';
	}
}

void imprimirTabela(Hash* tabela, int posicoes) {

	for( int i = 0; i < posicoes; i++ ) {
		printf("chave: %d, status: %c\n", (tabela + i)->chave, (tabela + i)->status);
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

int buscarElemento(int chave, Hash* tabela, int posicoes) {
	
	int i = 0;
	int endInicial = chave % posicoes;
	int end = endInicial;
	
	while (i < posicoes) {

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
