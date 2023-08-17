#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"


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

