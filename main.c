#include "sistema.h"

// ====================================================================
// FUNCOES DE INTERFACE E UTILITARIOS
// ====================================================================

void gotoxy(int x, int y) {
    COORD coord; coord.X = (short)x; coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_cor(int texto, int fundo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (fundo << 4) | texto);
}

void limpar_buffer() {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

// FUNCAO QUE ESTAVA FALTANDO! (Substitui o gets)
void ler_string(char *str, int tamanho) {
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = 0; // Remove o Enter do final
}

void tela(char *titulo_menu) {
    int l, c;
    set_cor(12, 0); // TUDO VERDE!
    system("cls");

    // BARRAS E CANTOS
    for (c = 1; c <= 80; c++) { 
        gotoxy(c, 1); printf("-"); gotoxy(c, 4); printf("-"); 
        gotoxy(c, 22); printf("-"); gotoxy(c, 24); printf("-"); 
    }
    for (l = 1; l <= 24; l++) { 
        gotoxy(1, l); printf("|"); gotoxy(80, l); printf("|"); 
    }
    gotoxy(1, 1); printf("+"); gotoxy(80, 1); printf("+");
    gotoxy(1, 4); printf("+"); gotoxy(80, 4); printf("+");
    gotoxy(1, 22); printf("+"); gotoxy(80, 22); printf("+");
    gotoxy(1, 24); printf("+"); gotoxy(80, 24); printf("+");

    // CABECALHO E TITULO DINAMICO
    gotoxy(3, 2); printf("UNICV");
    gotoxy(24, 2); printf("SISTEMA DE CONTROLE BANCARIO");
    gotoxy(62, 2); printf("Estrutura de Dados");
    
    int espaco = (80 - strlen(titulo_menu)) / 2;
    gotoxy(espaco, 3); printf("%s", titulo_menu);
    gotoxy(3, 3); printf("Andre Luiz");
    gotoxy(62, 3); printf("Felipe de Ciesco");  
    
    gotoxy(2, 23); printf("MSG.: ");
}

void limpar_msg() {
    gotoxy(8, 23); printf("                                                                       ");
}

void exibir_msg(char *msg, int sucesso) {
    limpar_msg();
    gotoxy(8, 23);
    printf("%s", msg); 
    getch();
}

// ====================================================================
// PERSISTENCIA (CARREGAR E SALVAR) - AS FUNCOES FALTANTES
// ====================================================================

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

// ====================================================================
// MOTOR PRINCIPAL
// ====================================================================

int main() {
    ListaBancos bancos = {NULL, NULL};
    ListaContas contas = {NULL, NULL};
    ListaMovimentacoes movimentacoes = {NULL, NULL};

    carregar_dados(&bancos, &contas, &movimentacoes);

    int opcao;
    do {
        tela("MENU PRINCIPAL");
        
        gotoxy(25, 11); printf("1 - Contas Bancarias");
        gotoxy(25, 13); printf("2 - Movimentacao Bancaria");
        gotoxy(25, 15); printf("3 - Sair do Programa");
        
        gotoxy(8, 23); printf("Digite sua Opcao: ");
        scanf("%d", &opcao); limpar_buffer();

        switch(opcao) {
            case 1: menu_cadastro_contas(&contas); break;
            case 2: menu_movimentacoes(&contas, &movimentacoes); break;
            case 3: exibir_msg("Saindo do programa...", 1); break;
            default: exibir_msg("Opcao invalida!", 0); break;
        }
    } while (opcao != 3);

    salvar_dados(&bancos, &contas, &movimentacoes);
    return 0;
}
