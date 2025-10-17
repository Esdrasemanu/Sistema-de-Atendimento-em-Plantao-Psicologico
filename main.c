#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "paciente.h"
#include "agendamento.h"
#include "validaCpf.h"
#include "validaDataHora.h"
#include "validaSala.h"

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

int flagTeste_Cria10Pacientes=0;
int flagDebug_MostraPacientes=0;
Lista* listaPacientes;
Lista* listaAgendamentos;
char ultimoCpf[MAX_CPF] = "";


void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Imprime uma lista com cabecalho com horario e salas livres para agendamento de consulta, em data passada por parametro. (é utilizada por menuMostraSalaseHorarios() )
 * @autor [andrericardo]
 */
void exibirTodasSalasLivresData(const char* data) {  
    printf("\n+--------------------------------------------------------------+\n");
    printf("|            SALAS LIVRES EM %s                          |\n", data);
    printf("+--------+-----------------------------------------------------+\n");
    printf("|  Hora  |                    Salas Livres                    |\n");
    printf("+--------+-----------------------------------------------------+\n");
    
    // Horários fixos do dia
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
    
    int totalHorarios = 36;
    
    for (int i = 0; i < totalHorarios; i++) {
        printf("| %-6s | ", horarios[i]);
        
        int salasLivres = 0;
        for (int j = 0; j < SALAS_COUNT; j++) {
            const char* sala = getSalaNome(j);
            if (salaDisponivel(listaAgendamentos, sala, data, horarios[i])) {
                printf("%s ", sala);
                salasLivres++;
            }
        }
        
        if (salasLivres == 0) {
            printf("Nenhuma sala livre");
            for (int k = 0; k < 20; k++) printf(" ");
        } else {
            int espacos = 45 - (salasLivres * 3);
            for (int k = 0; k < espacos; k++) printf(" ");
        }
        
        printf("|\n");
    }
    
    printf("+--------+-----------------------------------------------------+\n");
}

void menuCadastrarPaciente() {
    CLEAR_SCREEN();
    Paciente p;
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- CADASTRAR PACIENTE ---\n");
    printf("Nome: "); scanf("%49[^\n]", p.nome); clear_input();
    
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
        // ATUALIZA O ÚLTIMO CPF CADASTRADO
        strcpy(ultimoCpf, p.cpf);
        printf("\nPaciente cadastrado com sucesso!\n");
    } else {
        printf("\nErro ao cadastrar paciente!\n");
    }
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

