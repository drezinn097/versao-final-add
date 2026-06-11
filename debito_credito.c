#include "sistema.h"


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
