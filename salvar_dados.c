#include "sistema.h"


void salvar_dados(ListaBancos *B, ListaContas *C, ListaMovimentacoes *M) {
    FILE *arq;
    
    ContaBancaria *auxC = C->Primeiro;
    arq = fopen("contas.dat", "wb");
    if(arq != NULL) {
        while(auxC != NULL) { fwrite(auxC, sizeof(ContaBancaria), 1, arq); auxC = auxC->prox; }
        fclose(arq);
    }

    Banco *auxB = B->Primeiro;
    arq = fopen("bancos.dat", "wb");
    if(arq != NULL) {
        while(auxB != NULL) { fwrite(auxB, sizeof(Banco), 1, arq); auxB = auxB->prox; }
        fclose(arq);
    }

    Movimentacao *auxM = M->Primeiro;
    arq = fopen("movimentacoes.dat", "wb");
    if(arq != NULL) {
        while(auxM != NULL) { fwrite(auxM, sizeof(Movimentacao), 1, arq); auxM = auxM->prox; }
        fclose(arq);
    }
}
