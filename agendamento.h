#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include "lista.h"

#define MAX_SALA 10
#define MAX_DATA 11
#define MAX_HORA 6
#define MAX_CPF 15  // Adicionado aqui também

typedef struct {
    char cpf[MAX_CPF];
    char sala[MAX_SALA];
    char data[MAX_DATA];
    char hora[MAX_HORA];
    char status[20];
} Agendamento;

typedef struct {
    char cpf[MAX_CPF];
    char data[MAX_DATA];
} ChaveCPFData;

// Funções agendamento
void exibirAgendamento(void* dado);
void exibirAgendamentoDetalhado(void* dado);
void exibirAgendamentoHistorico(void* dado);
int compararAgendamentoCPF(void* elemento, void* chave);
int compararAgendamentoSala(void* elemento, void* chave);
int compararAgendamentoCPFData(void* elemento, void* chave);
void liberarAgendamento(void* dado);

// API completa
int cadastrarAgendamento(Lista* lista, Agendamento a);
int cancelarAgendamento(Lista* lista, const char* cpf, const char* data);
Lista* buscarAgendamentosCPF(Lista* lista, const char* cpf);
Lista* buscarAgendamentosSala(Lista* lista, const char* sala);
void exibirHorariosDisponiveis(Lista* lista, const char* data, const char* sala);
void exibirHistoricoCompleto(Lista* lista);

#endif