#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "paciente.h"
#include "agendamento.h"
#include "validaCpf.h"
#include "validaDataHora.h"
#include "validaSala.h"

int flagTeste_Cria10Pacientes=0;
int flagDebug_MostraPacientes=0;
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
    // Lê CPF com repetição até ser válido ou o usuário digitar '0' para cancelar
    while (1) {
        printf("CPF (digite 0 para cancelar): "); scanf("%14[^\n]", p.cpf); clear_input();
        if (strcmp(p.cpf, "0") == 0) return;
        if (validarCPF(p.cpf)) break;
        printf("CPF invalido! Tente novamente.\n");
    }
    printf("Matricula: "); scanf("%19[^\n]", p.matricula); clear_input();
    printf("Curso: "); scanf("%49[^\n]", p.curso); clear_input();

    if (!validarCPF(p.cpf)) {
            printf("CPF invalido!\n");
            return;
        }


    if (cadastrarPaciente(listaPacientes, p)) {
        printf("Paciente cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar paciente!\n");
    }
}

void menuAgendarConsulta() {
    Agendamento a;
    char cpf[MAX_CPF];
    
    printf("\n--- AGENDAR CONSULTA ---\n");
    // Repete input ate ser valido
    while (1) {
        printf("CPF do paciente (0 para cancelar): "); scanf("%14[^\n]", cpf); clear_input();
        if (strcmp(cpf, "0") == 0) return;
        if (!validarCPF(cpf)) { printf("CPF invalido!\n"); continue; }
        if (!buscarPacienteCPF(listaPacientes, cpf)) { printf("Paciente nao encontrado! Cadastre primeiro.\n"); continue; }
        break;
    }
        strcpy(a.cpf, cpf);
     // Repete input ate ser valido
    while (1) {
        printf("Sala (0 para cancelar): "); 
        scanf("%9[^\n]", a.sala); 
        clear_input();
        
        if (strcmp(a.sala, "0") == 0) {
            printf("Operacao cancelada.\n");
            return;
        }
        
        if (validarSala(a.sala)) break;
        printf("Sala invalida! ");
        imprimirSalas();
    }
    
    // Repete input ate ser valido
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); 
        scanf("%10[^\n]", a.data); 
        clear_input();
        
        if (strcmp(a.data, "0") == 0) {
            printf("Operacao cancelada.\n");
            return;
        }
        
        if (validarData(a.data)) {
            if (validarDataFutura(a.data)) {
                break;
            } else {
                printf("Data ja passou! Use uma data futura.\n");
            }
        } else {
            printf("Formato de data invalido! Use DD/MM/AAAA.\n");
        }
    }
    
    // Repete input ate ser valido
    while (1) {
        printf("Hora (HH:MM) (0 para cancelar): "); 
        scanf("%5[^\n]", a.hora); 
        clear_input();
        
        if (strcmp(a.hora, "0") == 0) {
            printf("Operacao cancelada.\n");
            return;
        }
        
        if (validarHora(a.hora)) {
            if (validarHoraIntervalo(a.hora)) {
                if (ehDataHoraFutura(a.data, a.hora)) {
                    break;
                } else {
                    printf("Data/hora ja passou! Use uma data/hora futura.\n");
                }
            } else {
                printf("Hora invalida! Use horarios em intervalos de 15 min (ex: 14:00, 14:15, 14:30, 14:45).\n");
            }
        } else {
            printf("Formato de hora invalido! Use HH:MM.\n");
        }
    }
    
    strcpy(a.status, "agendado");

   
    // Verifica disponibilidade da sala no horario
    if (!salaDisponivel(listaAgendamentos, a.sala, a.data, a.hora)) {
        printf("Sala %s ocupada em %s as %s! Escolha outro horario ou sala.\n", a.sala, a.data, a.hora);
        return;
    }

    if (cadastrarAgendamento(listaAgendamentos, a)) {
        printf("Consulta agendada com sucesso!\n");
    } else {
        printf("Erro ao agendar consulta!\n");
    }
}

