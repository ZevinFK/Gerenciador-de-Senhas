#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "painel.h"

#define LARGURA_COLUNA 14

static void desenhar(const Painel *p, const char *chamada) {
    const char *titulos[] = {"", "NORMAL", "PREFERENCIAL", "URGENTE"};
    const Senha *atual[TIPO_URGENTE + 1];
    int maior = 0;

    system("cls");

    printf("==========================================\n");
    printf("            PAINEL DE SENHAS\n");
    printf("==========================================\n");

    if (chamada != NULL) {
        printf("\n      >>> CHAMANDO: %s <<<\n\n", chamada);
    } else {
        printf("\n\n\n");
    }

    for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++) {
        printf("%-*s", LARGURA_COLUNA, titulos[i]);
    }
    printf("\n");

    for (int k = 0; k < LARGURA_COLUNA * 3; k++) {
        putchar('-');
    }
    printf("\n");

    for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++) {
        atual[i] = p->colunas[i].inicio;
        if (p->colunas[i].tamanho > maior) {
            maior = p->colunas[i].tamanho;
        }
    }

    if (maior == 0) {
        printf("  (nenhuma senha no painel)\n");
    }

    for (int linha = 0; linha < maior; linha++) {
        for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++) {
            if (atual[i] != NULL) {
                printf("%-*s", LARGURA_COLUNA, atual[i]->codigo);
                atual[i] = atual[i]->proxima;
            } else {
                printf("%-*s", LARGURA_COLUNA, "");
            }
        }
        printf("\n");
    }
}

void painel_iniciar(Painel *p) {
    for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++) {
        fila_iniciar(&p->colunas[i]);
    }
}

void painel_inserir(Painel *p, Senha *s) {
    fila_inserir(&p->colunas[s->tipo], s);
}

void painel_exibir(const Painel *p) {
    desenhar(p, NULL);
}

void painel_anunciar(const Painel *p, const Senha *s) {
    for (int i = 0; i < 3; i++) {
        desenhar(p, s->codigo);
        Sleep(500);
        desenhar(p, NULL);
        Sleep(500);
    }
}

void painel_aguardar(int segundos) {
    Sleep(segundos * 1000);
}

void painel_limpar(Painel *p) {
    for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++) {
        fila_liberar(&p->colunas[i]);
    }
}