#include "sistema.h"


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