void menuAgendarConsulta() {
    CLEAR_SCREEN();
    Agendamento a;
    char cpf[MAX_CPF];
    
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- AGENDAR CONSULTA ---\n");
    
    while (1) {
        printf("CPF do paciente (0 para cancelar, 4 para ultimo paciente): "); 
        scanf("%14[^\n]", cpf); 
        clear_input();
        
        // Opção 0: Cancelar
        if (strcmp(cpf, "0") == 0) return;
        
        // Opção 4: Usar último paciente
        if (strcmp(cpf, "4") == 0) {
            if (strlen(ultimoCpf) == 0) {
                printf("Nenhum paciente cadastrado recentemente!\n");
                continue;
            }
            strcpy(cpf, ultimoCpf);
            printf("Usando ultimo paciente: %s\n", cpf);
        }
        
        if (!validarCPF(cpf)) { 
            printf("CPF invalido!\n"); 
            continue; 
        }
        
        if (!buscarPacienteCPF(listaPacientes, cpf)) { 
            printf("Paciente nao encontrado! Cadastre primeiro.\n"); 
            continue; 
        }
        break;
    }
    
    strcpy(a.cpf, cpf);
    
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

    if (!salaDisponivel(listaAgendamentos, a.sala, a.data, a.hora)) {
        printf("\nSala %s ocupada em %s as %s! Escolha outro horario ou sala.\n", a.sala, a.data, a.hora);
    } else if (cadastrarAgendamento(listaAgendamentos, a)) {
        printf("\nConsulta agendada com sucesso!\n");
    } else {
        printf("\nErro ao agendar consulta!\n");
    }
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

void menuConsultarCPF() {
    CLEAR_SCREEN();
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- CONSULTAR POR CPF ---\n");
    
    if (!temAgendamentos(listaAgendamentos)) {
        printf("Nenhum agendamento cadastrado no sistema!\n");
        printf("\nPressione Enter para continuar...");
        clear_input();
        return;
    }
    
    char cpf[MAX_CPF];
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
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

void menuConsultarSala() {
    CLEAR_SCREEN();
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- CONSULTAR POR SALA ---\n");
    
    if (!temAgendamentos(listaAgendamentos)) {
        printf("Nenhum agendamento cadastrado no sistema!\n");
        printf("\nPressione Enter para continuar...");
        clear_input();
        return;
    }
    
    char sala[MAX_SALA];
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
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

void menuCancelarAgendamento() {
    CLEAR_SCREEN();
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- CANCELAR AGENDAMENTO ---\n");
    
    if (!temAgendamentos(listaAgendamentos)) {
        printf("Nenhum agendamento cadastrado no sistema!\n");
        printf("\nPressione Enter para continuar...");
        clear_input();
        return;
    }
    
    char cpf[MAX_CPF], data[MAX_DATA];
    
    while (1) {
        printf("CPF (0 para cancelar): "); scanf("%14[^\n]", cpf); clear_input();
        if (strcmp(cpf, "0") == 0) return;
        if (!validarCPF(cpf)) { printf("CPF invalido!\n"); continue; }
        break;
    }
    
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); scanf("%10[^\n]", data); clear_input();
        if (strcmp(data, "0") == 0) return;
        if (!validarData(data)) { printf("Data invalida!\n"); continue; }
        break;
    }

    if (cancelarAgendamento(listaAgendamentos, cpf, data)) {
        printf("\nAgendamento cancelado com sucesso!\n");
    } else {
        printf("\nAgendamento nao encontrado!\n");
    }
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

/**
 * @brief Pede input de data e sala, e imprime horarios disponiveis
 * @autor [andrericardo]
 */
void menuHorariosDisponiveis() {
    CLEAR_SCREEN();
    char data[MAX_DATA], sala[MAX_SALA];
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- HORARIOS DISPONIVEIS ---\n");
    
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); scanf("%10[^\n]", data); clear_input();
        if (strcmp(data, "0") == 0) return;
        if (!validarData(data)) { printf("Data invalida!\n"); continue; }
        break;
    }
    
    while (1) {
        printf("Sala (0 para cancelar): "); scanf("%9[^\n]", sala); clear_input();
        if (strcmp(sala, "0") == 0) return;
        if (!validarSala(sala)) { printf("Sala invalida!\n"); imprimirSalas(); continue; }
        break;
    }
    
    exibirHorariosDisponiveis(listaAgendamentos, data, sala);
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

/**
 * @brief Imprime a lista agendamento, nesse caso tratado como "historico de agendamentos feitos."
 * @autor [andrericardo]
 */
void menuHistoricoCompleto() {
    CLEAR_SCREEN();
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    exibirHistoricoCompleto(listaAgendamentos);
    printf("\nPressione Enter para continuar...");
    clear_input();
}

/**
 * @brief Pede input de data e horario, e imprime salas disponiveis
 * @autor [andrericardo]
 */
void menuSalasDisponiveis() {
    CLEAR_SCREEN();
    char data[MAX_DATA], hora[MAX_HORA];
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- SALAS LIVRES ---\n");
    
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
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

/**
 * @brief Funcao utilitaria que calcula e atualiza a proxima data (proximo dia) a partir de uma data informada
 *
 * leva em consideracao o numero de dias de cada mes e os anos bissextos.
 * O resultado e escrito de volta na mesma string fornecida como parametro.
 * @autor [andrericardo]
 */
void calcularProximaData(char *data) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        diasNoMes[1] = bissexto ? 29 : 28;
    }
    
    dia++;
    
    if (dia > diasNoMes[mes - 1]) {
        dia = 1;
        mes++;
        
        if (mes > 12) {
            mes = 1;
            ano++;
        }
    }
    
    sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
}

/**
 * @brief Funcao utilitaria que calcula e atualiza a data anterior (dia anterior) a partir de uma data informada
 *
 * leva em consideracao o numero de dias de cada mes e os anos bissextos.
 * O resultado e escrito de volta na mesma string fornecida como parametro.
 * @autor [andrericardo]
 */
