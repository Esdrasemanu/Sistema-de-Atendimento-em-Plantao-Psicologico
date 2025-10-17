#ifndef VALIDADATAHORA_H
#define VALIDADATAHORA_H

#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @brief Valida se uma data está no formato correto
 * @param data String no formato DD/MM/AAAA
 * @return 1 se válida, 0 se inválida
 */
int validarData(const char* data);

/**
 * @brief Valida se uma hora está no formato correto
 * @param hora String no formato HH:MM
 * @return 1 se válida, 0 se inválida
 */
int validarHora(const char* hora);

/**
 * @brief Valida se uma data é válida e não é passada
 * @param data String no formato DD/MM/AAAA
 * @return 1 se válida e futura, 0 se inválida ou passada
 */
int validarDataFutura(const char* data);

/**
 * @brief Valida se o horário está nos intervalos permitidos (15 em 15 min)
 * @param hora String no formato HH:MM
 * @return 1 se válida, 0 se inválida
 */
int validarHoraIntervalo(const char* hora);

/**
 * @brief Verifica se uma data/hora já passou
 * @param data String da data
 * @param hora String da hora
 * @return 1 se é futura, 0 se já passou
 */
int ehDataHoraFutura(const char* data, const char* hora);

#endif