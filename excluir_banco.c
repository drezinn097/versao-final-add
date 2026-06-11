#include "sistema.h"


void alterar_banco(ListaBancos *L) {
    int cod;
    tela(); gotoxy(24, 6); printf("Digite o Codigo do Banco para alterar: ");
    scanf("%d", &cod); limpar_buffer();
    
    Banco *banco = pesquisa_banco(L, cod);
    if (banco == NULL) { exibir_msg("Banco nao encontrado!", 0); return; }

    tela(); tela_Banco();
    gotoxy(46, 6); printf("%d (Nao alteravel)", banco->codigo_banco);
    gotoxy(46, 7);  ler_string(banco->nome_banco, 50);
    gotoxy(46, 8);  ler_string(banco->cnpj, 20);
    gotoxy(46, 9);  ler_string(banco->numero_agencia, 10);
    gotoxy(46, 10); ler_string(banco->endereco, 50);
    gotoxy(46, 11); ler_string(banco->numero, 10);
    gotoxy(46, 12); ler_string(banco->bairro, 30);
    gotoxy(46, 13); ler_string(banco->cidade, 30);
    gotoxy(46, 14); ler_string(banco->uf, 3);
    gotoxy(46, 15); ler_string(banco->telefone, 20);
    exibir_msg("Banco alterado com sucesso!", 1);
}
