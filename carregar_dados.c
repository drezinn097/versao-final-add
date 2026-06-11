#include "sistema.h"


void carregar_dados(ListaBancos *B, ListaContas *C, ListaMovimentacoes *M) {
    FILE *arq;
    
    // Contas
    ContaBancaria tempC; ContaBancaria *novoC;
    arq = fopen("contas.dat", "rb");
    if(arq != NULL) {
        while(fread(&tempC, sizeof(ContaBancaria), 1, arq)) {
            novoC = (ContaBancaria*) malloc(sizeof(ContaBancaria));
            *novoC = tempC; novoC->prox = NULL;
            if(C->Primeiro == NULL) { C->Primeiro = novoC; C->Ultimo = novoC; }
            else { C->Ultimo->prox = novoC; C->Ultimo = novoC; }
        }
        fclose(arq);
    }
    
    // Bancos
    Banco tempB; Banco *novoB;
    arq = fopen("bancos.dat", "rb");
    if(arq != NULL) {
        while(fread(&tempB, sizeof(Banco), 1, arq)) {
            novoB = (Banco*) malloc(sizeof(Banco));
            *novoB = tempB; novoB->prox = NULL;
            if(B->Primeiro == NULL) { B->Primeiro = novoB; B->Ultimo = novoB; }
            else { B->Ultimo->prox = novoB; B->Ultimo = novoB; }
        }
        fclose(arq);
    }

    // Movimentacoes (Lista Dupla)
    Movimentacao tempM; Movimentacao *novoM;
    arq = fopen("movimentacoes.dat", "rb");
    if(arq != NULL) {
        while(fread(&tempM, sizeof(Movimentacao), 1, arq)) {
            novoM = (Movimentacao*) malloc(sizeof(Movimentacao));
            *novoM = tempM; novoM->prox = NULL;
            if(M->Primeiro == NULL) { novoM->ant = NULL; M->Primeiro = novoM; } 
            else { novoM->ant = M->Ultimo; M->Ultimo->prox = novoM; }
            M->Ultimo = novoM;
        }
        fclose(arq);
    }
}
