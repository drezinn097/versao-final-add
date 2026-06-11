#include "sistema.h"

// ====================================================================
// FUNCAO PRINCIPAL DA LISTA DUPLAMENTE ENCADEADA
// ====================================================================

void registrar_movimentacao(ListaMovimentacoes *M, int codigo, char tipo[], double valor, double saldo) {
    Movimentacao *novo = (Movimentacao*) malloc(sizeof(Movimentacao));
    if(novo == NULL) { exibir_msg("Erro de alocacao de memoria!", 0); return; }

    // Gera um número sequencial automático para a movimentação
    novo->sequencial = (M->Ultimo == NULL) ? 1 : M->Ultimo->sequencial + 1;

    // Preenche os dados
    novo->codigo_conta = codigo;
    strcpy(novo->tp_movimentacao, tipo);
    novo->vl_movimento = valor;
    novo->vl_saldo = saldo;

    // Pede a data da transação
    gotoxy(24, 20); printf("Data Movimento (dd/mm/aaaa): ");
    ler_string(novo->dt_movimento, 11);
    limpar_msg(); // Limpa a mensagem da data para não sujar a tela

    // MANIPULAÇÃO DA LISTA DUPLA (O SEGREDINHO DO SUCESSO)
    novo->prox = NULL; 
    
    if(M->Primeiro == NULL) {
        // Se a lista está vazia, ele é o primeiro. Logo, não tem 'anterior'.
        novo->ant = NULL;
        M->Primeiro = novo;
    } else {
        // Se já tem gente, o 'anterior' do novo aponta pro atual último da lista
        novo->ant = M->Ultimo;
        // O 'proximo' do antigo último agora aponta pro novo
        M->Ultimo->prox = novo; 
    }
    // O ponteiro Ultimo da lista passa a ser o novo nó
    M->Ultimo = novo; 
}

// ====================================================================
// 1. DEBITO E CREDITO (SAQUE E DEPOSITO)
// ====================================================================

void debito_credito(ListaContas *L, ListaMovimentacoes *M) {
    int codigo, tipo; 
    double valor;
    
    tela("MOVIMENTACAO DE DEBITO E CREDITO");
    gotoxy(24, 8); printf("Codigo da Conta: ");
    scanf("%d", &codigo); limpar_buffer();

    ContaBancaria *conta = pesquisa_conta(L, codigo);
    if(conta == NULL) { exibir_msg("Conta nao encontrada!", 0); return; }

    if(strcmp(conta->status, "ATIVO") != 0) { 
        exibir_msg("ERRO: Operacao negada. Conta inativa!", 0); 
        return; 
    }

    gotoxy(24, 10); printf("Titular/Banco: %s", conta->banco);
    gotoxy(24, 11); printf("Saldo Atual..: R$ %.2lf", conta->vl_saldo);
    gotoxy(24, 12); printf("Limite.......: R$ %.2lf", conta->vl_limite);
    
    gotoxy(24, 14); printf("Tipo de Operacao (1 - Deposito | 2 - Saque): ");
    scanf("%d", &tipo); limpar_buffer();

    if(tipo != 1 && tipo != 2) { exibir_msg("Tipo de operacao invalida!", 0); return; }

    gotoxy(24, 16); printf("Valor da Operacao: R$ ");
    scanf("%lf", &valor); limpar_buffer();

    if(valor <= 0) { exibir_msg("Valor invalido! Deve ser maior que zero.", 0); return; }

    if(tipo == 1) { // DEPOSITO (CREDITO)
        conta->vl_saldo += valor;
        registrar_movimentacao(M, conta->codigo_conta, "CREDITO", valor, conta->vl_saldo);
        exibir_msg("Deposito (Credito) realizado com sucesso!", 1);
        
    } else if(tipo == 2) { // SAQUE (DEBITO)
        if(valor > (conta->vl_saldo + conta->vl_limite)) { 
            exibir_msg("ERRO: Saldo e Limite insuficientes para este saque!", 0); 
            return; 
        }
        conta->vl_saldo -= valor;
        registrar_movimentacao(M, conta->codigo_conta, "DEBITO", valor, conta->vl_saldo);
        exibir_msg("Saque (Debito) realizado com sucesso!", 1);
    }
}

// ====================================================================
// 2. TRANSFERENCIA ENTRE CONTAS
// ====================================================================

