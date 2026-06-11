#include "sistema.h"

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
