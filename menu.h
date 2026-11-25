#ifndef MENU_H
#define MENU_H


typedef enum {
    TIPO_NORMAL = 1,
    TIPO_PREFERENCIAL,
    TIPO_URGENTE
} TipoAtendimento;

typedef enum {
    SERVICO_EXAME = 1,
    SERVICO_AMOSTRA,
    SERVICO_RESULTADO
} TipoServico;

TipoServico menu_servico(void);

typedef enum {
    OPCAO_SAIR = 0,
    OPCAO_RETIRAR,
    OPCAO_CHAMAR
} OpcaoPrincipal;

OpcaoPrincipal menu_principal(void);

#endif