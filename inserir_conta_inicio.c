#include "sistema.h"


void inserir_conta_inicio(ListaContas *L) {
    ContaBancaria *novo = ler_dados_conta(L);
    
    novo->prox = L->Primeiro; // O novo aponta para o antigo primeiro
    L->Primeiro = novo;       // O primeiro passa a ser o novo
    
    if (L->Ultimo == NULL) {  // Se a lista estava vazia, ele também é o último
        L->Ultimo = novo;
    }
    exibir_msg("Conta cadastrada no INICIO com sucesso!", 1);
}
