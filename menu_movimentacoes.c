#include "sistema.h"


void menu_movimentacoes(ListaContas *L, ListaMovimentacoes *M) {
    int op;
    do {
        tela("MENU DE MOVIMENTACOES BANCARIAS");
        
        gotoxy(25, 10); printf("1 - Movimentacao de Debito e Credito");
        gotoxy(25, 12); printf("2 - Transferencia entre Contas Bancarias");
        gotoxy(25, 14); printf("3 - Consulta Movimentacoes Bancarias");
        gotoxy(25, 16); printf("4 - Retornar ao Menu Anterior");
        
        gotoxy(8, 23); printf("Digite sua Opcao: ");
        scanf("%d", &op); limpar_buffer();

        switch(op) {
            case 1: debito_credito(L, M); break;
            case 2: transferencia(L, M); break;
            case 3: {
                int codigo;
                tela("CONSULTA DE MOVIMENTACOES");
                gotoxy(25, 10); printf("Codigo da Conta para Extrato: ");
                scanf("%d", &codigo); limpar_buffer();
                extrato_conta(M, codigo);
                break;
            }
            case 4: break;
            default: exibir_msg("Opcao invalida!", 0); break;
        }
    } while(op != 4);
}
