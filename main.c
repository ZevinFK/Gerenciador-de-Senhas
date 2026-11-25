#include <stdio.h>
#include "menu.h"
#include "paciente.h"
#include "senha.h"
#include "fila.h"
#include "painel.h"

static void retirar_senha(Fila filas[], int contadores[])
{
    Paciente paciente = paciente_registrar();
    TipoAtendimento tipo = paciente_classificar(&paciente);
    TipoServico servico = menu_servico();

    contadores[tipo]++;
    Senha *nova = senha_criar(paciente, tipo, servico, contadores[tipo]);

    if (nova == NULL)
    {
        printf("Erro: sem memoria!\n");
        return;
    }

    char hora[9];
    senha_formatar_horario(nova, hora, sizeof(hora));

    printf("\nSenha: %s\n", nova->codigo);
    printf("Servico: %s\n", senha_nome_servico(nova->servico));
    printf("Retirada as: %s\n", hora);

    fila_inserir(&filas[tipo], nova);
}

static void chamar_senha(Fila filas[], Painel *painel)
{
    Senha *chamada = fila_chamar_proxima(filas);

    if (chamada == NULL)
    {
        printf("\nNenhuma senha na fila!\n");
        return;
    }

    painel_exibir(painel);
    painel_aguardar(5);

    painel_anunciar(painel, chamada);
    painel_inserir(painel, chamada);
    painel_exibir(painel);
    painel_aguardar(5);

    // AQUI entra a avaliacao (proxima etapa)

    painel_limpar(painel);
    painel_exibir(painel);
    painel_aguardar(2);
}

int main(void)
{
    Fila filas[TIPO_URGENTE + 1];
    int contadores[TIPO_URGENTE + 1] = {0};
    Painel painel;
    OpcaoPrincipal opcao;

    for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++)
    {
        fila_iniciar(&filas[i]);
    }
    painel_iniciar(&painel);

    do
    {
        opcao = menu_principal();

        if (opcao == OPCAO_RETIRAR)
        {
            retirar_senha(filas, contadores);
        }
        else if (opcao == OPCAO_CHAMAR)
        {
            chamar_senha(filas, &painel);
        }

    } while (opcao != OPCAO_SAIR);

    for (int i = TIPO_NORMAL; i <= TIPO_URGENTE; i++)
    {
        fila_liberar(&filas[i]);
    }
    painel_limpar(&painel);

    return 0;
}