#include "sistema.h"


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