void menuConsultarCPF() {
    char cpf[MAX_CPF];
    printf("\n--- CONSULTAR POR CPF ---\n");
    // Repetir leitura de CPF até válido ou cancelamento
    while (1) {
        printf("CPF (0 para cancelar): "); scanf("%14[^\n]", cpf); clear_input();
        if (strcmp(cpf, "0") == 0) return;
        if (!validarCPF(cpf)) { printf("CPF invalido!\n"); continue; }
        break;
    }
    Lista* resultado = buscarAgendamentosCPF(listaAgendamentos, cpf);
    if (resultado) {
        printf("\nAgendamentos para CPF %s:\n", cpf);
        exibirLista(resultado, exibirAgendamentoDetalhado);
        destruirLista(resultado, NULL);
    } else {
        printf("Nenhum agendamento encontrado!\n");
    }
}

void menuConsultarSala() {
    char sala[MAX_SALA];
    printf("\n--- CONSULTAR POR SALA ---\n");
    // Repetir leitura de sala até válida ou cancelamento
    while (1) {
        printf("Sala (0 para cancelar): "); scanf("%9[^\n]", sala); clear_input();
        if (strcmp(sala, "0") == 0) return;
        if (!validarSala(sala)) { printf("Sala invalida!\n"); imprimirSalas(); continue; }
        break;
    }
    Lista* resultado = buscarAgendamentosSala(listaAgendamentos, sala);
    if (resultado) {
        printf("\nAgendamentos na Sala %s:\n", sala);
        exibirLista(resultado, exibirAgendamentoDetalhado);
        destruirLista(resultado, NULL);
    } else {
        printf("Nenhum agendamento encontrado!\n");
    }
}

void menuCancelarAgendamento() {
    char cpf[MAX_CPF], data[MAX_DATA];
    printf("\n--- CANCELAR AGENDAMENTO ---\n");
    // Ler CPF (repetir até valido ou cancelar)
    while (1) {
        printf("CPF (0 para cancelar): "); scanf("%14[^\n]", cpf); clear_input();
        if (strcmp(cpf, "0") == 0) return;
        if (!validarCPF(cpf)) { printf("CPF invalido!\n"); continue; }
        break;
    }
    // Ler data (repetir até valida ou cancelar)
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); scanf("%10[^\n]", data); clear_input();
        if (strcmp(data, "0") == 0) return;
        if (!validarData(data)) { printf("Data invalida!\n"); continue; }
        break;
    }

    if (cancelarAgendamento(listaAgendamentos, cpf, data)) {
        printf("Agendamento cancelado com sucesso!\n");
    } else {
        printf("Agendamento nao encontrado!\n");
    }
}

void menuHorariosDisponiveis() {
    char data[MAX_DATA], sala[MAX_SALA];
    printf("\n--- HORARIOS DISPONIVEIS ---\n");
    // Ler data (repetir até valida ou cancelar)
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); scanf("%10[^\n]", data); clear_input();
        if (strcmp(data, "0") == 0) return;
        if (!validarData(data)) { printf("Data invalida!\n"); continue; }
        break;
    }
    // Ler sala (repetir até valida ou cancelar)
    while (1) {
        printf("Sala (0 para cancelar): "); scanf("%9[^\n]", sala); clear_input();
        if (strcmp(sala, "0") == 0) return;
        if (!validarSala(sala)) { printf("Sala invalida!\n"); imprimirSalas(); continue; }
        break;
    }
    exibirHorariosDisponiveis(listaAgendamentos, data, sala);
}

void menuHistoricoCompleto() {
    exibirHistoricoCompleto(listaAgendamentos);
}

