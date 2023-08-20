#ifndef DYNAMICARRAY_H_INCLUDED
#define DYNAMICARRAY_H_INCLUDED

#include "Aluno.h"

typedef struct {
	Aluno** alunos;
	int capacidade;
	int i;
} DynamicArray;

void inserirAluno(int ra, float nota, DynamicArray* vetor);

void exibirAlunos(DynamicArray vetor);

void buscarAluno(DynamicArray vetor, int ra);

#endif
