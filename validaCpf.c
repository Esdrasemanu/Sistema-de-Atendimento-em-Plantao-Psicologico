#include <string.h>
#include <ctype.h>
#include "validaCpf.h"

// aqui vai retornar 1 caso o cpf seja válido e 0 se não for
int validarCPF(const char* cpf) {
    int i, j, soma, digito1, digito2;
    char num[12];
    int tam = 0;
    if (!cpf) return 0;
    // Aqui irá tirar os caracteres que não sejam númericos
    for (i = 0, j = 0; cpf[i] != '\0'; i++) {
        if (isdigit((unsigned char)cpf[i])) {
            num[j++] = cpf[i];
        }
    }
    num[j] = '\0';
    tam = strlen(num);
    if (tam != 11) return 0;
    // Aqui vai ver se todos os digitos são iguais
    for (i = 1; i < 11; i++) {
        if (num[i] != num[0]) break;
    }
    if (i == 11) return 0;
    // Primeiro digito verificador
    soma = 0;
    for (i = 0; i < 9; i++) soma += (num[i] - '0') * (10 - i);
    digito1 = 11 - (soma % 11);
    if (digito1 >= 10) digito1 = 0;
    if (digito1 != (num[9] - '0')) return 0;
    // Segundo dígito verificador
    soma = 0;
    for (i = 0; i < 10; i++) soma += (num[i] - '0') * (11 - i);
    digito2 = 11 - (soma % 11);
    if (digito2 >= 10) digito2 = 0;
    if (digito2 != (num[10] - '0')) return 0;
    return 1;
}