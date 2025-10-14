#include "lista.h"

/*
 * Implementação de lista encadeada genérica.
 * Observações importantes:
 *  - A lista armazena ponteiros (void*). Gerenciamento de memória dos dados
 *    é responsabilidade do chamador, a não ser que ele passe uma função de
 *    liberação para destruirLista.
 */

Lista* criarLista() {
    Lista* nova = (Lista*)malloc(sizeof(Lista));
    if (nova == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para a lista.\n");
        return NULL;
    }
    
    nova->inicio = NULL;
    nova->fim = NULL;
    nova->quantidade = 0;
    
    return nova;
}

int listaVazia(Lista* lista) {
    if (lista == NULL) {
        printf("Erro: Lista invalida.\n");
        return -1;
    }
    return (lista->inicio == NULL);
}

int inserirFinal(Lista* lista, void* dado) {
    if (lista == NULL) {
        printf("Erro: Lista invalida.\n");
        return 0;
    }
    
    if (dado == NULL) {
        printf("Erro: Dados invalidos.\n");
        return 0;
    }
    
    /* Cria novo no */
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para o no.\n");
        return 0;
    }
    
    novo->dado = dado;
    novo->proximo = NULL;
    
    /* Insere na lista */
    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    
    lista->quantidade++;
    return 1;
}

void* removerElemento(Lista* lista, void* chave, int (*comparar)(void*, void*)) {
    if (lista == NULL || lista->inicio == NULL || comparar == NULL) {
        return NULL;
    }
    
    No* atual = lista->inicio;
    No* anterior = NULL;
    void* dadosRemovidos = NULL;
    
    /* Percorre a lista procurando o elemento */
    while (atual != NULL) {
        if (comparar(atual->dado, chave)) {
            /* Encontrou - remove o no */
            if (anterior == NULL) {
                lista->inicio = atual->proximo;
                if (lista->fim == atual) {
                    lista->fim = NULL; /* Era o unico elemento */
                }
            } else {
                anterior->proximo = atual->proximo;
                if (lista->fim == atual) {
                    lista->fim = anterior; /* Atualiza o fim se necessario */
                }
            }
            
            dadosRemovidos = atual->dado;
            free(atual);
            lista->quantidade--;
            return dadosRemovidos;
        }
        
        anterior = atual;
        atual = atual->proximo;
    }
    
    return NULL; /* Nao encontrou */
}

void* buscarElemento(Lista* lista, void* chave, int (*comparar)(void*, void*)) {
    if (lista == NULL || comparar == NULL) {
        return NULL;
    }
    
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        if (comparar(atual->dado, chave)) {
            return atual->dado; /* Encontrou */
        }
        atual = atual->proximo;
    }
    
    return NULL; /* Nao encontrou */
}

Lista* buscarTodosElementos(Lista* lista, void* chave, int (*comparar)(void*, void*)) {
    if (lista == NULL || comparar == NULL) {
        return NULL;
    }
    
    Lista* resultado = criarLista();
    if (resultado == NULL) {
        return NULL;
    }
    
    No* atual = lista->inicio;
    int encontrados = 0;
    
    while (atual != NULL) {
        if (comparar(atual->dado, chave)) {
            /* Insere o ponteiro original; cuidado com destrucao fora daqui */
            if (!inserirFinal(resultado, atual->dado)) {
                destruirLista(resultado, NULL); /* Libera a lista, mas nao os dados */
                return NULL;
            }
            encontrados++;
        }
        atual = atual->proximo;
    }
    
    if (encontrados == 0) {
        free(resultado);
        return NULL;
    }
    
    return resultado;
}

void exibirLista(Lista* lista, void (*formatar)(void*)) {
    if (lista == NULL) {
        printf("Lista invalida.\n");
        return;
    }
    
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    
    if (formatar == NULL) {
        printf("Erro: Funcao de formatacao nao fornecida.\n");
        return;
    }
    
    No* atual = lista->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("%d. ", posicao++);
        formatar(atual->dado);
        printf("\n");
        atual = atual->proximo;
    }
}

void destruirLista(Lista* lista, void (*liberarDados)(void*)) {
    if (lista == NULL) {
        return;
    }
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        
        /* Libera os dados se uma funcao for fornecida */
        if (liberarDados != NULL && temp->dado != NULL) {
            liberarDados(temp->dado);
        }
        
        free(temp);
    }
    
    free(lista);
}

int tamanhoLista(Lista* lista) {
    if (lista == NULL) {
        return -1;
    }
    return lista->quantidade;
}

void percorrerLista(Lista* lista, void (*funcao)(void*)) {
    if (lista == NULL || funcao == NULL) {
        return;
    }
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        funcao(atual->dado);
        atual = atual->proximo;
    }
}