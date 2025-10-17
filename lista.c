#include "lista.h"

// Cria uma nova lista vazia - Esdras Emanuel 
Lista* criarLista() {
    Lista* nova = (Lista*)malloc(sizeof(Lista)); // Aloca memória para a lista
    if (nova == NULL) {
        printf("Erro: Não foi possível alocar memória para a lista.\n");
        return NULL;
    }

    // Inicializa os ponteiros e quantidade
    nova->inicio = NULL;
    nova->fim = NULL;
    nova->quantidade = 0;

    return nova;
}

// Verifica se a lista está vazia
int listaVazia(Lista* lista) {
    if (lista == NULL) {
        printf("Erro: Lista inválida.\n");
        return -1; // Lista nula
    }

    return (lista->inicio == NULL); // Retorna 1 se estiver vazia, 0 se não
}

// Insere um novo elemento no final da lista
int inserirFinal(Lista* lista, void* dado) {
    if (lista == NULL) {
        printf("Erro: Lista inválida.\n");
        return 0;
    }

    if (dado == NULL) {
        printf("Erro: Dados inválidos.\n");
        return 0;
    }

    // Cria um novo nó
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: Não foi possível alocar memória para o nó.\n");
        return 0;
    }

    novo->dado = dado;     // Armazena o dado no nó
    novo->proximo = NULL;  // Último nó aponta para NULL

    // Se a lista estiver vazia, o novo é o primeiro e último
    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        // Se não, adiciona no final
        lista->fim->proximo = novo;
        lista->fim = novo;
    }

    lista->quantidade++; // Atualiza a quantidade de elementos
    return 1; // Sucesso
}

// Remove um elemento da lista que combina com a chave fornecida
void* removerElemento(Lista* lista, void* chave, int (*comparar)(void*, void*)) {
    if (lista == NULL || lista->inicio == NULL || comparar == NULL) {
        return NULL; // Verifica se a lista está válida
    }

    No* atual = lista->inicio;
    No* anterior = NULL;
    void* dadosRemovidos = NULL;

    // Percorre a lista procurando o eleme
