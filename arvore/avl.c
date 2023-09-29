#include <stdio.h>
#include <stdlib.h>

typedef struct No {

	int chave;
	int fatorB;
	struct No* esquerda;
	struct No* direita;
	struct No* pai;
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

//enviando o no cujo nivel seja retornado 
int calcularNivel(Nodo* no) {

	if(!no) {
		return -1;
	}

	return 1 + calcularNivel(no->pai);
}

int calcularFatorB(Nodo* raiz) {

	if(!raiz) {
		return -1;
	}

	int soma_esq = 1 + calcularFatorB(raiz->esquerda);
	int soma_dir = 1 + calcularFatorB(raiz->direita);

	raiz->fatorB = soma_dir - soma_esq;

	return soma_esq > soma_dir ?  soma_esq :  soma_dir;
}

//param: raiz da arvore e chave para inserir
Nodo* inserirNodo(Nodo* no, int chave) {

	//ARRUMAR
	if (no == NULL){
        return criarNodo(chave);
    }

	//se a chave enviada for maior que a raiz(subraiz)
	if(chave > no->chave){

		//checar se existe no à direita, se nao existir insere a chave
		if(!no->direita) {

			Nodo* novo = criarNodo(chave);
			no->direita = novo;
			novo->pai = no; 
			return novo;
		}

		//se existir, enviar o no a direita para comparaçao
		inserirNodo(no->direita, chave);

	} else {

		if(!no->esquerda) {
		
			Nodo* novo = criarNodo(chave);
			no->esquerda = novo;
			novo->pai = no; 
			return novo;
		}

		inserirNodo(no->esquerda, chave);	
	}
}

Nodo* inserirNodo2(Nodo* raiz, int chave) {

	if(!raiz) {

		return criarNodo(chave);
	}

	if(chave > raiz->chave) {

		raiz->direita = inserirNodo2(raiz->direita, chave);

	} else {

		raiz->esquerda = inserirNodo2(raiz->esquerda, chave);	
	}

	return raiz;
	
}

void imprimirArvore(Nodo* no){

	if(!no) {
		return;	
	}

	imprimirArvore(no->esquerda);
	printf("Chave: %d ---", no->chave);
	printf("Fator Balanceamento: %d \n", no->fatorB);
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

// param: nodo a ser removido
int removerNodoCaso1e2(Nodo** raiz, Nodo* no) {

	//verifica se nao é o nodo raiz
	if(no->pai) {

		char filho;	
		//verificando se o no a ser excluido é o filho da esquerda ou da direita:
		filho = no->pai->esquerda == no ? 'e' : 'd';

		//caso 1: nodo folha, sem filhos
		if(!no->direita && !no->esquerda) {
	
			//anula o filho da direita ou esquerda do pai
			(filho == 'e') ? (no->pai->esquerda = NULL) : (no->pai->direita = NULL);
		
			free(no);
			
			return 1;
	
		//caso 2: no tem filho a esquerda
		} else if(!no->direita) {

			//atualiza o pai
			no->esquerda->pai = no->pai;
			//atualiza o filho da direita ou esquerda
			(filho == 'e') ? (no->pai->esquerda = no->esquerda) : (no->pai->direita = no->esquerda);
		
			free(no);
			
			return 1;
			
		//caso 2: no tem filho a direita
		} else if(!no->esquerda) {
		
			no->direita->pai = no->pai;
			(filho == 'e') ? (no->pai->esquerda = no->direita) : (no->pai->direita = no->direita);
	
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
			//ponteiro para arvore da main receb o filho a esquerda
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

	//busca chave na arvore
	Nodo* encontrado = buscarNodo(*raiz, chave);

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
		
	} else {
		printf("Nodo %d nao encontrado.\n", chave);
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

