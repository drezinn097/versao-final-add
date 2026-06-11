#include "sistema.h"


ContaBancaria* ler_dados_conta(ListaContas *L) {
    ContaBancaria *novo = (ContaBancaria *) malloc(sizeof(ContaBancaria));
    ContaBancaria *resultado;
    
    do {
        tela("CADASTRO DE CONTA BANCARIA");
        gotoxy(24, 6);  printf("CODIGO CONTA........: ");
        gotoxy(24, 7);  printf("BANCO...............: ");
        gotoxy(24, 8);  printf("AGENCIA.............: ");
        gotoxy(24, 9);  printf("NUMERO DA CONTA.....: ");
        gotoxy(24, 10); printf("TIPO DA CONTA.......: ");
        gotoxy(24, 11); printf("SALDO INICIAL.......: ");
        gotoxy(24, 12); printf("LIMITE DA CONTA.....: ");
        gotoxy(24, 13); printf("STATUS (ATIVO/INATIVO): ");

        gotoxy(46, 6); scanf("%d", &novo->codigo_conta);
        limpar_buffer();
        resultado = pesquisa_conta(L, novo->codigo_conta);
        if (resultado != NULL) exibir_msg("ERRO: Este Codigo ja Existe!", 0);
    } while (resultado != NULL);

    gotoxy(46, 7);  ler_string(novo->banco, 50);
    gotoxy(46, 8);  ler_string(novo->agencia, 10);
    gotoxy(46, 9);  ler_string(novo->numero_conta, 20);
    gotoxy(46, 10); ler_string(novo->tipo_conta, 20);
    gotoxy(46, 11); scanf("%lf", &novo->vl_saldo);
    gotoxy(46, 12); scanf("%lf", &novo->vl_limite); limpar_buffer();
    gotoxy(46, 13); ler_string(novo->status, 10);
    strupr(novo->status); // Transforma em maiúsculo para garantir
    
    novo->prox = NULL;
    return novo;
}
