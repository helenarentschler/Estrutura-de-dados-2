#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int pos = 4000;

void inserirNumeros(int* vet) {

	srand(time(NULL));

	int num = 0, flag = 0;

	for(int i = 0; i < pos; i++) {

		do{
			flag = 0;
			
			num = rand() % 5000;

			for(int j = 0; j < i; j++) {

				if(*(vet + j) == num) {

					flag = 1;
				}
			}
			
		} while (flag);

		*(vet + i) = num;
	}			
}

void bubbleSort(int* vet) {

	int maior;
	
	for(int j = 0; j < pos; j++) {

		for(int i = 0; i < pos; i++) {
		
			if(*(vet + i) > *(vet + i + 1)) {

				maior = *(vet + i);
				*(vet + i) = *(vet + i + 1);
				*(vet + i + 1) = maior;
			}
		}
	}			
}

int buscaBinaria(int* vet, int n){

	int med, a = 0, b = pos - 1;
	clock_t ticks[2];
	ticks[0] = clock();
	
	while(a <= b) {

		med = floor((a + b) / 2);

		if(n == *(vet + med)) {
		
			ticks[1] = clock();

			double tempo = (double)(ticks[1] - ticks[0]) / CLOCKS_PER_SEC * 1000.0;
			printf("Tempo busca binaria: %.2f ms", tempo);
			
			return med;
			
		} else if(n > *(vet + med)) {

			a = med + 1;
			
		} else {

			b = med - 1;
		}
	}

	ticks[1] = clock();
	
	double tempo = (double)(ticks[1] - ticks[0]) * 1000 / CLOCKS_PER_SEC * 1000.0;

	printf("Tempo busca binaria: %.2f ms", tempo);

	return -1;
}

int buscaLinear(int* vet, int n) {

	clock_t ticks[2];
	ticks[0] = clock();
	
	for(int i = 0; i < pos; i++) {
		
		if(*(vet+i) == n) {
		
			ticks[1] = clock();

			double tempo = (double)(ticks[1] - ticks[0]) * 1000 / CLOCKS_PER_SEC * 1000;

			printf("Tempo busca linear: %.2f ms", tempo);
			
			return i;
		}
	}
	
	ticks[1] = clock();

	double tempo = (double)(ticks[1] - ticks[0]) * 1000 / CLOCKS_PER_SEC * 1000;

	printf("Tempo busca linear: %.2f ms", tempo);

	return -1;
}

int buscaBinariaRecursiva(int a, int b, int* vetor, int valor) {

	if(b < a) {
		return -1;
	}

	if(a == b) {
		return	a;
	}

	int m = (a + b) / 2;
	
	if(vetor[m] > valor) {
	    return buscaBinariaRecursiva(a, m-1, vetor, valor);	
	} else {
	    return buscaBinariaRecursiva(m+1, b, vetor, valor);	
	}
}

int main(){

	int vet[pos], num;

	inserirNumeros(vet);

	bubbleSort(vet);

	for(int i = 0; i < pos; i++) {
	
		printf("%d\n", *(vet + i));
	}

	printf("Insira numero a ser buscado: ");
	scanf("%d", &num);
	
	int resBin = buscaBinaria(vet, num);

	if(resBin != -1) {

		printf("Binaria - Encontrado na posiçao %d\n", resBin);
		
	} else {

		printf("Nao econtrado");
	}

	int resLin = buscaLinear(vet, num);

	if(resLin != -1) {
	
		printf("Linear - Encontrado na posiçao %d\n", resLin);
		
	} else {

		printf("Nao econtrado");
	}

	int resBinRec = buscaBinariaRecursiva(0, pos, vet, num);

	if(resBinRec != -1) {
	
		printf("Binaria recursiva - Encontrado na posiçao %d\n", resBinRec);
		
	} else {

		printf("Nao econtrado");
	}
	
	return 0;
}
