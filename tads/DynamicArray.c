#include <stdio.h>
#include <stdlib.h>

#include "DynamicArray.h"

void inserirAluno(int ra, float nota, DynamicArray* vetor) {
	
	if(vetor->i < vetor->capacidade) {
	
		(vetor->i)++;
		definirRa((vetor->alunos + vetor->i), ra);
		definirNota((vetor->alunos + vetor->i), nota);
		
	} else {
	
		Aluno* novoVetor = (Aluno*) realloc(vetor->alunos, (vetor->capacidade)*2*sizeof(Aluno));

		if(novoVetor) {
			vetor->alunos = novoVetor;
			vetor->capacidade = (vetor->capacidade)*2;
			inserirAluno(ra, nota, vetor);
			
		} else {
			printf("Sem espaço em memoria\n");
		}
	}
}

void exibirAlunos(DynamicArray vetor) {

	printf("Alunos\n");

	for(int cont = 0; cont < vetor.i; cont++) {

		printf("\n----------\n");
		exibirRa((vetor.alunos + cont));
		exibirNota((vetor.alunos + cont));
	}
}

void buscarAluno(DynamicArray vetor, int ra) {

	for(int cont = 0; cont < vetor.i; cont++) {

		if((vetor.alunos + cont)->ra == ra) {

			printf("Aluno: Ra - %d Nota: %f", ra, (vetor.alunos + cont)->nota);
			return;
		}
	}

	printf("Aluno nao encontrado\n");
}
