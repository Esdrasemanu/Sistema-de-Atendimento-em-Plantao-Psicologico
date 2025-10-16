#include <string.h>
#include <stdio.h>
#include "validaDataHora.h"

int validarData(const char* data) {
    int d, m, a;
    if (!data || strlen(data) != 10) return 0;
    if (sscanf(data, "%2d/%2d/%4d", &d, &m, &a) != 3) return 0;
    if (d < 1 || d > 31 || m < 1 || m > 12 || a < 1900) return 0;
    // Meses normais (30 dias)
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return 0;
    // Validação de fevereiro e ano bissexto
    if (m == 2) {
        int bissexto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
        if (d > 29 || (d == 29 && !bissexto)) return 0;
    }
    return 1;
}


// Validação padrão de data e hora
int validarHora(const char* hora) {
    int h, m;
    if (!hora || strlen(hora) != 5) return 0;
    if (sscanf(hora, "%2d:%2d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23 || m < 0 || m > 59) return 0;
    return 1;
}