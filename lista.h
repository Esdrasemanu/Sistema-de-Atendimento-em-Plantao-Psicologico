#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Módulo: lista (genérico)
 * Descrição: lista encadeada simples que armazena ponteiros genéricos (void*).
 * Uso típico: armazenar ponteiros para estruturas (ex: Estudante) sem assumir
 * propriedade dos dados, a menos que o chamador decida entregar essa
 * responsabilidade à lista (via função liberarDados em destruirLista).
 *
 * Principais cuidados:
 *  - Se os dados inseridos foram alocados dinamicamente, providencie uma
 *    função liberarDados para destruir esses dados quando destruir a lista.
 *  - As funções de busca usam uma função comparar fornecida pelo chamador.
 */

typedef struct no {
    void* dado;           // Ponteiro genérico para os dados
    struct no* proximo;   // Ponteiro para o próximo nó
} No;

typedef struct {
    No* inicio;          // Primeiro elemento da lista
    No* fim;             // Último elemento da lista
    int quantidade;      // Número de elementos na lista
} Lista;

/* API pública */
Lista* criarLista();
int listaVazia(Lista* lista);
int inserirFinal(Lista* lista, void* dado);
void* removerElemento(Lista* lista, void* chave, int (*comparar)(void*, void*));
void* buscarElemento(Lista* lista, void* chave, int (*comparar)(void*, void*));
Lista* buscarTodosElementos(Lista* lista, void* chave, int (*comparar)(void*, void*));
void exibirLista(Lista* lista, void (*formatar)(void*));
void destruirLista(Lista* lista, void (*liberarDados)(void*));
int tamanhoLista(Lista* lista);
void percorrerLista(Lista* lista, void (*funcao)(void*));

#endif