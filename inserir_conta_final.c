#include "sistema.h"


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
