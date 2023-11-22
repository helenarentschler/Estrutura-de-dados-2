#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "avl.h"

int executarAvl(FILE* entrada);
int executarHash(FILE* entrada);

int main() {

	//lendo arquivo de entrada
	FILE* entrada = fopen("in.txt", "r");

	int comparacoesHash = executarHash(entrada);
	int comparacoesAvl = executarAvl(entrada);

	printf("comparaçoes hash: %d\n", comparacoesHash);
	printf("comparaçoes avl: %d\n", comparacoesAvl);

	return 0;
}

int executarHash(FILE* entrada) {
	
	int qntComparacoes = 0;
	int posicoes = 8;
	int qnt = 0;
	
	//tabela hash
	Hash* tabela = (Hash*) malloc(sizeof(Hash) * posicoes);	
	
	inicializarTabela(tabela, posicoes);

	//chaves lidas do arquivo
	int chave = 0;

	//opçao de operaçao: i - inserir e b - buscar
	char op;

	while(fscanf(entrada, "%c %d\n", &op, &chave) != EOF) {

		if(op == 'i') {

			inserirElemento( chave, tabela, posicoes, &qnt );
			tabela = calcularCarga( tabela, &qnt, &posicoes);
			
		} else if(op == 'b'){

			buscarElemento(chave, tabela, posicoes, &qntComparacoes);
		}
	}

	//abrindo arquivo hash.txt de saida
	FILE* saida = fopen("hash.txt", "w");

	//imprimindo tabela Hash no arquivo de saida
	imprimirTabela(tabela, posicoes, saida, qntComparacoes);
	
	return qntComparacoes;
};


int executarAvl(FILE* entrada) {

	rewind(entrada);
	
	int qntComparacoes = 0;
	
	//avl
	Nodo* raiz = NULL;

	//chaves lidas do arquivo
	int chave = 0;

	//opçao de operaçao: i - inserir e b - buscar
	char op;

	while(fscanf(entrada, "%c %d\n", &op, &chave) != EOF) {

		if(op == 'i') {

			raiz = inserirNodo(raiz, chave);
			raiz = balancear(raiz);
			
		} else if(op == 'b') {

			buscarNodo(raiz, chave, &qntComparacoes);
		}
	}

	//abrindo arquivo avl.txt de saida
	FILE* saida = fopen("avl.txt", "w");

	//imprimindo avl em ordem no arquivo de saida
	imprimirArvore(raiz, saida);
	
	return qntComparacoes;
};