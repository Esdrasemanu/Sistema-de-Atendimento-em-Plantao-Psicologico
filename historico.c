// Implementação do histórico de atendimentos
#include "historico.h"

/*
 * criaHistorico
 * - Aloca e inicializa a estrutura Historico.
 * - Retorna NULL em caso de falha de alocação.
 */
Historico* criaHistorico(void) {
	Historico* h = (Historico*) malloc(sizeof(Historico));
	if (!h) return NULL;
	h->cabeca = NULL;
	return h;
}

/*
 * encontraCurso
 * - Função interna que procura um curso pelo nome.
 * - Retorna ponteiro para Curso se encontrado, ou NULL caso contrário.
 */
static Curso* encontraCurso(Historico* h, const char* nome) {
	Curso* cur = h->cabeca;
	while (cur) {
		if (strcmp(cur->nome, nome) == 0) return cur;
		cur = cur->prox;
	}
	return NULL;
}

/*
 * criaCurso
 * - Função interna que cria um novo nó Curso e o insere no início da lista.
 * - Retorna ponteiro para o novo Curso, ou NULL se malloc falhar.
 */
static Curso* criaCurso(Historico* h, const char* nome) {
	Curso* c = (Curso*) malloc(sizeof(Curso));
	if (!c) return NULL;
	strncpy(c->nome, nome, sizeof(c->nome)-1);
	c->nome[sizeof(c->nome)-1] = '\0';
	c->lista = NULL;
	c->prox = h->cabeca;
	h->cabeca = c;
	return c;
}

/*
 * insereAtendimento
 * - Insere um novo Atendimento no final da lista do curso especificado.
 * - Se o curso não existir, é criado.
 * - Não há retorno; a função simplesmente retorna em caso de erro.
 */
void insereAtendimento(Historico* h, const char* curso, const char* cpf, const char* data, const char* psicologo, const char* resumo) {
	if (!h || !curso || !cpf) return;

	Curso* c = encontraCurso(h, curso);
	if (!c) c = criaCurso(h, curso);
	if (!c) return;

	Atendimento* a = (Atendimento*) malloc(sizeof(Atendimento));
	if (!a) return;
	strncpy(a->cpf, cpf, sizeof(a->cpf)-1); a->cpf[sizeof(a->cpf)-1] = '\0';
	strncpy(a->data, data, sizeof(a->data)-1); a->data[sizeof(a->data)-1] = '\0';
	strncpy(a->psicologo, psicologo, sizeof(a->psicologo)-1); a->psicologo[sizeof(a->psicologo)-1] = '\0';
	strncpy(a->resumo, resumo, sizeof(a->resumo)-1); a->resumo[sizeof(a->resumo)-1] = '\0';
	a->prox = NULL;

	/* insere no final da lista de atendimentos do curso */
	if (!c->lista) {
		c->lista = a;
	} else {
		Atendimento* it = c->lista;
		while (it->prox) it = it->prox;
		it->prox = a;
	}
}

/*
 * consultaPorCPF
 * - Percorre todos os cursos e imprime atendimentos cujo cpf bata com o parâmetro.
 * - Imprime mensagem caso nenhum atendimento seja encontrado.
 */
void consultaPorCPF(const Historico* h, const char* cpf) {
	if (!h || !cpf) return;
	Curso* c = h->cabeca;
	int found = 0;
	while (c) {
		Atendimento* a = c->lista;
		while (a) {
			if (strcmp(a->cpf, cpf) == 0) {
				if (!found) printf("\nHistorico para CPF %s:\n", cpf);
				printf("Curso: %s | Data: %s | Psicologo: %s\nResumo: %s\n\n", c->nome, a->data, a->psicologo, a->resumo);
				found = 1;
			}
			a = a->prox;
		}
		c = c->prox;
	}
	if (!found) printf("Nenhum atendimento encontrado para CPF %s.\n", cpf);
}

/*
 * imprimeRelatorio
 * - Percorre cursos e imprime todos os atendimentos agrupados por curso.
 */
void imprimeRelatorio(const Historico* h) {
	if (!h) return;
	Curso* c = h->cabeca;
	if (!c) {
		printf("Nenhum atendimento registrado.\n");
		return;
	}
	while (c) {
		printf("\n--- Curso: %s ---\n", c->nome);
		Atendimento* a = c->lista;
		if (!a) {
			printf("(nenhum atendimento)\n");
		} else {
			int i = 1;
			while (a) {
				printf("%d) CPF: %s | Data: %s | Psicologo: %s\nResumo: %s\n", i++, a->cpf, a->data, a->psicologo, a->resumo);
				a = a->prox;
			}
		}
		c = c->prox;
	}
}

/*
 * liberaHistorico
 * - Libera memória de atendimentos, cursos e do próprio Historico.
 */
void liberaHistorico(Historico* h) {
	if (!h) return;
	Curso* c = h->cabeca;
	while (c) {
		Atendimento* a = c->lista;
		while (a) {
			Atendimento* tmpA = a;
			a = a->prox;
			free(tmpA);
		}
		Curso* tmpC = c;
		c = c->prox;
		free(tmpC);
	}
	free(h);
}

