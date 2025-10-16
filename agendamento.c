#include "agendamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaCpf.h"
#include "validaDataHora.h"

void exibirAgendamento(void* dado) {
    Agendamento* a = (Agendamento*)dado;
    printf("CPF: %s | Sala: %s | Data: %s | Hora: %s", a->cpf, a->sala, a->data, a->hora);
}

void exibirAgendamentoDetalhado(void* dado) {
    Agendamento* a = (Agendamento*)dado;
    printf("CPF: %s | Sala: %s | Data: %s | Hora: %s | Status: %s", 
           a->cpf, a->sala, a->data, a->hora, a->status);
}

void exibirAgendamentoHistorico(void* dado) {
    Agendamento* a = (Agendamento*)dado;
    printf("  %-15s %-10s %-12s %-8s %-12s", a->cpf, a->sala, a->data, a->hora, a->status);
}

int compararAgendamentoCPF(void* elemento, void* chave) {
    Agendamento* a = (Agendamento*)elemento;
    char* cpf = (char*)chave;
    return strcmp(a->cpf, cpf) == 0;
}

int compararAgendamentoSala(void* elemento, void* chave) {
    Agendamento* a = (Agendamento*)elemento;
    char* sala = (char*)chave;
    return strcmp(a->sala, sala) == 0;
}

int compararAgendamentoCPFData(void* elemento, void* chave) {
    Agendamento* a = (Agendamento*)elemento;
    ChaveCPFData* busca = (ChaveCPFData*)chave;
    return (strcmp(a->cpf, busca->cpf) == 0) && (strcmp(a->data, busca->data) == 0);
}

void liberarAgendamento(void* dado) {
    free((Agendamento*)dado);
}

int cadastrarAgendamento(Lista* lista, Agendamento a) {

    if (!validarCPF(a.cpf)) {
        printf("CPF invalido\n");
        return 0;
    }
    if(validarData(a.data) == 0) {
        printf("Data invalida\n");
        return 0;
    }
    if (validarHora(a.hora) == 0) {
        printf("Hora invalida\n");
        return 0;
    }

    Agendamento* novo = (Agendamento*)malloc(sizeof(Agendamento));
    if (!novo) return 0;
    *novo = a;
    return inserirFinal(lista, novo);
}

int cancelarAgendamento(Lista* lista, const char* cpf, const char* data) {
    ChaveCPFData chave;
    strcpy(chave.cpf, cpf);
    strcpy(chave.data, data);
    
    Agendamento* ag = (Agendamento*)removerElemento(lista, &chave, compararAgendamentoCPFData);
    if (ag) {
        liberarAgendamento(ag);
        return 1;
    }
    return 0;
}

Lista* buscarAgendamentosCPF(Lista* lista, const char* cpf) {
    return buscarTodosElementos(lista, (void*)cpf, compararAgendamentoCPF);
}

Lista* buscarAgendamentosSala(Lista* lista, const char* sala) {
    return buscarTodosElementos(lista, (void*)sala, compararAgendamentoSala);
}

void exibirHorariosDisponiveis(Lista* lista, const char* data, const char* sala) {
    printf("\n--- HORARIOS DISPONIVEIS - %s - Sala %s ---\n", data, sala);
    printf("Horarios livres: 08:00, 09:00, 10:00, 11:00, 14:00, 15:00, 16:00, 17:00\n");
    
    // Verifica horários ocupados
    if (!listaVazia(lista)) {
        printf("Horarios ocupados: ");
        No* atual = lista->inicio;
        while (atual != NULL) {
            Agendamento* a = (Agendamento*)atual->dado;
            if (strcmp(a->data, data) == 0 && strcmp(a->sala, sala) == 0) {
                printf("%s ", a->hora);
            }
            atual = atual->proximo;
        }
        printf("\n");
    }
}

void exibirHistoricoCompleto(Lista* lista) {
    printf("\n=== HISTORICO COMPLETO DE AGENDAMENTOS ===\n");
    printf("==================================================================\n");
    printf("  CPF             Sala      Data        Hora     Status\n");
    printf("==================================================================\n");
    
    if (listaVazia(lista)) {
        printf("  Nenhum agendamento registrado.\n");
    } else {
        percorrerLista(lista, exibirAgendamentoHistorico);
    }
    printf("==================================================================\n");
    printf("Total: %d agendamentos\n", tamanhoLista(lista));
}