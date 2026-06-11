#include "sistema.h"


void menu_cadastro_contas(ListaContas *L) {
    int op;
    do {
        tela("MENU DE CONTAS BANCARIAS");
        
        gotoxy(25, 8);  printf("1 - Cadastrar Contas Bancarias no Final");
        gotoxy(25, 9);  printf("2 - Cadastrar Contas Bancarias no Inicio");
        gotoxy(25, 10); printf("3 - Cadastrar Contas Bancarias na Posicao");
        gotoxy(25, 11); printf("4 - Remover Contas Bancarias no Final");
        gotoxy(25, 12); printf("5 - Remover Contas Bancarias no Inicio");
        gotoxy(25, 13); printf("6 - Remover Contas Bancarias na Posicao");
        gotoxy(25, 14); printf("7 - Alteracao do Contas Bancarias");
        gotoxy(25, 15); printf("8 - Consultar Contas Bancarias");
        gotoxy(25, 16); printf("9 - Retornar ao Menu Anterior");
        
        gotoxy(8, 23); printf("Digite sua Opcao: ");
        scanf("%d", &op); limpar_buffer();

        switch(op) {
            case 1: inserir_conta_final(L); break;
            case 2: inserir_conta_inicio(L); break;
            case 3: inserir_conta_posicao(L); break;
            case 4: excluir_conta_final(L); break;
            case 5: excluir_conta_inicio(L); break;
            case 6: excluir_conta_posicao(L); break;
            case 7: alterar_conta(L); break;
            case 8: consultar_contas(L); break;
            case 9: break;
            default: exibir_msg("Opcao invalida!", 0); break;
        }
    } while(op != 9);
}
