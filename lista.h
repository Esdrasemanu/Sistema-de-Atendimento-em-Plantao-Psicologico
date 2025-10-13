#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura de um nó da lista encadeada
 * @details Usa void* para ser genérico e armazenar qualquer tipo de dado
 * @autor [andrericardo]
 */
typedef struct no {
    void* dado;           // Ponteiro genérico para os dados
    struct no* proximo;   // Ponteiro para o próximo nó
} No;

/**
 * @brief Estrutura da lista com cabeçalho
 * @details Mantém controle do início, fim e quantidade de elementos
 * @autor [andrericardo]
 */
typedef struct {
    No* inicio;          // Primeiro elemento da lista
    No* fim;             // Último elemento da lista
    int quantidade;      // Número de elementos na lista
} Lista;

/**
 * @brief Cria e inicializa uma nova lista vazia
 * @return Ponteiro para a lista criada ou NULL em caso de erro
 * @autor [andrericardo]
 */
Lista* criarLista();

/**
 * @brief Verifica se a lista está vazia
 * @param lista Ponteiro para a lista
 * @return 1 se vazia, 0 se não vazia, -1 se lista inválida
 * @autor [andrericardo]
 */
int listaVazia(Lista* lista);

/**
 * @brief Insere um elemento no FINAL da lista
 * @param lista Ponteiro para a lista
 * @param dado Ponteiro para os dados a serem inseridos
 * @return 1 se sucesso, 0 se erro
 * @autor [andrericardo]
 */
int inserirFinal(Lista* lista, void* dado);

/**
 * @brief Remove um elemento da lista usando uma função de comparação
 * @param lista Ponteiro para a lista
 * @param chave Ponteiro para a chave de busca
 * @param comparar Função que compara um elemento com a chave
 * @return Ponteiro para os dados removidos ou NULL se não encontrado
 * @autor [andrericardo]
 */
void* removerElemento(Lista* lista, void* chave, int (*comparar)(void*, void*));

/**
 * @brief Busca um elemento na lista
 * @param lista Ponteiro para a lista
 * @param chave Ponteiro para a chave de busca
 * @param comparar Função que compara um elemento com a chave
 * @return Ponteiro para os dados encontrados ou NULL se não encontrado
 * @autor [andrericardo]
 */
void* buscarElemento(Lista* lista, void* chave, int (*comparar)(void*, void*));

/**
 * @brief Busca todos os elementos que atendem a um critério
 * @param lista Ponteiro para a lista
 * @param chave Ponteiro para a chave de busca
 * @param comparar Função que compara um elemento com a chave
 * @return Nova lista com os elementos encontrados ou NULL se erro
 * @autor [andrericardo]
 */
Lista* buscarTodosElementos(Lista* lista, void* chave, int (*comparar)(void*, void*));

/**
 * @brief Exibe todos os elementos da lista usando função de formatação
 * @param lista Ponteiro para a lista
 * @param formatar Função que formata um elemento para exibição
 * @autor [andrericardo]
 */
void exibirLista(Lista* lista, void (*formatar)(void*));

/**
 * @brief Libera toda a memória alocada para a lista
 * @param lista Ponteiro para a lista a ser destruída
 * @param liberarDados Função para liberar a memória dos dados (NULL se não quiser liberar)
 * @autor [andrericardo]
 */
void destruirLista(Lista* lista, void (*liberarDados)(void*));

/**
 * @brief Retorna a quantidade de elementos na lista
 * @param lista Ponteiro para a lista
 * @return Número de elementos ou -1 se lista inválida
 * @autor [andrericardo]
 */
int tamanhoLista(Lista* lista);

/**
 * @brief Percorre a lista aplicando uma função em cada elemento
 * @param lista Ponteiro para a lista
 * @param funcao Função a ser aplicada em cada elemento
 * @autor [andrericardo]
 */
void percorrerLista(Lista* lista, void (*funcao)(void*));

#endif