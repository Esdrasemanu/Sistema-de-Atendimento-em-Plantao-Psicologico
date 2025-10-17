#ifndef VALIDA_SALA_H
#define VALIDA_SALA_H

#include "lista.h"

#define SALAS_COUNT 9

int validarSala(const char* sala);
void imprimirSalas(void);
const char* getSalaNome(int idx);
int salaDisponivel(Lista* lista, const char* sala, const char* data, const char* hora);

#endif
