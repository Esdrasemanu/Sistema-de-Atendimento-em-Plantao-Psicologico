#include "agendamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaCpf.h"
#include "validaDataHora.h"
#include "validaSala.h"

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
    // Validações em camadas
    if (!validarCPF(a.cpf)) {
        printf("❌ CPF invalido!\n");
        return 0;
    }
    
    if (!validarSala(a.sala)) {
        printf("❌ Sala invalida! ");
        imprimirSalas();
        return 0;
    }
    
    if (!validarData(a.data)) {
        printf("❌ Formato de data invalido! Use DD/MM/AAAA.\n");
        return 0;
    }
    
    if (!validarDataFutura(a.data)) {
        printf("❌ Data ja passou! Use uma data futura.\n");
        return 0;
    }
    
    if (!validarHora(a.hora)) {
        printf("❌ Formato de hora invalido! Use HH:MM.\n");
        return 0;
    }
    
    if (!validarHoraIntervalo(a.hora)) {
        printf("❌ Hora invalida! Use horarios em intervalos de 15 min (ex: 14:00, 14:15, 14:30, 14:45).\n");
        return 0;
    }
    
    if (!ehDataHoraFutura(a.data, a.hora)) {
        printf("❌ Data/hora ja passou! Use uma data/hora futura.\n");
        return 0;
    }
    
    // Verifica se a sala está disponível na data/hora
    if (!salaDisponivel(lista, a.sala, a.data, a.hora)) {
        printf("❌ Sala %s ja esta ocupada em %s as %s!\n", a.sala, a.data, a.hora);
        return 0;
    }

    Agendamento* novo = (Agendamento*)malloc(sizeof(Agendamento));
    if (!novo) return 0;
    *novo = a;
    return inserirFinal(lista, novo);
}


// NOVA função para verificar se há agendamentos
int temAgendamentos(Lista* lista) {
    return !listaVazia(lista);
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

void exibirSalasLivres(Lista* lista, const char* data, const char* hora) {
    printf("\nSalas livres em %s as %s:\n", data, hora);
    
    int salasLivres = 0;
    for (int i = 0; i < SALAS_COUNT; ++i) {
        const char* s = getSalaNome(i);
        if (salaDisponivel(lista, s, data, hora)) {
            printf(" %s", s);
            salasLivres++;
        }
    }
    
    if (salasLivres == 0) {
        printf(" ❌ Nenhuma sala livre neste horario!");
    }
    printf("\n");
}

void UTILexibirAgendamentoLinha(void* dado) {
    Agendamento* a = (Agendamento*)dado;
    printf("| %-18s | %-6s | %-10s | %-6s | %-7s |\n", 
           a->cpf, a->sala, a->data, a->hora, a->status);                  
}

void exibirHistoricoCompleto(Lista* lista) {
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                   HISTORICO DE AGENDAMENTOS                 |\n");
    printf("+---------------------+--------+------------+--------+---------+\n");
    printf("|         CPF         |  Sala  |    Data    |  Hora  | Status  |\n");
    printf("+---------------------+--------+------------+--------+---------+\n");
    
    if (listaVazia(lista)) {
        printf("|              Nenhum agendamento registrado               |\n");
    } else {
        percorrerLista(lista, UTILexibirAgendamentoLinha);
    }
    
    printf("+---------------------+--------+------------+--------+---------+\n");
    printf("| Total: %-3d agendamentos |\n", tamanhoLista(lista));

}

// Função auxiliar para comparar datas (para ordenacao)
int compararDatas(const char* data1, const char* data2) {
    int dia1, mes1, ano1, dia2, mes2, ano2;
    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);
    
    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

// Funcao auxiliar para ordenar uma lista de agendamentos por data (Insertion Sort)

void ordenarAgendamentosPorData(Lista* lista) {
    if (listaVazia(lista) || lista->inicio->proximo == NULL) return;
    
    No* ordenado = NULL;
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        No* proximo = atual->proximo;
        
        // Insere o nó atual na lista ordenada
        if (ordenado == NULL || compararDatas(((Agendamento*)atual->dado)->data, 
                                            ((Agendamento*)ordenado->dado)->data) < 0) {
            // Insere no início
            atual->proximo = ordenado;
            ordenado = atual;
        } else {
            // Encontra a posição correta
            No* temp = ordenado;
            while (temp->proximo != NULL && 
                   compararDatas(((Agendamento*)atual->dado)->data,
                                ((Agendamento*)temp->proximo->dado)->data) >= 0) {
                temp = temp->proximo;
            }
            atual->proximo = temp->proximo;
            temp->proximo = atual;
        }
        
        atual = proximo;
    }
    
    lista->inicio = ordenado;
    
    // Atualiza o ponteiro fim
    No* temp = ordenado;
    while (temp != NULL && temp->proximo != NULL) {
        temp = temp->proximo;
    }
    lista->fim = temp;
}

// Funcao para criar uma copia profunda da lista
Lista* copiarListaAgendamentos(Lista* original) {
    if (!original) return NULL;
    
    Lista* copia = criarLista();
    if (!copia) return NULL;
    
    No* atual = original->inicio;
    while (atual != NULL) {
        Agendamento* ag_original = (Agendamento*)atual->dado;
        Agendamento* ag_copia = (Agendamento*)malloc(sizeof(Agendamento));
        if (!ag_copia) {
            destruirLista(copia, liberarAgendamento);
            return NULL;
        }
        
        // Cópia profunda dos dados
        *ag_copia = *ag_original;
        
        if (!inserirFinal(copia, ag_copia)) {
            free(ag_copia);
            destruirLista(copia, liberarAgendamento);
            return NULL;
        }
        
        atual = atual->proximo;
    }
    
    return copia;
}

// Nova funcao para mostrar proximos agendamentos 
void exibirProximosAgendamentos(Lista* lista, int quantidade) {
    if (listaVazia(lista)) {
        printf("\n Nenhum agendamento registrado!\n");
        return;
    }
    
    // CORREÇÃO: Cria uma cópia PROFUNDA da lista para ordenar
    Lista* copia = copiarListaAgendamentos(lista);
    if (!copia) {
        printf("Erro ao criar copia da lista!\n");
        return;
    }
    
    // Ordena a cópia por data (NÃO afeta a original)
    ordenarAgendamentosPorData(copia);
    
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                 PROXIMOS AGENDAMENTOS                      |\n");
    printf("+---------------------+--------+------------+--------+---------+\n");
    printf("|         CPF         |  Sala  |    Data    |  Hora  | Status  |\n");
    printf("+---------------------+--------+------------+--------+---------+\n");
    
    // Exibe apenas a quantidade solicitada (ou todos se quantidade = 0)
    int contador = 0;
    No* atual = copia->inicio;
    
    while (atual != NULL && (quantidade == 0 || contador < quantidade)) {
        Agendamento* a = (Agendamento*)atual->dado;
        printf("| %-18s | %-6s | %-10s | %-6s | %-7s |\n", 
               a->cpf, a->sala, a->data, a->hora, a->status);
        atual = atual->proximo;
        contador++;
    }
    
    printf("+---------------------+--------+------------+--------+---------+\n");
    printf("| Mostrando %-2d de %-36d agendamentos |\n", 
           contador, tamanhoLista(lista));
    printf("+--------------------------------------------------------------+\n");
    
    // Libera a copia
    destruirLista(copia, liberarAgendamento);
}