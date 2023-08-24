#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	srand(time(NULL));

	int vet[5000];
	int num = 0, flag = 0;

	for(int i = 0; i < 5000; i++) {

		num = rand() % 5000;

		for(int j = 0; j < i; j++) {

			if(vet[j] == num) {
				 flag = 1;
				 break;
			}
		}

		if(!flag) {

			vet[i] = num;
		}
	}
	
	return 0;
}
