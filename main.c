// READ.ME deve ter: Funcionalidades, os procedimentos de compilacao e execucao, as funcoes implantadas e exemplos de utilizacao

#include <stdio.h>
#include "menu.h"

int main(void) {
    TipoAtendimento tipo = menu_tipo();
    printf("Tipo: %d\n", tipo);
    

    TipoServico tipoS = menu_servico();
    printf("Tipo: %d\n", tipoS);

    return 0;
}