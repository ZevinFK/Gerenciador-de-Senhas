#include <stdlib.h>
#include "fila.h"

void fila_iniciar(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int fila_vazia(const Fila *f) {
    return f->inicio == NULL;
}

void fila_inserir(Fila *f, Senha *s) {
    s->proxima = NULL;

    if (fila_vazia(f)){
        f->inicio = s;
    } else {
        f->fim->proxima = s;
    }

    f->fim = s;
    f->tamanho++;

}

Senha *fila_remover(Fila *f) {
    if (fila_vazia(f)) {
        return NULL;
    }
    
    Senha *removida = f->inicio;
    f->inicio = removida->proxima;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    removida->proxima = NULL;
    f->tamanho--;
    return removida;

}

void fila_liberar(Fila *f) {
    Senha *atual;
    while ((atual = fila_remover(f)) != NULL) {
        free(atual);
    }
}

Senha *fila_chamar_proxima(Fila filas[]) {
    for (int tipo = TIPO_URGENTE; tipo >= TIPO_NORMAL; tipo--) {
        if (!fila_vazia(&filas[tipo])) {
            return fila_remover(&filas[tipo]);
        }
    }

    return NULL;
}