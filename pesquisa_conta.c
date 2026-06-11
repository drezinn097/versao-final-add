#include "sistema.h"


ContaBancaria* pesquisa_conta(ListaContas *L, int cod) {
    ContaBancaria *aux = L->Primeiro;
    while (aux != NULL) {
        if (aux->codigo_conta == cod) return aux;
        aux = aux->prox;
    }
    return NULL;
}
