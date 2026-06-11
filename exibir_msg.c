#include "sistema.h"


void exibir_msg(char *msg, int sucesso) {
    limpar_msg();
    gotoxy(8, 23);
    printf("%s", msg); 
    getch();
}  
