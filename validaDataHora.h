#ifndef VALIDADATAHORA_H
#define VALIDADATAHORA_H

#include <stdio.h>
#include <string.h>
#include <time.h>

// Valida se a data está no formato correto "DD/MM/AAAA"
// Retorna 1 se estiver válida, 0 se estiver inválida
int validarData(const char* data);

// Valida se a hora está no formato correto "HH:MM"
// Retorna 1 se estiver válida, 0 se estiver inválida
int validarHora(const char* hora);

// Verifica se a data é válida e se está no futuro
// Ex: não pode ser uma data passada
// Retorna 1 se for válida e futura, 0 se inválida ou passada
int validarDataFutura(const char* data);

// Verifica se a hora está em intervalos de 15 minutos (ex: 13:00, 13:15, 13:30)
// Retorna 1 se estiver válida, 0 se estiver fora do intervalo
int validarHoraIntervalo(const char* hora);

// Verifica se a combinação data + hora é futura
// Retorna 1 se ainda não passou, 0 se já passou
int ehDataHoraFutura(const char* data, const char* hora);

#endif // VALIDADATAHORA_H
