#include <stdio.h>
#include "menu.h"

TipoServico menu_servico(void) {
    int op;

    do {
        printf("1 - Realizacao de Exames/Coleta\n");
        printf("2 - Entrega de Amostras\n");
        printf("3 - Retirada de Resultados/Orcamentos\n");
        scanf("%d", &op);

        if (op < 1 || op > 3) {
            printf("Opcao selecionada invalida! Tente novamente.\n");
        }

    } while (op < 1 || op > 3);

    return (TipoServico)op;
}

OpcaoPrincipal menu_principal(void) {
    int op;

    do {
        printf("\n=== SISTEMA DE SENHAS ===\n");
        printf("1 - Retirar senha\n");
        printf("2 - Chamar proxima senha\n");
        printf("0 - Sair\n");
        scanf("%d", &op);

        if (op < 0 || op > 2) {
            printf("Opcao selecionada invalida! Tente novamente.\n");
        }

    } while (op < 0 || op > 2);

    return (OpcaoPrincipal)op;
}