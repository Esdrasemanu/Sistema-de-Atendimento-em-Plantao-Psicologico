#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "paciente.h"
#include "agendamento.h"

Lista* listaPacientes;
Lista* listaAgendamentos;

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menuCadastrarPaciente() {
    Paciente p;
    printf("\n--- CADASTRAR PACIENTE ---\n");
    printf("Nome: "); scanf("%49[^\n]", p.nome); clear_input();
    printf("CPF: "); scanf("%14[^\n]", p.cpf); clear_input();
    printf("Matricula: "); scanf("%19[^\n]", p.matricula); clear_input();
    printf("Curso: "); scanf("%49[^\n]", p.curso); clear_input();
    
    if (cadastrarPaciente(listaPacientes, p)) {
        printf("✅ Paciente cadastrado com sucesso!\n");
    } else {
        printf("❌ Erro ao cadastrar paciente!\n");
    }
}

void menuAgendarConsulta() {
    Agendamento a;
    char cpf[MAX_CPF];
    
    printf("\n--- AGENDAR CONSULTA ---\n");
    printf("CPF do paciente: "); scanf("%14[^\n]", cpf); clear_input();
    
    if (!buscarPacienteCPF(listaPacientes, cpf)) {
        printf("❌ Paciente nao encontrado! Cadastre primeiro.\n");
        return;
    }
    
    strcpy(a.cpf, cpf);
    printf("Sala: "); scanf("%9[^\n]", a.sala); clear_input();
    printf("Data (DD/MM/AAAA): "); scanf("%10[^\n]", a.data); clear_input();
    printf("Hora (HH:MM): "); scanf("%5[^\n]", a.hora); clear_input();
    strcpy(a.status, "agendado");
    
    if (cadastrarAgendamento(listaAgendamentos, a)) {
        printf("✅ Consulta agendada com sucesso!\n");
    } else {
        printf("❌ Erro ao agendar consulta!\n");
    }
}

void menuConsultarCPF() {
    char cpf[MAX_CPF];
    printf("\n--- CONSULTAR POR CPF ---\n");
    printf("CPF: "); scanf("%14[^\n]", cpf); clear_input();
    
    Lista* resultado = buscarAgendamentosCPF(listaAgendamentos, cpf);
    if (resultado) {
        printf("\nAgendamentos para CPF %s:\n", cpf);
        exibirLista(resultado, exibirAgendamentoDetalhado);
        destruirLista(resultado, NULL);
    } else {
        printf("❌ Nenhum agendamento encontrado!\n");
    }
}

void menuConsultarSala() {
    char sala[MAX_SALA];
    printf("\n--- CONSULTAR POR SALA ---\n");
    printf("Sala: "); scanf("%9[^\n]", sala); clear_input();
    
    Lista* resultado = buscarAgendamentosSala(listaAgendamentos, sala);
    if (resultado) {
        printf("\nAgendamentos na Sala %s:\n", sala);
        exibirLista(resultado, exibirAgendamentoDetalhado);
        destruirLista(resultado, NULL);
    } else {
        printf("❌ Nenhum agendamento encontrado!\n");
    }
}

void menuCancelarAgendamento() {
    char cpf[MAX_CPF], data[MAX_DATA];
    printf("\n--- CANCELAR AGENDAMENTO ---\n");
    printf("CPF: "); scanf("%14[^\n]", cpf); clear_input();
    printf("Data (DD/MM/AAAA): "); scanf("%10[^\n]", data); clear_input();
    
    if (cancelarAgendamento(listaAgendamentos, cpf, data)) {
        printf("✅ Agendamento cancelado com sucesso!\n");
    } else {
        printf("❌ Agendamento nao encontrado!\n");
    }
}

void menuHorariosDisponiveis() {
    char data[MAX_DATA], sala[MAX_SALA];
    printf("\n--- HORARIOS DISPONIVEIS ---\n");
    printf("Data (DD/MM/AAAA): "); scanf("%10[^\n]", data); clear_input();
    printf("Sala: "); scanf("%9[^\n]", sala); clear_input();
    
    exibirHorariosDisponiveis(listaAgendamentos, data, sala);
}

void menuHistoricoCompleto() {
    exibirHistoricoCompleto(listaAgendamentos);
}

int main() {
    listaPacientes = criarLista();
    listaAgendamentos = criarLista();
    
    if (!listaPacientes || !listaAgendamentos) {
        printf("❌ Erro ao inicializar sistema!\n");
        return 1;
    }
    
    int opcao;
    do {
        printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Agendar Consulta\n");
        printf("3. Consultar por CPF\n");
        printf("4. Consultar por Sala\n");
        printf("5. Cancelar Agendamento\n");
        printf("6. Horarios Disponiveis\n");
        printf("7. Historico Completo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        clear_input();
        
        switch(opcao) {
            case 1: menuCadastrarPaciente(); break;
            case 2: menuAgendarConsulta(); break;
            case 3: menuConsultarCPF(); break;
            case 4: menuConsultarSala(); break;
            case 5: menuCancelarAgendamento(); break;
            case 6: menuHorariosDisponiveis(); break;
            case 7: menuHistoricoCompleto(); break;
            case 0: printf("👋 Saindo...\n"); break;
            default: printf("❌ Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    destruirLista(listaPacientes, liberarPaciente);
    destruirLista(listaAgendamentos, liberarAgendamento);
    
    return 0;
}