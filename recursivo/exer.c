#include <stdio.h>

int somar(int a, int b) {

	if(a == b) {
		return b;
	}

	//coloco return ou nao? (tanto faz pois a execuçao da funçao é a ultima coisa?)
	return a + somar(a + 1, b);
}

int fatorial(int n) {

	if(n == 1) {
		return 1;
	}

	return n * fatorial(n-1);
}

int exponencial(int b, int e) {

	if(e == 1){
		return b;
	}

	return b * exponencial(b, e - 1);
}

int busca(int* vet, int n, int i) {
	
	if(vet[i] == n) {
		return i;
	} else if (i == 0) {
		return -1;
	}
	
	return busca(vet, n, i - 1);
}

void inverterVetor(int* vet, int a, int b) {

	if(a == b) {
		return;
	}

	int aux = vet[a];
	vet[a] = vet[b];
	vet[b] = aux;
	
	return inverterVetor(vet, a+1, b-1);
}

int ePalindromo(char* vet, int a, int b) {

	if(vet[a] != vet[b]) {
		return 0;
	} else if(a == b) {
		return 1;
	}
	return ePalindromo(vet, a+1, b-1);
}

int main() {

	int vet[10] = {1,9,50,3,12}; 
	char palavra[30];
	
	printf("A soma é: %d\n", somar(3, 5));
	printf("Fatorial é: %d", fatorial(4));
	printf("Exponencial é: %d", exponencial(4, 3));
	printf("Resultado da busca %d", busca(vet, 12, 9));
	inverterVetor(vet, 0, 4);
	
	for(int i = 0; i < 5; i++) {
		printf("%d\n",vet[i]);	
	}

	printf("Escreva uma palavra: ");
	scanf("%s", palavra);

	if(ePalindromo(palavra, 0, 2)) {
		printf("é palindromo");
	} else {
		printf("nao é palindromo");
	}
	
	return 0;
}
