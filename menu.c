#include <stdio.h>
#include "menu.h"

TipoAtendimento menu_tipo(void) {
    char op;

    do {
        printf("1 - Atendimento Normal\n");
        printf("2 - Atendimento Preferencial\n");
        scanf(" %c", &op);

        if (op != '1' && op != '2') {
            printf("Opcao selecionada invalida! Tente novamente.\n");
        } 
        
    }while(op !='1' && op !='2'); 

if (op == '1') {
    return TIPO_NORMAL;
}
return TIPO_PREFERENCIAL;
}   


TipoServico menu_servico(void) {
    int op;

    do {
        printf("1 - Realizacao de Exames/Coleta\n");
        printf("2 - Entrega de Amostras\n");
        printf("3 - Retirada de Resultados/Orrcamentos\n");
        scanf("%d", &op);
    
        if (op < 1 || op > 3) {
            printf("Opcao selecionada invalida! Tente novamente.\n");
        } 
        
    }while(op < 1 || op > 3);

    return (TipoServico) op;

} 
