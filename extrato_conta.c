#include "sistema.h"


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
