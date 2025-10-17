#ifndef VALIDASALA_H
#define VALIDASALA_H

#include "lista.h"
#include "agendamento.h"

#define SALAS_COUNT 9

// Funções para validação de salas
int validarSala(const char* sala);
void imprimirSalas(void);
const char* getSalaNome(int idx);
int salaDisponivel(Lista* lista, const char* sala, const char* data, const char* hora);

#endif