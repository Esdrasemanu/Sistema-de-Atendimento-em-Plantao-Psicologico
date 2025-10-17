#ifndef VALIDADATAHORA_H
#define VALIDADATAHORA_H

#include <stdio.h>
#include <string.h>
#include <time.h>

/**
Valida se uma data está no formato correto
data String no formato DD/MM/AAAA
1 se válida, 0 se inválida
 */
int validarData(const char* data);

/**
 Valida se uma hora está no formato correto
 hora String no formato HH:MM
 return 1 se válida, 0 se inválida
 */
int validarHora(const char* hora);

/**
 Valida se uma data é válida e não é passada
 data String no formato DD/MM/AAAA
 1 se válida e futura, 0 se inválida ou passada
 */
int validarDataFutura(const char* data);

/**
 * Valida se o horário está nos intervalos permitidos (15 em 15 min)
 * hora String no formato HH:MM
 *  1 se válida, 0 se inválida
 */
int validarHoraIntervalo(const char* hora);

/**
 *  Verifica se uma data/hora já passou
 * data String da data
 *  hora String da hora
 * 1 se é futura, 0 se já passou
 */
int ehDataHoraFutura(const char* data, const char* hora);

#endif
