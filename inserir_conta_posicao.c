#include "sistema.h"


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
