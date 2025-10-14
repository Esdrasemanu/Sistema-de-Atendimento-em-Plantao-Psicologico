#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Inclui os arquivos que definem as funcoes da fila e historico
#include "fila.h"
#include "historico.h"

/*
 * main.c
 * Fluxo principal do programa:
 *  - Cria fila e historico
 *  - Mostra um menu com opções para inserir na fila, realizar atendimento
 *    (remover da fila e salvar no historico), imprimir fila, consultar
 *    historico por CPF, cancelar inscrição na fila por CPF e imprimir
 *    relatório geral por curso.
 *  - Ao sair, libera as estruturas alocadas.
 *
 * Como testar manualmente:
 * 1) Rodar o programa e escolher opção 1 para inserir vários usuários.
 * 2) Usar opção 3 para verificar que a fila foi preenchida corretamente.
 * 3) Executar opção 2 para chamar o próximo; insira data, psicólogo e resumo.
 *    Em seguida, use opção 4 para consultar o CPF do atendido e confirmar que
 *    o registro foi salvo no histórico.
 * 4) Inserir e cancelar (opção 5) para testar remoção por CPF quando não for
 *    o primeiro da fila.
 * 5) Usar opção 6 para gerar e revisar o relatório por curso.
 *
 * Observações:
 *  - As leituras de texto usam fgets com limites compatíveis com os tamanhos
 *    das strings definidas nas structs.
 *  - O programa simplifica tratamento de erros; melhorias podem incluir validação
 *    de formatos (ex: CPF) e verificação de retornos de inserção.
 */

// Função utilitária para remover o '\n' que fgets deixa no final da string
void clear_nl(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    // Cria as duas estruturas principais do programa
    Fila* fila = criaFila();
    Historico* hist = criaHistorico();
    
    // Variaveis de trabalho
    int opcao;
    Estudante e; // Usada para guardar dados de um estudante
    char cpf[15]; // Usada para buscas por CPF

    // Se nao conseguir criar as estruturas, encerra o programa
    if (!fila || !hist) {
        printf("ERRO: Nao foi possivel iniciar o sistema.\n");
        return 1;
    }

    // Loop principal: repete o menu ate que o usuario escolha a opcao 0 (Sair)
    do {
        // Menu simples
        printf("\n--- SISTEMA DE ATENDIMENTO ---\n");
        printf(" 1 - Chegada (Entrar na Fila)\n");
        printf(" 2 - Atendimento (Chamar Proximo)\n");
        printf(" 3 - Ver Fila\n");
        printf(" 4 - Consultar Historico de um CPF\n");
        printf(" 5 - Cancelar na Fila (por CPF)\n");
        printf(" 6 - Relatorio de Atendimentos\n");
        printf(" 0 - Sair do Sistema\n");
        printf("Escolha uma opcao: ");
        
        // Le a opcao escolhida
        if (scanf("%d", &opcao) != 1) {
             // Se o usuario digitar letra, limpa e tenta de novo
             while (getchar() != '\n'); 
             opcao = -1; 
             continue;
        }
        getchar(); // Limpa o 'Enter' que ficou no buffer apos ler o numero

        // Decide o que fazer com base na opcao
        switch(opcao) {
            case 1: // INSERIR NA FILA (Chegada)
                printf("\n--- REGISTRAR CHEGADA ---\n");
                printf("Nome: ");
                fgets(e.nome, 50, stdin);
                clear_nl(e.nome); // Remove o Enter

                printf("CPF: ");
                fgets(e.cpf, 15, stdin);
                clear_nl(e.cpf);

                printf("Curso: ");
                fgets(e.curso, 50, stdin);
                clear_nl(e.curso);

                insereFila(fila, e);
                printf("-> %s entrou na fila.\n", e.nome);
                break;

            case 2: { // REALIZAR ATENDIMENTO (Remover da Fila e Salvar no Historico)
                Estudante atendido;
                // removeFila tenta tirar o primeiro da fila
                if(removeFila(fila, &atendido)) {
                    printf("\n--- NOVO ATENDIMENTO ---\n");
                    printf("-> Chamando: %s\n", atendido.nome);
                    
                    char data[20], psicologo[50], resumo[200];

                    // Pede os dados do atendimento
                    printf("Data: ");
                    fgets(data, 20, stdin);
                    clear_nl(data);

                    printf("Psicologo: ");
                    fgets(psicologo, 50, stdin);
                    clear_nl(psicologo);

                    printf("Resumo (o que foi conversado): ");
                    fgets(resumo, 200, stdin);
                    clear_nl(resumo);

                    // Adiciona o registro completo ao historico
                    insereAtendimento(hist, atendido.curso, atendido.cpf, data, psicologo, resumo);
                    printf("-> Atendimento salvo no historico.\n");
                } else {
                    printf("-> A fila esta vazia. Ninguem para atender.\n");
                }
                break;
            }

            case 3: // VER FILA
                printf("\n--- FILA DE ESPERA ---\n");
                imprimeFila(fila); // Imprime todos que estao na fila
                break;

            case 4: // CONSULTAR HISTORICO
                printf("\n--- BUSCA POR CPF ---\n");
                printf("Digite o CPF para ver o historico: ");
                fgets(cpf, 15, stdin);
                clear_nl(cpf);
                consultaPorCPF(hist, cpf); // Procura e imprime os atendimentos
                break;

            case 5: // CANCELAR ATENDIMENTO NA FILA
                printf("\n--- CANCELAR ESPERA ---\n");
                printf("Digite o CPF para remover da fila: ");
                fgets(cpf, 15, stdin);
                clear_nl(cpf);
                
                // Tenta remover a pessoa da fila, mesmo que nao seja a primeira
                if (cancelaFila(fila, cpf)) {
                    printf("-> Estudante removido da lista de espera.\n");
                } else {
                    printf("-> CPF nao foi encontrado na fila.\n");
                }
                break;

            case 6: // RELATORIO
                printf("\n--- RELATORIO GERAL POR CURSO ---\n");
                imprimeRelatorio(hist); // Imprime todos os atendimentos agrupados
                break;

            case 0: // SAIR
                printf("\nEncerrando o programa.\n");
                // Libera estruturas antes de sair
                liberaFila(fila);
                liberaHistorico(hist);
                break;

            default:
                printf("Opcao invalida. Escolha um numero de 0 a 6.\n");
        }

    } while(opcao != 0); // Continua o loop enquanto a opcao nao for 0

    return 0;
}