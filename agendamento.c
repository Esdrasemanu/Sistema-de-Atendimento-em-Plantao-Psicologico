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
    // Validacoes em camadas
    if (!validarCPF(a.cpf)) {
        printf("CPF invalido!\n");
        return 0;
    }
    
    if (!validarSala(a.sala)) {
        printf("Sala invalida! ");
        imprimirSalas();
        return 0;
    }
    
    if (!validarData(a.data)) {
        printf("Formato de data invalido! Use DD/MM/AAAA.\n");
        return 0;
    }
    
    if (!validarDataFutura(a.data)) {
        printf("Data ja passou! Use uma data futura.\n");
        return 0;
    }
    
    if (!validarHora(a.hora)) {
        printf("Formato de hora invalido! Use HH:MM.\n");
        return 0;
    }
    
    if (!validarHoraIntervalo(a.hora)) {
        printf("Hora invalida! Use horarios em intervalos de 15 min (ex: 14:00, 14:15, 14:30, 14:45).\n");
        return 0;
    }
    
    if (!ehDataHoraFutura(a.data, a.hora)) {
        printf("Data/hora ja passou! Use uma data/hora futura.\n");
        return 0;
    }
    
    // Verifica se a sala está disponível na data/hora
    if (!salaDisponivel(lista, a.sala, a.data, a.hora)) {
        printf("Sala %s ja esta ocupada em %s as %s!\n", a.sala, a.data, a.hora);
        return 0;
    }

    Agendamento* novo = (Agendamento*)malloc(sizeof(Agendamento));
    if (!novo) return 0;
    *novo = a;
    return inserirFinal(lista, novo);
}


/**
 * @brief Funcao que implementa verificao de lista vazia da lista generica.
 * @autor [andrericardo]
 */
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

/**
 * @brief Funcao que mostra horarios disponiveis em uma data e sala, strings passadas por parametro, e usando a lista de agendamentos
 * @autor [andrericardo]
 */
void exibirHorariosDisponiveis(Lista* lista, const char* data, const char* sala) {
    printf("\n+--------------------------------------------------------------+\n");
    printf("| HORARIOS DISPONIVEIS - %s - Sala %s |\n", data, sala);
    printf("+--------+------------+\n");
    printf("| Hora   | Disponivel |\n");
    printf("+--------+------------+\n");
    
    // Todos os horários possíveis do dia
    char* horarios[] = {
        "08:00", "08:15", "08:30", "08:45",
        "09:00", "09:15", "09:30", "09:45", 
        "10:00", "10:15", "10:30", "10:45",
        "11:00", "11:15", "11:30", "11:45",
        "12:00", "12:15", "12:30", "12:45",
        "13:00", "13:15", "13:30", "13:45",
        "14:00", "14:15", "14:30", "14:45",
        "15:00", "15:15", "15:30", "15:45",
        "16:00", "16:15", "16:30", "16:45",
        "17:00", "17:15", "17:30", "17:45"
    };
    
    int totalHorarios = 40;
    int horariosLivres = 0;
    
    for (int i = 0; i < totalHorarios; i++) {
        int disponivel = 1; // Assume que está livre
        
        // Verifica se há algum agendamento neste horário
        if (!listaVazia(lista)) {
            No* atual = lista->inicio;
            while (atual != NULL) {
                Agendamento* a = (Agendamento*)atual->dado;
                if (strcmp(a->data, data) == 0 && 
                    strcmp(a->sala, sala) == 0 && 
                    strcmp(a->hora, horarios[i]) == 0 &&
                    strcmp(a->status, "agendado") == 0) {
                    disponivel = 0; // Está ocupado
                    break;
                }
                atual = atual->proximo;
            }
        }
        
        if (disponivel) {
            printf("| %-6s |    LIVRE   |\n", horarios[i]);
            horariosLivres++;
        } else {
            printf("| %-6s |  OCUPADO   |\n", horarios[i]);
        }
    }
    
    printf("+--------+------------+\n");
    printf("| Total de horarios livres: %-28d |\n", horariosLivres);
    printf("+--------------------------------------------------------------+\n");
}

/**
 * @brief Funcao que mostra horarios disponiveis em uma sala e horario , strings passadas por parametro, e usando a lista de agendamentos
 * @autor [andrericardo]
 */
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
        printf("Nenhuma sala livre neste horario!");
    }
    printf("\n");
}

/**
 * @brief Funcao utilitaria usada por exibirHistoricoCompleto(), que exibe todos os dados de um no da lista agendamento
 * @autor [andrericardo]
 */
void UTILexibirAgendamentoLinha(void* dado) {
    Agendamento* a = (Agendamento*)dado;
    printf("| %-18s | %-6s | %-10s | %-6s | %-7s |\n", 
           a->cpf, a->sala, a->data, a->hora, a->status);                  
}

