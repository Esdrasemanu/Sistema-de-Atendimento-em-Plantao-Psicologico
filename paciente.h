#ifndef PACIENTE_H
#define PACIENTE_H

#include "lista.h"

#define MAX_NOME 50
#define MAX_CPF 15
#define MAX_MATRICULA 20
#define MAX_CURSO 50

typedef struct {
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char matricula[MAX_MATRICULA];
    char curso[MAX_CURSO];
} Paciente;

// Funções pacientes
void exibirPaciente(void* dado);
int compararPacienteCPF(void* elemento, void* chave);
void liberarPaciente(void* dado);
int cadastrarPaciente(Lista* lista, Paciente p);
Paciente* buscarPacienteCPF(Lista* lista, const char* cpf);

#endif