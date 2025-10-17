#include "lista.h"

Lista* criarLista() {
    Lista* nova = (Lista*)malloc(sizeof(Lista));
    if (nova == NULL) {
        printf("Erro: Não foi possível alocar memória para a lista.\n");
        return NULL;
    }
    
    nova->inicio = NULL;
    nova->fim = NULL;
    nova->quantidade = 0;
    
    return nova;
}

/**
 Verifica se a lista está vazia
 */
int listaVazia(Lista* lista) {
    if (lista == NULL) {
        printf("Erro: Lista inválida.\n");
        return -1;
    }
    return (lista->inicio == NULL);
}

/**
Insere um elemento no FINAL da lista
 
 */
int inserirFinal(Lista* lista, void* dado) {
    if (lista == NULL) {
        printf("Erro: Lista inválida.\n");
        return 0;
    }
    
    if (dado == NULL) {
        printf("Erro: Dados inválidos.\n");
        return 0;
    }
    
    // Cria novo nó
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: Não foi possível alocar memória para o nó.\n");
        return 0;
    }
    
    // Configura o novo nó
    novo->dado = dado;
    novo->proximo = NULL;
    
    // Insere na lista
    if (lista->inicio == NULL) {
        // Lista vazia - primeiro elemento
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        // Lista não vazia - insere no final
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    
    lista->quantidade++;
    return 1;
}

/**
  Remove um elemento da lista usando função de comparação
 
 */
void* removerElemento(Lista* lista, void* chave, int (*comparar)(void*, void*)) {
    if (lista == NULL || lista->inicio == NULL || comparar == NULL) {
        return NULL;
    }
    
    No* atual = lista->inicio;
    No* anterior = NULL;
    void* dadosRemovidos = NULL;
    
    // Percorre a lista procurando o elemento
    while (atual != NULL) {
        if (comparar(atual->dado, chave)) {
            // Encontrou - remove o nó
            if (anterior == NULL) {
                // Remove do início
                lista->inicio = atual->proximo;
                if (lista->fim == atual) {
                    lista->fim = NULL; // Era o único elemento
                }
            } else {
                // Remove do meio/fim
                anterior->proximo = atual->proximo;
                if (lista->fim == atual) {
                    lista->fim = anterior; // Atualiza o fim se necessário
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
    
    return NULL; // Não encontrou
}

/**
 Busca um elemento na lista
 
 */
void* buscarElemento(Lista* lista, void* chave, int (*comparar)(void*, void*)) {
    if (lista == NULL || comparar == NULL) {
        return NULL;
    }
    
    No* atual = lista->inicio;
    
    while (atual != NULL) {
        if (comparar(atual->dado, chave)) {
            return atual->dado; // Encontrou
        }
        atual = atual->proximo;
    }
    
    return NULL; // Não encontrou
}

/**
 Busca todos os elementos que atendem a um critério

 */
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
            // INSERE uma CÓPIA dos dados? Ou o ponteiro original?
            // Aqui estamos inserindo o ponteiro original (cuidado com destruição!)
            if (!inserirFinal(resultado, atual->dado)) {
                destruirLista(resultado, NULL); // Libera a lista, mas não os dados
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

/**
 Exibe todos os elementos da lista
 
 */
void exibirLista(Lista* lista, void (*formatar)(void*)) {
    if (lista == NULL) {
        printf("Lista inválida.\n");
        return;
    }
    
    if (lista->inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    
    if (formatar == NULL) {
        printf("Erro: Função de formatação não fornecida.\n");
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

/**
 Libera toda a memória alocada para a lista

 */
void destruirLista(Lista* lista, void (*liberarDados)(void*)) {
    if (lista == NULL) {
        return;
    }
    
    No* atual = lista->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        
        // Libera os dados se uma função for fornecida
        if (liberarDados != NULL && temp->dado != NULL) {
            liberarDados(temp->dado);
        }
        
        free(temp);
    }
    
    free(lista);
}

/**
Retorna a quantidade de elementos na lista

 */
int tamanhoLista(Lista* lista) {
    if (lista == NULL) {
        return -1;
    }
    return lista->quantidade;
}

/**
 Percorre a lista aplicando uma função em cada elemento
 
 */
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
