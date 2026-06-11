#include "sistema.h"


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
