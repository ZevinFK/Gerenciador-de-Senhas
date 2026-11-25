#ifndef PACIENTE_H
#define PACIENTE_H

#include "menu.h"

typedef struct {
    char genero;
    int idade;
    int gestante;
    int lactante;
    int necessidade_especial;
    int obeso;
} Paciente;

Paciente paciente_registrar(void);
TipoAtendimento paciente_classificar(const Paciente *p);

#endif