/**
 * @brief Funcao que mostra uma lista com cabecalho, e percorre a lista usando a funcao utilitaria UTILexibirAgendamentoLinha(), assim mostrando os registros em ordem de insercao na lista
 * @autor [andrericardo]
 */
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


/**
 * @brief Funcao auxiliar para comparar datas (para ordenacao)
 * @autor [andrericardo]
 */
int compararDatas(const char* data1, const char* data2) {
    int dia1, mes1, ano1, dia2, mes2, ano2;
    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);
    
    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

/**
 * @brief Funcao auxiliar para comparar datas E hora (pra ordenacao)
 * @autor [andrericardo]
 */
int compararDataHora(Agendamento* a1, Agendamento* a2) {
    // Primeiro compara as datas
    int cmpData = compararDatas(a1->data, a2->data);
    if (cmpData != 0) return cmpData;
    
    // Se mesma data, compara as horas
    return strcmp(a1->hora, a2->hora);
}

/**
 * @brief Funcao que ordena os agendamentos por data e hora em uma nova lista (nao modifica estrutura da lista original)
 * @autor [andrericardo]
 */
void ordenarAgendamentosPorDataHora(Lista* lista) {
    if (listaVazia(lista) || lista->inicio->proximo == NULL) return;
    
    No* ordenado = NULL;
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        No* proximo = atual->proximo;
        
        // Insere o nó atual na lista ordenada
        if (ordenado == NULL || compararDataHora(((Agendamento*)atual->dado), 
                                               ((Agendamento*)ordenado->dado)) < 0) {
            // Insere no início
            atual->proximo = ordenado;
            ordenado = atual;
        } else {
            // Encontra a posição correta
            No* temp = ordenado;
            while (temp->proximo != NULL && 
                   compararDataHora(((Agendamento*)atual->dado),
                                   ((Agendamento*)temp->proximo->dado)) >= 0) {
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



/**
 * @brief Funcao auxiliar para criar uma copia da lista
 * @autor [andrericardo]
 */

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


/**
 * @brief Funcao para mostrar proximos agendamentos (registros da lista original, porem em ordem cronologica)
 * @autor [andrericardo]
 */

void exibirProximosAgendamentos(Lista* lista, int quantidade) {
    if (listaVazia(lista)) {
        printf("\n Nenhum agendamento registrado!\n");
        return;
    }
    
    Lista* copia = criarLista();
    if (!copia) {
        printf("Erro ao criar copia da lista!\n");
        return;
    }
    
    // Filtrar apenas agendamentos futuros com status "agendado"
    No* atual = lista->inicio;
    while (atual != NULL) {
        Agendamento* ag = (Agendamento*)atual->dado;
        
        // Verifica se é agendamento futuro e com status agendado
        if (strcmp(ag->status, "agendado") == 0 && ehDataHoraFutura(ag->data, ag->hora)) {
            Agendamento* novoAg = malloc(sizeof(Agendamento));
            if (novoAg) {
                strcpy(novoAg->cpf, ag->cpf);
                strcpy(novoAg->sala, ag->sala);
                strcpy(novoAg->data, ag->data);
                strcpy(novoAg->hora, ag->hora);
                strcpy(novoAg->status, ag->status);
                inserirFinal(copia, novoAg); 
            }
        }
        atual = atual->proximo;
    }
    
    if (listaVazia(copia)) {
        printf("\n Nenhum agendamento futuro encontrado!\n");
        destruirLista(copia, liberarAgendamento);
        return;
    }
    
    // Ordena a cópia por data E hora
    ordenarAgendamentosPorDataHora(copia);
    
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                 PROXIMOS AGENDAMENTOS                      |\n");
    printf("+---------------------+--------+------------+--------+---------+\n");
    printf("|         CPF         |  Sala  |    Data    |  Hora  | Status  |\n");
    printf("+---------------------+--------+------------+--------+---------+\n");
    
    // Exibe apenas a quantidade solicitada (ou todos se quantidade = 0)
    int contador = 0;
    int totalFuturos = tamanhoLista(copia);
    atual = copia->inicio;
    
    while (atual != NULL && (quantidade == 0 || contador < quantidade)) {
        Agendamento* a = (Agendamento*)atual->dado;
        printf("| %-18s | %-6s | %-10s | %-6s | %-7s |\n", 
               a->cpf, a->sala, a->data, a->hora, a->status);
        atual = atual->proximo;
        contador++;
    }
    
    printf("+---------------------+--------+------------+--------+---------+\n");
    printf("| Mostrando %-2d de %-36d agendamentos |\n", 
           contador, totalFuturos);
    printf("+--------------------------------------------------------------+\n");
    
    // Libera a copia
    destruirLista(copia, liberarAgendamento);
}