#include "sistema.h"


void alterar_conta(ListaContas *L) {
    int cod;
    tela("ALTERACAO DE CONTA BANCARIA"); 
    gotoxy(24, 6); printf("Digite o Codigo da Conta para alterar: ");
    scanf("%d", &cod); limpar_buffer();
    
    ContaBancaria *conta = pesquisa_conta(L, cod);

    if (conta == NULL) { exibir_msg("Conta nao encontrada!", 0); return; }

    tela("ALTERACAO DE CONTA BANCARIA");
    gotoxy(24, 6);  printf("CODIGO CONTA........: ");
    gotoxy(24, 7);  printf("BANCO...............: ");
    gotoxy(24, 8);  printf("AGENCIA.............: ");
    gotoxy(24, 9);  printf("NUMERO DA CONTA.....: ");
    gotoxy(24, 10); printf("TIPO DA CONTA.......: ");
    gotoxy(24, 11); printf("SALDO INICIAL.......: ");
    gotoxy(24, 12); printf("LIMITE DA CONTA.....: ");
    gotoxy(24, 13); printf("STATUS (ATIVO/INATIVO): ");

    gotoxy(46, 6); printf("%d (Nao alteravel)", conta->codigo_conta);
    gotoxy(46, 7); ler_string(conta->banco, 50);
    gotoxy(46, 8); ler_string(conta->agencia, 10);
    gotoxy(46, 9); ler_string(conta->numero_conta, 20);
    gotoxy(46, 10); ler_string(conta->tipo_conta, 20);
    gotoxy(46, 11); scanf("%lf", &conta->vl_saldo);
    gotoxy(46, 12); scanf("%lf", &conta->vl_limite); limpar_buffer();
    gotoxy(46, 13); ler_string(conta->status, 10); strupr(conta->status);
    
    exibir_msg("Conta alterada com sucesso!", 1);
}