void calcularDataAnterior(char *data) {
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    dia--;
    
    if (dia < 1) {
        mes--;
        
        if (mes < 1) {
            mes = 12;
            ano--;
        }
        
        if (mes == 2) {
            int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
            diasNoMes[1] = bissexto ? 29 : 28;
        }
        
        dia = diasNoMes[mes - 1];
    }
    
    sprintf(data, "%02d/%02d/%04d", dia, mes, ano);
}

/**
 * @brief Funcao que coleta data e permite o sistema de navegacao para mostrar listas implementadas na funcao exibirTodasSalasLivresData().
 * @autor [andrericardo]
 */
void menuMostraSalaseHorarios() {
    CLEAR_SCREEN();
    char data[MAX_DATA];
    int navegacao;
    
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- VISUALIZAR TODAS SALAS LIVRES ---\n");
    
    while (1) {
        printf("Data (DD/MM/AAAA) (0 para cancelar): "); 
        scanf("%10[^\n]", data); 
        
        clear_input();
        
        if (strcmp(data, "0") == 0) return;
        if ((!validarData(data)) || (!validarDataFutura(data))) {
            printf("Data invalida!\n"); 
            continue; 
        }
        break;
    }
    

            
            


    do {
        CLEAR_SCREEN();
        printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
        exibirTodasSalasLivresData(data);
        
        printf("| Data: %-45s |\n", data);
        printf("+--------------------------------------------------------------+\n");
        printf("| [3] Data anterior | [0] Sair | [1] Proxima data | [2] Nova data |\n");
        printf("+--------------------------------------------------------------+\n");
        printf("Escolha: ");
        
        scanf("%d", &navegacao);
        clear_input();
        
        if (navegacao == 1) {
            calcularProximaData(data);
        }
        else if (navegacao == 3) {
            calcularDataAnterior(data);
        }
        else if (navegacao == 2) {
            while (1) {
                printf("Nova data (DD/MM/AAAA): "); 
                scanf("%10[^\n]", data); 
                clear_input();
                
                if (!validarData(data)) { 
                    printf("Data invalida!\n"); 
                    continue; 
                }
                break;
            }
        }
        
    } while (navegacao != 0);
}

void menuProximosAgendamentos() {
    CLEAR_SCREEN();
    int quantidade;
    printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
    printf("--- PROXIMOS AGENDAMENTOS ---\n");
    printf("Quantidade a mostrar (0 para todos): ");
    scanf("%d", &quantidade);
    clear_input();
    
    if (quantidade < 0) {
        printf("Quantidade invalida!\n");
    } else {
        exibirProximosAgendamentos(listaAgendamentos, quantidade);
    }
    
    printf("\nPressione Enter para continuar...");
    clear_input();
}

int main() {
    listaPacientes = criarLista();
    listaAgendamentos = criarLista();
    
    if (!listaPacientes || !listaAgendamentos) {
        printf("Erro ao inicializar sistema!\n");
        return 1;
    }
    
    if (flagTeste_Cria10Pacientes == 1) {

    }

    int opcao;
    do {
        CLEAR_SCREEN();
        printf("\n=== SISTEMA DE AGENDAMENTO ===\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Agendar Consulta\n");
        printf("3. Consultar por CPF\n");
        printf("4. Consultar por Sala\n");
        printf("5. Cancelar Agendamento\n");
        printf("7. Historico Completo\n");
        printf("9. Proximos Agendamentos\n");
        printf("10. Mostrar Salas e Horarios Disponiveis\n");
        printf("11. Mostrar Salas Disponiveis (por data/hora)\n");
        printf("12. Mostrar Horarios Disponiveis (por sala)\n");
        printf("0. Sair\n");

        if(flagDebug_MostraPacientes==1){
            // ... (código debug permanece igual)
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
            case 7: menuHistoricoCompleto(); break;
            case 9: menuProximosAgendamentos(); break;
            case 10: menuMostraSalaseHorarios(); break;
            case 11: menuSalasDisponiveis(); break;
            case 12: menuHorariosDisponiveis(); break;
            case 0: printf("Saindo...\n"); break;
            default: 
                printf("Opcao invalida! Pressione Enter para continuar...");
                clear_input();
        }
    } while(opcao != 0);
    
    destruirLista(listaPacientes, liberarPaciente);
    destruirLista(listaAgendamentos, liberarAgendamento);
    
    return 0;
}