void transferencia(ListaContas *L, ListaMovimentacoes *M) {
    int cod_origem, cod_destino;
    double valor;

    tela("TRANSFERENCIA ENTRE CONTAS BANCARIAS");
    
    gotoxy(24, 8); printf("Codigo da Conta de ORIGEM (Quem envia): ");
    scanf("%d", &cod_origem); limpar_buffer();
    ContaBancaria *c_origem = pesquisa_conta(L, cod_origem);
    
    if(c_origem == NULL) { exibir_msg("Conta de origem nao encontrada!", 0); return; }
    if(strcmp(c_origem->status, "ATIVO") != 0) { exibir_msg("ERRO: Conta de origem inativa!", 0); return; }

    gotoxy(24, 10); printf("Codigo da Conta de DESTINO (Quem recebe): ");
    scanf("%d", &cod_destino); limpar_buffer();
    ContaBancaria *c_destino = pesquisa_conta(L, cod_destino);

    if(c_destino == NULL) { exibir_msg("Conta de destino nao encontrada!", 0); return; }
    if(strcmp(c_destino->status, "ATIVO") != 0) { exibir_msg("ERRO: Conta de destino inativa!", 0); return; }
    if(cod_origem == cod_destino) { exibir_msg("ERRO: As contas devem ser diferentes!", 0); return; }

    gotoxy(24, 12); printf("Saldo Disponivel (Origem): R$ %.2lf", c_origem->vl_saldo + c_origem->vl_limite);
    gotoxy(24, 14); printf("Valor a Transferir: R$ ");
    scanf("%lf", &valor); limpar_buffer();

    if(valor <= 0) { exibir_msg("Valor invalido!", 0); return; }
    if(valor > (c_origem->vl_saldo + c_origem->vl_limite)) { 
        exibir_msg("ERRO: Saldo insuficiente na conta de origem!", 0); 
        return; 
    }

    // Efetiva a transferência (matemática)
    c_origem->vl_saldo -= valor;
    c_destino->vl_saldo += valor;

    // Registra as duas movimentações
    tela("REGISTRO DA TRANSFERENCIA (DATA)");
    gotoxy(24, 18); printf("Registrando DEBITO na Origem...");
    registrar_movimentacao(M, c_origem->codigo_conta, "TRANSF-OUT", valor, c_origem->vl_saldo);
    
    gotoxy(24, 19); printf("Registrando CREDITO no Destino...");
    registrar_movimentacao(M, c_destino->codigo_conta, "TRANSF-IN", valor, c_destino->vl_saldo);

    exibir_msg("Transferencia realizada com sucesso!", 1);
}

// ====================================================================
// 3. CONSULTA (EXTRATO)
// ====================================================================

void extrato_conta(ListaMovimentacoes *M, int codigo) {
    Movimentacao *aux = M->Primeiro;
    int linha = 8;
    int encontrou = 0;
    
    tela("EXTRATO DE MOVIMENTACOES"); 
    gotoxy(5, 6); printf("CONTA: %d", codigo);
    gotoxy(5, 7); printf("----------------------------------------------------------------------");
    
    while(aux != NULL) {
        if(aux->codigo_conta == codigo) {
            encontrou = 1;
            
            if(linha >= 21) { 
                exibir_msg("Pressione qualquer tecla para continuar...", 1);
                tela("EXTRATO DE MOVIMENTACOES (CONTINUACAO)"); 
                gotoxy(5, 6); printf("CONTA: %d", codigo);
                gotoxy(5, 7); printf("----------------------------------------------------------------------");
                linha = 8;
            }
            
            gotoxy(5, linha++); 
            printf("Seq: %03d | Data: %s | Tipo: %-10s | Valor: %8.2lf | Saldo: %8.2lf", 
                   aux->sequencial, aux->dt_movimento, aux->tp_movimentacao, aux->vl_movimento, aux->vl_saldo);
        }
        aux = aux->prox; // Percorrendo do início ao fim
    }
    
    if(!encontrou) exibir_msg("Nenhuma movimentacao registrada para esta conta.", 0);
    else exibir_msg("Fim do extrato! Pressione qualquer tecla.", 1);
}

// ====================================================================
// MENU DE MOVIMENTACOES (IDÊNTICO À IMAGEM 3)
// ====================================================================

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
