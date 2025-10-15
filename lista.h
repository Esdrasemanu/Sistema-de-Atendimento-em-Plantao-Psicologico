#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    void* dado;
    struct no* proximo;
} No;

typedef struct {
    No* inicio;
    No* fim;
    int quantidade;
} Lista;

// API pública - CORRIGIDO: nomes consistentes
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