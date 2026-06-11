#include "sistema.h"

// ====================================================================
// FUNCOES AUXILIARES DE CONTAS
// ====================================================================

ContaBancaria* pesquisa_conta(ListaContas *L, int cod) {
    ContaBancaria *aux = L->Primeiro;
    while (aux != NULL) {
        if (aux->codigo_conta == cod) return aux;
        aux = aux->prox;
    }
    return NULL;
}

// Essa funcao limpa a tela de cadastro e lê os dados (usada nas inserções)
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

// ====================================================================
// 1, 2 e 3: INSERCOES (MANIPULACAO DE PONTEIROS)
// ====================================================================

// 1 - INSERIR NO FINAL
void inserir_conta_final(ListaContas *L) {
    ContaBancaria *novo = ler_dados_conta(L);
    
    if (L->Primeiro == NULL) { // Lista vazia
        L->Primeiro = novo;
    } else { // Já tem gente, coloca no final
        L->Ultimo->prox = novo;
    }
    L->Ultimo = novo;
    exibir_msg("Conta cadastrada no FINAL com sucesso!", 1);
}

// 2 - INSERIR NO INICIO
void inserir_conta_inicio(ListaContas *L) {
    ContaBancaria *novo = ler_dados_conta(L);
    
    novo->prox = L->Primeiro; // O novo aponta para o antigo primeiro
    L->Primeiro = novo;       // O primeiro passa a ser o novo
    
    if (L->Ultimo == NULL) {  // Se a lista estava vazia, ele também é o último
        L->Ultimo = novo;
    }
    exibir_msg("Conta cadastrada no INICIO com sucesso!", 1);
}

// 3 - INSERIR NA POSICAO ESPECIFICA
void inserir_conta_posicao(ListaContas *L) {
    int pos, cont = 1;
    tela("INSERIR CONTA NA POSICAO"); 
    gotoxy(24, 8); printf("Digite a Posicao desejada (1, 2, 3...): ");
    scanf("%d", &pos); limpar_buffer();

    // Se a posição for 1 ou lista vazia, cai na regra de inserir no início
    if (pos <= 1 || L->Primeiro == NULL) {
        inserir_conta_inicio(L);
        return;
    }

    ContaBancaria *novo = ler_dados_conta(L);
    ContaBancaria *aux = L->Primeiro;
    
    // Navega até a posição anterior à desejada
    while (aux->prox != NULL && cont < pos - 1) {
        aux = aux->prox;
        cont++;
    }
    
    novo->prox = aux->prox; // O novo aponta pra onde o aux apontava
    aux->prox = novo;       // O aux aponta pro novo
    
    // Se inseriu na última posição, atualiza o ponteiro Ultimo
    if (novo->prox == NULL) {
        L->Ultimo = novo;
    }
    exibir_msg("Conta cadastrada na POSICAO especifica com sucesso!", 1);
}

// ====================================================================
// 4, 5 e 6: REMOCOES (FREE E MANIPULACAO DE PONTEIROS)
// ====================================================================

// 4 - REMOVER NO FINAL
void excluir_conta_final(ListaContas *L) {
    if (L->Primeiro == NULL) { exibir_msg("A lista de contas ja esta vazia!", 0); return; }
    
    ContaBancaria *atual = L->Primeiro;
    ContaBancaria *anterior = NULL;
    
    // Percorre até achar o último
    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (anterior == NULL) { 
        // Só tinha uma conta na lista
        L->Primeiro = NULL; 
        L->Ultimo = NULL;
    } else {
        anterior->prox = NULL; 
        L->Ultimo = anterior;
    }
    
    free(atual); // Libera a memória!
    exibir_msg("Conta do FINAL removida com sucesso!", 1);
}

// 5 - REMOVER NO INICIO
void excluir_conta_inicio(ListaContas *L) {
    if (L->Primeiro == NULL) { exibir_msg("A lista de contas ja esta vazia!", 0); return; }
    
    ContaBancaria *aux = L->Primeiro;
    
    L->Primeiro = L->Primeiro->prox; // O primeiro pula pro segundo
    
    if (L->Primeiro == NULL) { // Se a lista ficou vazia
        L->Ultimo = NULL;
    }
    
    free(aux);
    exibir_msg("Conta do INICIO removida com sucesso!", 1);
}

// 6 - REMOVER NA POSICAO ESPECIFICA
void excluir_conta_posicao(ListaContas *L) {
    if (L->Primeiro == NULL) { exibir_msg("A lista de contas ja esta vazia!", 0); return; }
    
    int pos, cont = 1;
    tela("REMOVER CONTA NA POSICAO"); 
    gotoxy(24, 8); printf("Digite a Posicao para remover (1, 2, 3...): ");
    scanf("%d", &pos); limpar_buffer();

    if (pos <= 1) {
        excluir_conta_inicio(L);
        return;
    }

    ContaBancaria *atual = L->Primeiro;
    ContaBancaria *anterior = NULL;
    
    while (atual != NULL && cont < pos) {
        anterior = atual;
        atual = atual->prox;
        cont++;
    }

    if (atual == NULL) { 
        exibir_msg("Posicao invalida (maior que o tamanho da lista)!", 0); 
        return; 
    }

    anterior->prox = atual->prox; // O de trás pula o que vai ser excluido
    
    if (atual->prox == NULL) { // Se excluiu o último
        L->Ultimo = anterior;
    }
    
    free(atual);
    exibir_msg("Conta da POSICAO removida com sucesso!", 1);
}

// ====================================================================
// 7 e 8: ALTERACAO E CONSULTA
// ====================================================================

// 7 - ALTERAR CONTA
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

// 8 - CONSULTAR CONTAS
void consultar_contas(ListaContas *L) {
    tela("LISTA DE CONTAS BANCARIAS");
    ContaBancaria *aux = L->Primeiro;
    int linha = 6;
    
    if (aux == NULL) { exibir_msg("Nenhuma conta cadastrada!", 0); return; }

    while (aux != NULL) {
        if(linha >= 22) { // Paginação se tiver muitas contas
            exibir_msg("Pressione qualquer tecla para continuar...", 1);
            tela("LISTA DE CONTAS BANCARIAS (CONTINUACAO)");
            linha = 6;
        }
        
        gotoxy(5, linha++); printf("Cod: %d | Bco: %s | Ag: %s | Cta: %s | Saldo: R$%.2lf | %s", 
            aux->codigo_conta, aux->banco, aux->agencia, aux->numero_conta, aux->vl_saldo, aux->status);
        
        aux = aux->prox;
    }
    exibir_msg("Consulta finalizada!", 1);
}

// ====================================================================
// MENU PRINCIPAL DE CONTAS
// ====================================================================

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
