#ifndef FILA_H
#define FILA_H

/*
 * Módulo: fila
 * Descrição: implementação de uma fila de espera simples para estudantes.
 * Estruturas:
 *  - Estudante: contém nome, cpf e curso (strings com tamanhos fixos).
 *  - NoFila: nó da fila que contém um Estudante e ponteiro para o próximo.
 *  - Fila: mantém ponteiros para inicio e fim.
 *
 * Contratos (resumidos):
 *  - criaFila(): retorna ponteiro para Fila inicializada ou NULL em erro (malloc).
 *  - insereFila(f, e): insere no fim; retorna 1 se sucesso, 0 se falha (malloc).
 *  - removeFila(f, e): remove do início; retorna 1 e copia o Estudante em *e, ou 0 se vazia.
 *  - cancelaFila(f, cpf): procura por CPF em qualquer posição e remove; retorna 1 se removido.
 *  - imprimeFila(f): imprime cada estudante; aceita ponteiro constante.
 *  - liberaFila(f): libera toda a memória usada pela fila.
 *
 * Observações:
 *  - As funções trabalham com cópia de Estudante (tipo por valor).
 *  - Todas as funções assumem que parâmetros não nulos são usados corretamente pelo chamador.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char cpf[15];
    char curso[50];
} Estudante;

typedef struct NoFila {
    Estudante dado;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim;
} Fila;

/* API pública */
Fila* criaFila(void);
int insereFila(Fila* f, Estudante e);
int removeFila(Fila* f, Estudante* e);
int cancelaFila(Fila* f, const char* cpf);
void imprimeFila(const Fila* f);
void liberaFila(Fila* f);

#endif
