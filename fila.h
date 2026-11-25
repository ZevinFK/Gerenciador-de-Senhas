#ifndef FILA_H
#define FILA_H

#include "senha.h"

typedef struct {
    Senha *inicio;
    Senha *fim;
    int tamanho;
} Fila;

void fila_iniciar(Fila *f);
int fila_vazia(const Fila *f);
void fila_inserir(Fila *f, Senha *s);
Senha *fila_remover(Fila *f);
void fila_liberar(Fila *f);
Senha *fila_chamar_proxima(Fila filas[]);

#endif