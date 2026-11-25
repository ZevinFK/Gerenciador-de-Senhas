#include <stdio.h>
#include <stdlib.h>
#include "senha.h"

Senha *senha_criar(Paciente paciente, TipoAtendimento tipo, TipoServico servico, int numero) {
    Senha *nova = (Senha *)malloc(sizeof(Senha));
    if (nova == NULL) {
        return NULL;
    }

    char prefixo;
    switch (tipo) {
        case TIPO_URGENTE:
            prefixo = 'U';
            break;
        case TIPO_PREFERENCIAL:
            prefixo = 'P';
            break;
        default:
            prefixo = 'N';
            break;
    }
    snprintf(nova->codigo, sizeof(nova->codigo), "%c%03d", prefixo, numero);

    nova->tipo = tipo;
    nova->servico = servico;
    nova->paciente = paciente;
    nova->horario = time(NULL);
    nova->proxima = NULL;

    return nova;
}

void senha_formatar_horario(const Senha *s, char *destino, size_t tamanho) {
    struct tm *info = localtime(&s->horario);
    strftime(destino, tamanho, "%H:%M:%S", info);
}

const char *senha_nome_servico(TipoServico servico) {
    switch (servico) {
        case SERVICO_EXAME:     return "Exames/Coleta";
        case SERVICO_AMOSTRA:   return "Entrega de Amostras";
        case SERVICO_RESULTADO: return "Resultados/Orcamentos";
    }
    return "Desconhecido";
}