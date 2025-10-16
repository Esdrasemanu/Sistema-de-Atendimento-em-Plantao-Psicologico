#include "paciente.h"
#include "validaCpf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exibirPaciente(void* dado) {
    Paciente* p = (Paciente*)dado;
    printf("Nome: %s | CPF: %s | Curso: %s", p->nome, p->cpf, p->curso);
}

int compararPacienteCPF(void* elemento, void* chave) {
    Paciente* p = (Paciente*)elemento;
    char* cpf = (char*)chave;
    return strcmp(p->cpf, cpf) == 0;
}

void liberarPaciente(void* dado) {
    free((Paciente*)dado);
}

int cadastrarPaciente(Lista* lista, Paciente p) {

    if (!validarCPF(p.cpf)) {
        printf("CPF invalido!\n");
        return 0;
    }

    if (buscarElemento(lista, (void*)p.cpf, compararPacienteCPF)) {
        printf("Erro: CPF ja cadastrado!\n");
        return 0;
    }
    
    Paciente* novo = (Paciente*)malloc(sizeof(Paciente));
    if (!novo) return 0;
    
    *novo = p;
    return inserirFinal(lista, novo);
}

Paciente* buscarPacienteCPF(Lista* lista, const char* cpf) {
    return (Paciente*)buscarElemento(lista, (void*)cpf, compararPacienteCPF);
}