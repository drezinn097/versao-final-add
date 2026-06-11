#include "sistema.h"

Banco* pesquisa_banco(ListaBancos *L, int cod) {
    Banco *aux = L->Primeiro;
    while (aux != NULL) {
        if (aux->codigo_banco == cod) return aux;
        aux = aux->prox;
    }
    return NULL;
}