void menuSalasLivres() {
    char data[MAX_DATA], hora[MAX_HORA];
    printf("\n--- SALAS LIVRES ---\n");
    
    // Ler data (repetir até valida ou cancelar)
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); 
        scanf("%10[^\n]", data); 
        clear_input();
        if (strcmp(data, "0") == 0) return;
        if (!validarData(data)) { 
            printf("Data invalida!\n"); 
            continue; 
        }
        break;
    }
    
    // Ler hora (repetir até valida ou cancelar)
    while (1) {
        printf("Hora (HH:MM) (0 para cancelar): "); 
        scanf("%5[^\n]", hora); 
        clear_input();
        if (strcmp(hora, "0") == 0) return;
        if (!validarHora(hora)) { 
            printf("Hora invalida!\n"); 
            continue; 
        }
        break;
    }
    
    exibirSalasLivres(listaAgendamentos, data, hora);
}

void menuProximosAgendamentos() {
    int quantidade;
    printf("\n--- PROXIMOS AGENDAMENTOS ---\n");
    printf("Quantidade a mostrar (0 para todos): ");
    scanf("%d", &quantidade);
    clear_input();
    
    if (quantidade < 0) {
        printf("Quantidade invalida!\n");
        return;
    }
    
    exibirProximosAgendamentos(listaAgendamentos, quantidade);
}

int main() {

    


    listaPacientes = criarLista();
    listaAgendamentos = criarLista();
    
    if (!listaPacientes || !listaAgendamentos) {
        printf("Erro ao inicializar sistema!\n");
        return 1;
    }
    
    if (flagTeste_Cria10Pacientes == 1) {
    Paciente p1 = {"João Silva", "25075653065", "20240001", "Engenharia"};
        cadastrarPaciente(listaPacientes, p1);
        
        Paciente p2 = {"Maria Santos", "88288718060", "20240002", "Medicina"};
        cadastrarPaciente(listaPacientes, p2);
        
        Paciente p3 = {"Pedro Costa", "099.423.780-49", "20240003", "Direito"};
        cadastrarPaciente(listaPacientes, p3);
        
        Paciente p4 = {"Ana Oliveira", "216.788.690-07", "20240004", "Administração"};
        cadastrarPaciente(listaPacientes, p4);
        
        Paciente p5 = {"Carlos Lima", "912.435.810-00", "20240005", "Psicologia"};
        cadastrarPaciente(listaPacientes, p5);
        
        Paciente p6 = {"Beatriz Souza", "476.839.200-88", "20240006", "Arquitetura"};
        cadastrarPaciente(listaPacientes, p6);
        
        Paciente p7 = {"Lucas Pereira", "717.785.530-01", "20240007", "Enfermagem"};
        cadastrarPaciente(listaPacientes, p7);
        
        Paciente p8 = {"Juliana Rocha", "378.242.540-54", "20240008", "Farmácia"};
        cadastrarPaciente(listaPacientes, p8);
        
        Paciente p9 = {"Ricardo Alves", "155.073.530-69", "20240009", "Veterinária"};
        cadastrarPaciente(listaPacientes, p9);
        
        Paciente p10 = {"Fernanda Martins", "419.603.620-11", "20240010", "Pedagogia"};
        cadastrarPaciente(listaPacientes, p10);
        
        printf("✅ %d pacientes de teste criados!\n", tamanhoLista(listaPacientes));

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
        printf("8. Mostrar Salas Livres (por data/hora)\n");
        printf("9. Proximos Agendamentos\n");
        printf("0. Sair\n");
        if(flagDebug_MostraPacientes==1){
            if (!listaVazia(listaPacientes)) {
            printf("Pacientes: ");
            No* atual = listaPacientes->inicio;
            int count = 0;
            while (atual != NULL) {
                Paciente* p = (Paciente*)atual->dado;
                printf("%s(%s)", p->nome, p->cpf);
                atual = atual->proximo;
                if (atual != NULL) {
                    printf(", ");
                    count++;
                    if (count % 2 == 0) printf("\n           "); // Quebra a cada 2
                }
            }
            printf("\n");
        }
}
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
            case 8: menuSalasLivres(); break;
            case 9: menuProximosAgendamentos();break;
            case 0: printf("Saindo...\n"); break;
            default: printf("opcao invalida!\n");
        }
    } while(opcao != 0);
    
    destruirLista(listaPacientes, liberarPaciente);
    destruirLista(listaAgendamentos, liberarAgendamento);
    
    return 0;
}