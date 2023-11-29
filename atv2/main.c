#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash.h"
#include "avl.h"
#include "hash-encadeada.h"

int executarAvl(FILE* entrada);
int executarHash(FILE* entrada);
int executarHashEncadeada(FILE* entrada);

int main() {

	//lendo arquivo de entrada
	FILE* entrada = fopen("in1.txt", "r");

	int comparacoesHash = executarHash(entrada);
	int comparacoesHashEncadeada = executarHashEncadeada(entrada);
	int comparacoesAvl = executarAvl(entrada);

	printf("comparaçoes hash: %d\n", comparacoesHash );
	printf("comparaçoes hashEncadeada: %d\n", comparacoesHashEncadeada);
	printf("comparaçoes avl: %d\n", comparacoesAvl);

	return 0;
}


int executarHash(FILE* entrada) {
	
	int qntComparacoes = 0;
	int posicoes = 100;
	int qnt = 0;
	float tempoFinal = 0;		
	
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

			clock_t tempoHash = clock();

			buscarElemento(chave, tabela, posicoes, &qntComparacoes);

			float tempo = ((double) (clock() - tempoHash)) / CLOCKS_PER_SEC;

			tempoFinal += tempo;
		}
	}

	printf("tempo das buscas na Hash: %f\n", tempoFinal);

	//abrindo arquivo hash.txt de saida
	FILE* saida = fopen("hash.txt", "w");

	//imprimindo tabela Hash no arquivo de saida
	imprimirTabela(tabela, posicoes, saida, qntComparacoes);
	
	return qntComparacoes;
};


int executarHashEncadeada(FILE* entrada) {

	rewind(entrada);
	
	int qntComparacoes = 0;
	int posicoes = 100;
	float tempoFinal = 0;

	//tabela hash
	Encad* tabela = (Encad*) malloc(sizeof(Encad) * posicoes);	
	
	inicializarTabelaE(tabela, posicoes);

	//chaves lidas do arquivo
	int chave = 0;

	//opçao de operaçao: i - inserir e b - buscar
	char op;

	while(fscanf(entrada, "%c %d\n", &op, &chave) != EOF) {

		if(op == 'i') {

			inserirElementoE(chave, tabela, posicoes);
			
		} else if(op == 'b'){
			
			clock_t tempoHashEncadeada = clock();

			buscarElementoE(chave, tabela, &qntComparacoes, posicoes);

			float tempo = ((double) (clock() - tempoHashEncadeada))/CLOCKS_PER_SEC;

			tempoFinal += tempo;
		}
	}

	printf("tempo das buscas na Hash encadeada: %f\n", tempoFinal);

	//abrindo arquivo hash.txt de saida
	FILE* saida = fopen("hashEncadeada.txt", "w");

	//imprimindo tabela Hash no arquivo de saida
	imprimirTabelaE(tabela, saida, qntComparacoes,posicoes);
	
	return qntComparacoes;
};


int executarAvl(FILE* entrada) {

	rewind(entrada);
	
	int qntComparacoes = 0;
	float tempoFinal = 0;

	//avl
	Nodo* raiz = NULL;

	//chaves lidas do arquivo
	int chave = 0;

	//opçao de operaçao: i - inserir e b - buscar
	char op;

	while(fscanf(entrada, "%c %d\n", &op, &chave) != EOF) {

		if(op == 'i') {

			raiz = inserirNodo(raiz, chave);
			recalcularAlturas(raiz);
			verificarDesbalanceamentos(raiz, &raiz);

		} else if(op == 'b') {

			clock_t tempoArvore = clock();

			buscarNodo(raiz, chave, &qntComparacoes);

			float tempo = ((double) (clock() - tempoArvore))/CLOCKS_PER_SEC;

			tempoFinal += tempo;
		}
	}

	printf("tempo das buscas na AVL: %f\n", tempoFinal);

	//abrindo arquivo avl.txt de saida
	FILE* saida = fopen("avl.txt", "w");

	//imprimindo avl em ordem no arquivo de saida
	imprimirArvore(raiz, saida);
	
	return qntComparacoes;
};

