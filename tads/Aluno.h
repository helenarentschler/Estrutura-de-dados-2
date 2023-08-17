#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED

typedef struct {
	int ra;
	float nota;
} Aluno;

Aluno* criarAluno();
void destruirAluno(Aluno* aluno);
void definirRa(Aluno* aluno, int ra);
void definirNota(Aluno* aluno, float nota);
void exibirRa(Aluno* aluno);
void exibirNota(Aluno* aluno);

#endif
