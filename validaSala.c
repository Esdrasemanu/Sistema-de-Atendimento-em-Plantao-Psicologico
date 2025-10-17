#include <stdio.h>
#include <string.h>
#include "validaSala.h"
#include "validaDataHora.h"  // ← ATUALIZADO: inclui o novo header
#include "agendamento.h"

static const char* SALAS[SALAS_COUNT] = {"A1","A2","A3","B1","B2","B3","C1","C2","C3"};

int validarSala(const char* sala) {
    if (!sala) return 0;
    for (int i = 0; i < SALAS_COUNT; ++i) {
        if (strcmp(sala, SALAS[i]) == 0) return 1;
    }
    return 0;
}

void imprimirSalas(void) {
    printf("Salas disponiveis:\n");
    for (int i = 0; i < SALAS_COUNT; ++i) {
        printf(" %s", SALAS[i]);
        if ((i+1) % 3 == 0) printf("\n");
    }
}

const char* getSalaNome(int idx) {
    if (idx < 0 || idx >= SALAS_COUNT) return NULL;
    return SALAS[idx];
}

// ATUALIZADO: usa validarData e validarHora do novo código
int salaDisponivel(Lista* lista, const char* sala, const char* data, const char* hora) {
    if (!validarSala(sala)) return 0;
    if (!validarData(data) || !validarHora(hora)) return 0; // usa funções mantidas
    if (listaVazia(lista)) return 1;

    No* atual = lista->inicio;
    while (atual) {
        Agendamento* a = (Agendamento*)atual->dado;
        if (strcmp(a->sala, sala) == 0 && strcmp(a->data, data) == 0 && strcmp(a->hora, hora) == 0) {
            return 0; // ocupada
        }
        atual = atual->proximo;
    }
    return 1; // disponível
}