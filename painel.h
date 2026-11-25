#ifndef PAINEL_H
#define PAINEL_H

#include "fila.h"

typedef struct {
    Fila colunas[TIPO_URGENTE + 1];
} Painel;

void painel_iniciar(Painel *p);
void painel_inserir(Painel *p, Senha *s);
void painel_exibir(const Painel *p);
void painel_anunciar(const Painel *p, const Senha *s);
void painel_aguardar(int segundos);
void painel_limpar(Painel *p);

#endif