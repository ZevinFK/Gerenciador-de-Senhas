#ifndef MENU_H
#define MENU_H


typedef enum {
    TIPO_NORMAL = 1,
    TIPO_PREFERENCIAL
} TipoAtendimento;

typedef enum {
    SERVICO_EXAME = 1,
    SERVICO_AMOSTRA,
    SERVICO_RESULTADO
} TipoServico;

TipoAtendimento menu_tipo(void);
TipoServico menu_servico(void);

#endif