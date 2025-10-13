#ifndef HISTORICO_H
#define HISTORICO_H

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
    Curso* cabeca; // lista com cabeçalho por curso
} Historico;

Historico* criaHistorico();
void insereAtendimento(Historico* h, char* curso, char* cpf, char* data, char* psicologo, char* resumo);
void consultaPorCPF(Historico* h, char* cpf);
void imprimeRelatorio(Historico* h);

#endif
