#ifndef SENHA_H
#define SENHA_H

#include <time.h>
#include "menu.h"
#include "paciente.h"

typedef struct Senha {
    char codigo[8];
    TipoAtendimento tipo;
    TipoServico servico;
    Paciente paciente;
    time_t horario;
    struct Senha *proxima;
} Senha;

Senha *senha_criar(
    Paciente paciente, 
    TipoAtendimento tipo,
    TipoServico servico,
    int numero);

    void senha_formatar_horario(
    const Senha *s, 
    char *destino, size_t tamanho);
    const char *senha_nome_servico(
        TipoServico servico);

#endif