esse arquivo funciona? como modulo para ler int sem problemas? "#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

// readInt agora retorna int (0/-1) mas aceita parâmetro opcional para tipo de erro
int readInt(int *destino, int *tipo_erro) {
    if (!destino) {
        if (tipo_erro) *tipo_erro = 3; // erro vazio
        return -1;
    }
    
    char buffer[64];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        if (tipo_erro) *tipo_erro = 3;
        return -1;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\n') {
        if (tipo_erro) *tipo_erro = 1; // não é número
        return -1;
    }
    
    if ((val == LONG_MAX || val == LONG_MIN) && errno == ERANGE) {
        if (tipo_erro) *tipo_erro = 2; // overflow
        return -1;
    }
    
    if (val < INT_MIN || val > INT_MAX) {
        if (tipo_erro) *tipo_erro = 2; // overflow
        return -1;
    }
    
    *destino = (int)val;
    return 0;
}

int main() {
    int valor;
    int tipo_erro;
    
    printf("=== TESTE readInt NOVA IMPLEMENTACAO ===\n");
    printf("Digite um numero: ");
    
    int resultado = readInt(&valor, &tipo_erro);
    
    printf("\n=== RESULTADO ===\n");
    printf("Return: %d\n", resultado);
    printf("Tipo erro: %d\n", tipo_erro);
    
    if (resultado == 0) {
        printf("SUCESSO! Valor lido: %d\n", valor);
    } else {
        // Simulando como ficaria no seu código real
        if (tipo_erro == 2) {
            printf("ERRO: Overflow! Valor fora da faixa [%d a %d]\n", INT_MIN, INT_MAX);
        } else {
            printf("ERRO: Digite um numero inteiro!\n");
        }
    }
    
    printf("\nTeste com NULL (sem detalhes de erro): ");
    int resultado2 = readInt(&valor, NULL);
    printf("Return: %d\n", resultado2);
    
    printf("\nPressione Enter para sair...");
    getchar();
    return 0;
}"