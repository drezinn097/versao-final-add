#include "sistema.h"


void consultar_bancos(ListaBancos *L) {
    tela();
    Banco *aux = L->Primeiro;
    int linha = 6;
    if (aux == NULL) { exibir_msg("Nenhum banco cadastrado!", 0); return; }

    set_cor(11, 0); gotoxy(24, 4); printf("--- LISTA DE BANCOS ---"); set_cor(15, 0);
    while (aux != NULL && linha < 20) {
        gotoxy(5, linha++); printf("Cod: %d | Nome: %s | CNPJ: %s | Ag: %s | Cidade: %s-%s", 
            aux->codigo_banco, aux->nome_banco, aux->cnpj, aux->numero_agencia, aux->cidade, aux->uf);
        aux = aux->prox;
    }
    exibir_msg("Consulta finalizada!", 1);
}
