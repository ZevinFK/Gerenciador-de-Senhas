#include <stdio.h>
#include <ctype.h>
#include "paciente.h"

#define IDADE_URGENTE 80

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); {
    }
}

static int perguntar_sim_nao(const char *pergunta) {
    char resp;

    do {
        printf("%s (s/n): ", pergunta);
        scanf(" %c", &resp);
        limpar_buffer();
        resp = tolower(resp);
    
        if (resp != 's' && resp != 'n') {
            printf("Resposta invalida! Digite s ou n.\n");
        }
    } while (resp != 's' && resp != 'n');

    return resp == 's';

}

static char perguntar_genero(void) {

    char g;

    do {
        printf("Genero (m/f): ");
        scanf(" %c", &g);
        limpar_buffer();
        g = tolower(g);
    
        if (g != 'm' && g != 'f') {
            printf("Opcao invalida! Digite m ou f.\n");
        }
    } while (g != 'm' && g != 'f');

    return g;
}

static int perguntar_idade(void) {
    int idade;
    int lidos;

    do {
        printf("Idade: ");
        lidos = scanf("%d", &idade);
        limpar_buffer();

        if (lidos != 1 || idade < 0 || idade > 120) {
            printf("Idade invalida! Digite um numero entre 0 e 120.\n");
        }

    } while (lidos != 1 || idade < 0 || idade > 120);

    return idade;
}

Paciente paciente_registrar(void) {
    Paciente p;

    printf("\n=== REGISTRO DO PACIENTE ===\n");
    p.genero = perguntar_genero();
    p.idade = perguntar_idade();

    p.gestante = 0;
    p.lactante = 0;
    if (p.genero == 'f') {
        p.gestante = perguntar_sim_nao("Esta gestante?");
        p.lactante = perguntar_sim_nao("Esta lactante?");
    }

    p.necessidade_especial = perguntar_sim_nao("Possui necessidade especial?");
    p.obeso = perguntar_sim_nao("Possui condicao de obesidade?");

    return p;
}

TipoAtendimento paciente_classificar(const Paciente *p) {
    if (p->idade >= IDADE_URGENTE) {
        return TIPO_URGENTE;
    }

    if (p->gestante || p->lactante || p->necessidade_especial || p->obeso) {
        return TIPO_PREFERENCIAL;
    }

    return TIPO_NORMAL;
}