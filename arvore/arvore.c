// AP1 - Helena Rentschler - RA: 2539527

#include <stdio.h>
#include <stdlib.h>

// definiçao do tipo nodo
typedef struct No {

	int chave;
	struct No* esquerda;
	struct No* direita;
	struct No* pai;

} Nodo;

Nodo* criarNodo(int chave);
Nodo* inserirNodo(Nodo* no, int chave);
void imprimirArvoreArquivo(FILE* arquivo, Nodo* no);
Nodo* buscarNodo(Nodo* no, int chave);
int removerNodoCaso1e2(Nodo** raiz, Nodo* no);
void removerNodo(Nodo** raiz, int chave);

int main() {

	FILE* entrada = fopen("in.txt", "r");

	int chave = 0;

	char op;

	Nodo* raiz = NULL;

	//lendo arquivo de entrada
	while(fscanf(entrada, "%c %d\n", &op, &chave) != EOF) {

		if(op == 'i') {

			raiz = inserirNodo(raiz, chave);
			
		} else if(op == 'r'){

			removerNodo(&raiz, chave);
		}
	}

	FILE* saida = fopen("out.txt", "w");

	//escrevendo no arquivo de saida
	imprimirArvoreArquivo(saida, raiz);
	
	return 0;
}

//funçao: cria um nodo nodo na memoria
//param: chave
Nodo* criarNodo(int chave){

	Nodo* novo = (Nodo*) malloc(sizeof(Nodo));

	if(novo) {
		novo->chave = chave;
		novo->esquerda = NULL;
		novo->direita = NULL;
		novo->pai = NULL;
	}

	return novo;
}

//funçao: inserçao do nodo correspodnente a chave enviada na arvore
//param: endereço da raiz e chave para inserir
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

//funçao: impressao em ordem no arquivo de saida
// param: ponteiro para arquivo de saida e endereço da raiz da arvore
void imprimirArvoreArquivo(FILE* arquivo, Nodo* no){

	if(!no) {
		return;	
	}

	imprimirArvoreArquivo(arquivo, no->esquerda);
	fprintf(arquivo,"%d\n", no->chave);
	imprimirArvoreArquivo(arquivo, no->direita);
}

// funçao: busca binaria de um nodo por chave
// param: endereço da raiz da arvore, chave para busca
Nodo* buscarNodo(Nodo* no, int chave) {

	//se o nodo for nulo, retorna nulo
	if(!no) {
		return NULL;
	}

	//se encontrou o nodo correspondente a chave, retorna o endereço dele
	if(no->chave == chave) {
		return no;
	}

	//se a chave de pesquisa for maior que a chave do nodo
	if(chave > no->chave){
		//buscar a raiz a partir do nodo da direita 
		buscarNodo(no->direita, chave);
		
	} else {
		// caso contrario, buscar a raiz a partir do nodo da esquerda
		buscarNodo(no->esquerda, chave);
	}
}

//funçao: tenta remover um nodo caso 1 e 2. Se conseguir, retorna 1
// param: ponteiro para o ponteiro arvore da main, nodo a ser removido
int removerNodoCaso1e2(Nodo** raiz, Nodo* no) {

	//verifica se nao é o nodo raiz
	if(no->pai) {

		char filho;	
		//verificando se o nodo a ser excluido é o filho da esquerda ou da direita, guardando numa flag filho
		filho = no->pai->esquerda == no ? 'e' : 'd';

		//caso 1: nodo folha, sem filhos
		if(!no->direita && !no->esquerda) {
	
			//anula o filho da direita ou esquerda 
			(filho == 'e') ? (no->pai->esquerda = NULL) : (no->pai->direita = NULL);

			//remove nodo
			free(no);
			
			return 1;
	
		//caso 2: nodo tem filho a esquerda
		} else if(!no->direita) {

			//campo pai do filho da esquerda recebe o nodo "avo"
			no->esquerda->pai = no->pai;
			//no->pai recebe o "neto" a esquerda ou direita (com base na flag)
			(filho == 'e') ? (no->pai->esquerda = no->esquerda) : (no->pai->direita = no->esquerda);

			//remove nodo
			free(no);
			
			return 1;
			
		//caso 2: nodo tem filho a direita
		} else if(!no->esquerda) {
		
			//campo pai do filho da direita recebe o nodo "avo"	
			no->direita->pai = no->pai;

			//no->pai recebe o "neto" a esquerda ou direita (com base na flag)
			(filho == 'e') ? (no->pai->esquerda = no->direita) : (no->pai->direita = no->direita);

			//remove nodo
			free(no);
			
			return 1;
			
		}  else {
		
			return 0;	
		}

	// se o nodo for raiz
	} else {
		//caso 1: nodo folha, sem filhos
		if(!no->direita && !no->esquerda) {
			//anula o ponteiro da main
			*raiz = NULL;
			free(no);
			
			return 1;
	
		//caso 2: nodo tem filho a esquerda
		} else if(!no->direita) {
			//ponteiro para arvore da main recebe o filho a esquerda
			*raiz = no->esquerda;
			//nova raiz tem pai nulo
			no->esquerda->pai = NULL;  
			free(no);
			
			return 1;
			
		//caso 2: nodo tem filho a direita
		} else if(!no->esquerda) {

			//ponteiro para arvore da main recebe filho a direita
			*raiz = no->direita;
			//nova raiz tem pai nulo
			no->direita->pai = NULL;  
			free(no);
			
			return 1;
			
		}  else {
		
			return 0;	
		}
	}
}

// param: raiz da arvore, chave para busca
void removerNodo(Nodo** raiz, int chave) {

	//ponteiro para o retonro da busca
	Nodo* encontrado;
	
	do {
		//busca chave na arvore
		encontrado = buscarNodo(*raiz, chave);

		//caso retorne um nodo encontrado
		if(encontrado) {

			//tenta remover para o caso 1 e 2
			if(!removerNodoCaso1e2(raiz, encontrado)) {

				//caso 3: comeca a busca pelo sucessor pelo filho da direita
				Nodo* sucessor = encontrado->direita;

				//enquanto tiver filhos a esquerda
				while(sucessor->esquerda) {

					sucessor = sucessor->esquerda;
				}

				//troca a chave do nodo encontrado pela chave do sucessor
				encontrado->chave = sucessor->chave;

				//remove nodo sucessor da arvore
				removerNodoCaso1e2(raiz, sucessor);
			}	
		} 
		
	} while(encontrado); // repete a busca enquanto houver instancias da chave na arvore 
}


