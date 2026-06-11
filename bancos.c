#include "sistema.h"

Banco* pesquisa_banco(ListaBancos *L, int cod) {
    Banco *aux = L->Primeiro;
    while (aux != NULL) {
        if (aux->codigo_banco == cod) return aux;
        aux = aux->prox;
    }
    return NULL;
}

void tela_Banco() {
    set_cor(11, 0); // Ciano
    gotoxy(24, 4); printf("| CADASTRO DE BANCO/AGENCIA |");
    set_cor(15, 0); // Branco
    gotoxy(24, 6);  printf("CODIGO DO BANCO.....: ");
    gotoxy(24, 7);  printf("NOME DA INSTITUICAO.: ");
    gotoxy(24, 8);  printf("CNPJ................: ");
    gotoxy(24, 9);  printf("NUMERO DA AGENCIA...: ");
    gotoxy(24, 10); printf("ENDERECO............: ");
    gotoxy(24, 11); printf("NUMERO..............: ");
    gotoxy(24, 12); printf("BAIRRO..............: ");
    gotoxy(24, 13); printf("CIDADE..............: ");
    gotoxy(24, 14); printf("ESTADO (UF).........: ");
    gotoxy(24, 15); printf("TELEFONE CONTATO....: ");
}

// 1. INSERIR BANCO/AGENCIA (Sempre no final para simplificar o cadastro)
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

// 2. ALTERAR BANCO/AGENCIA
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

// 3. EXCLUIR BANCO/AGENCIA
void excluir_banco(ListaBancos *L) {
    int cod;
    tela(); gotoxy(24, 6); printf("Digite o Codigo para excluir: ");
    scanf("%d", &cod); limpar_buffer();

    Banco *atual = L->Primeiro, *anterior = NULL;
    while (atual != NULL && atual->codigo_banco != cod) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) { exibir_msg("Banco nao encontrado!", 0); return; }

    if (anterior == NULL) { // É o primeiro
        L->Primeiro = atual->prox;
        if (L->Primeiro == NULL) L->Ultimo = NULL;
    } else {
        anterior->prox = atual->prox;
        if (atual->prox == NULL) L->Ultimo = anterior;
    }
    free(atual);
    exibir_msg("Banco excluido com sucesso!", 1);
}

// 4. CONSULTAR BANCOS/AGENCIAS
void consultar_bancos(ListaBancos *L) {
    tela();
    Banco *aux = L->Primeiro;
    int linha = 6;
    if (aux == NULL) { exibir_msg("Nenhum banco cadastrado!", 0); return; }

    set_cor(11, 0); gotoxy(24, 4); printf("--- LISTA DE BANCOS ---"); set_cor(15, 0);
    while (aux != NULL && linha < 20) {
        gotoxy(5, linha++); printf("Cod: %d | Nome: %s | CNPJ: %s | Ag: %s | Cidade: %s-%s", 
            aux->codigo_banco, aux->nome_banco, aux->cnpj, aux->numero_agencia, aux->cidade, aux->uf);
        aux = aux->prox;
    }
    exibir_msg("Consulta finalizada!", 1);
}

// MENU BANCOS
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
