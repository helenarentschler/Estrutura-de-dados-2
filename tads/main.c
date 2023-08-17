#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"

int main() {

	DynamicArray alunos;
	alunos.alunos = (Aluno*) malloc(sizeof(Aluno));
	alunos.i = 0;
	alunos.capacidade = 10;

	int ra;
	float nota;

	while(ra) {
	
		printf("Insira RA do aluno: ");
		scanf("%d", &ra);
		printf("Insira nota do aluno: ");
		scanf("%f", &nota);

		inserirAluno(ra, nota, &alunos);
	}

	exibirAlunos(alunos);

	buscarAluno(alunos, 4);
	
	return 0;
}
