#include "sistema.h"


void inserir_banco(ListaBancos *L) {
    Banco *novo = (Banco *) malloc(sizeof(Banco));
    Banco *resultado;
    
    do {
        tela(); tela_Banco();
        gotoxy(46, 6); scanf("%d", &novo->codigo_banco);
        limpar_buffer();
        resultado = pesquisa_banco(L, novo->codigo_banco);
        if (resultado != NULL) exibir_msg("ERRO: Este Codigo ja Existe!", 0);
    } while (resultado != NULL);

    gotoxy(46, 7);  ler_string(novo->nome_banco, 50);
    gotoxy(46, 8);  ler_string(novo->cnpj, 20);
    gotoxy(46, 9);  ler_string(novo->numero_agencia, 10);
    gotoxy(46, 10); ler_string(novo->endereco, 50);
    gotoxy(46, 11); ler_string(novo->numero, 10);
    gotoxy(46, 12); ler_string(novo->bairro, 30);
    gotoxy(46, 13); ler_string(novo->cidade, 30);
    gotoxy(46, 14); ler_string(novo->uf, 3);
    gotoxy(46, 15); ler_string(novo->telefone, 20);
    novo->prox = NULL;

    if (L->Primeiro == NULL) {
        L->Primeiro = novo;
    } else {
        L->Ultimo->prox = novo;
    }
    L->Ultimo = novo;
    exibir_msg("Banco/Agencia cadastrado com sucesso!", 1);
}
