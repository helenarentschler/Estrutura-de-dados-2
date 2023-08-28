#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void inserirNumeros(int* vet) {

	srand(time(NULL));

	int num = 0, flag = 0;

	for(int i = 0; i < 1000; i++) {

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
	
	for(int j = 0; j < 1000; j++) {

		for(int i = 0; i < 1000; i++) {
		
			if(*(vet + i) > *(vet + i + 1)) {

				maior = *(vet + i);
				*(vet + i) = *(vet + i + 1);
				*(vet + i + 1) = maior;
			}
		}
	}			
}

int buscaBinaria(int* vet, int n){

	int med, a = 0, b = 999;
	
	while(a <= b) {

		med = floor((a + b) / 2);

		if(n == *(vet + med)) {

			return med;
			
		} else if(n > *(vet + med)) {

			a = med + 1;
			
		} else {

			b = med - 1;
		}
	}

	return -1;
}

int main(){

	int vet[1000], num;

	inserirNumeros(vet);

	bubbleSort(vet);

	for(int i = 0; i < 1000; i++) {
	
		printf("%d\n", *(vet + i));
	}

	scanf("%d", &num);
	
	int res = buscaBinaria(vet, num);

	if(res != -1) {

		printf("Encontrado na posiçao %d\n", res);
		
	} else {

		printf("Nao econtrado");
	}
		
	return 0;
}
