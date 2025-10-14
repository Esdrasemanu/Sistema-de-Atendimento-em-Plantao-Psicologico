#include "fila.h"

/*
 * Cria uma fila vazia.
 * Retorna: ponteiro para Fila alocada, ou NULL se malloc falhar.
 * Observação: chamador assume propriedade da fila retornada e deve chamar
 * liberaFila quando terminar.
 */
Fila* criaFila(void) {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (!f) return NULL;
    f->inicio = f->fim = NULL;
    return f;
}

/*
 * Insere um Estudante no fim da fila.
 * Entradas: f (fila existente), e (estrutura Estudante por valor).
 * Retorno: 1 se sucesso, 0 se falha (ex: malloc).
 * Observação: copia a estrutura Estudante para dentro do nó; o chamador
 * pode manter sua própria cópia.
 */
int insereFila(Fila* f, Estudante e) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    if (!novo) return 0;
    novo->dado = e;
    novo->prox = NULL;
    if (f->fim)
        f->fim->prox = novo;
    else
        f->inicio = novo;
    f->fim = novo;
    return 1;
}

/*
 * Remove o primeiro elemento da fila.
 * Se houver elemento, copia os dados para *e e retorna 1.
 * Se a fila estiver vazia, retorna 0.
 */
int removeFila(Fila* f, Estudante* e) {
    if (!f->inicio) return 0;
    NoFila* temp = f->inicio;
    *e = temp->dado;
    f->inicio = temp->prox;
    if (!f->inicio) f->fim = NULL;
    free(temp);
    return 1;
}

/*
 * Cancela (remove) um elemento da fila por CPF, mesmo que não esteja na frente.
 * Retorna 1 se encontrou e removeu, 0 caso contrário.
 */
int cancelaFila(Fila* f, const char* cpf) {
    NoFila *atual = f->inicio, *ant = NULL;
    while (atual) {
        if (strcmp(atual->dado.cpf, cpf) == 0) {
            if (ant) ant->prox = atual->prox;
            else f->inicio = atual->prox;
            if (atual == f->fim) f->fim = ant;
            free(atual);
            return 1;
        }
        ant = atual;
        atual = atual->prox;
    }
    return 0;
}

/*
 * Imprime a fila no formato: Nome | CPF | Curso
 * Se a fila estiver vazia, imprime mensagem apropriada.
 */
void imprimeFila(const Fila* f) {
    NoFila* atual = f->inicio;
    if (!atual) {
        printf("(fila vazia)\n");
        return;
    }
    while (atual) {
        printf("Nome: %s | CPF: %s | Curso: %s\n",
               atual->dado.nome, atual->dado.cpf, atual->dado.curso);
        atual = atual->prox;
    }
}

/*
 * Libera toda a memória usada pela fila (nós e estrutura Fila).
 * Observação: como os Estudantes são copiados por valor, não há ponteiros
 * adicionais para liberar aqui.
 */
void liberaFila(Fila* f) {
    NoFila* atual = f->inicio;
    while (atual) {
        NoFila* tmp = atual;
        atual = atual->prox;
        free(tmp);
    }
    free(f);
}
