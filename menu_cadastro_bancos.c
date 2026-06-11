#include "sistema.h"

void menu_cadastro_bancos(ListaBancos *L) {
    int op;
    do {
        tela();
        set_cor(11, 0); gotoxy(25, 6); printf("--- SUBMENU DE BANCOS ---"); set_cor(15, 0);
        gotoxy(24, 9);  printf("1 - Incluir Banco/Agencia");
        gotoxy(24, 11); printf("2 - Alterar Banco/Agencia");
        gotoxy(24, 13); printf("3 - Excluir Banco/Agencia");
        gotoxy(24, 15); printf("4 - Consultar Bancos/Agencias");
        gotoxy(24, 17); printf("5 - Voltar");
        gotoxy(7, 23); printf("Digite sua Opcao: ");
        scanf("%d", &op); limpar_buffer();

        switch(op) {
            case 1: inserir_banco(L); break;
            case 2: alterar_banco(L); break;
            case 3: excluir_banco(L); break;
            case 4: consultar_bancos(L); break;
            case 5: break;
            default: exibir_msg("Opcao invalida!", 0); break;
        }
    } while(op != 5);
}
