#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Módulo: historico
 * Descrição: mantém um histórico de atendimentos agrupados por curso.
 * Estruturas:
 *  - Atendimento: dados de um atendimento (cpf, data, psicologo, resumo) e ponteiro para próximo.
 *  - Curso: nó que contém o nome do curso e a lista encadeada de Atendimentos.
 *  - Historico: cabeça da lista de cursos.
 *
 * Contratos:
 *  - criaHistorico(): aloca e inicializa o historico.
 *  - insereAtendimento(h, curso, cpf, ...): insere um atendimento no final da lista do curso
 *      (cria o curso se necessário).
 *  - consultaPorCPF(h, cpf): percorre todos os cursos e imprime atendimentos do CPF.
 *  - imprimeRelatorio(h): imprime todos os atendimentos agrupados por curso.
 *  - liberaHistorico(h): libera toda a memória associada.
 *
 * Observações:
 *  - Strings têm tamanhos fixos; ao inserir, use strncpy para evitar overflow.
 *  - Esta implementação armazena cópias das strings nos nós; não há compartilhamento de ponteiros.
 */

typedef struct Atendimento {
    char cpf[15];
    char data[11];
    char psicologo[50];
    char resumo[200];
    struct Atendimento* prox;
} Atendimento;

typedef struct Curso {
    char nome[30];
    Atendimento* lista;
    struct Curso* prox;
} Curso;

typedef struct {
    Curso* cabeca;
} Historico;

/* API pública */
Historico* criaHistorico(void);
void insereAtendimento(Historico* h, const char* curso, const char* cpf, const char* data, const char* psicologo, const char* resumo);
void consultaPorCPF(const Historico* h, const char* cpf);
void imprimeRelatorio(const Historico* h);
void liberaHistorico(Historico* h);

#endif
