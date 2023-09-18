#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"

Aluno* criarAluno(int ra, float nota) {

	Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));

	if(aluno) {

		aluno->ra = ra;
		aluno->nota = nota;		

	} else {
	
		printf("Nao foi possivel alocar memoria\n");
	}

	return aluno;
}

void definirRa(Aluno* aluno, int ra) {

	aluno->ra = ra;
}

void definirNota(Aluno* aluno, float nota) {

	aluno->nota = nota;
}

void exibirRa(Aluno* aluno) {

	printf("RA do aluno: %d\n", aluno->ra);
}

void exibirNota(Aluno* aluno) {

	printf("Nota do aluno: %f\n", aluno->nota);
}

void destruirAluno(Aluno* aluno){

	free(aluno);
}
