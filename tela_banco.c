#include "sistema.h"


void tela_Banco() {
    set_cor(11, 0); // Ciano
    gotoxy(24, 4); printf("| CADASTRO DE BANCO/AGENCIA |");
    set_cor(15, 0); // Branco
    gotoxy(24, 6);  printf("CODIGO DO BANCO.....: ");
    gotoxy(24, 7);  printf("NOME DA INSTITUICAO.: ");
    gotoxy(24, 8);  printf("CNPJ................: ");
    gotoxy(24, 9);  printf("NUMERO DA AGENCIA...: ");
    gotoxy(24, 10); printf("ENDERECO............: ");
    gotoxy(24, 11); printf("NUMERO..............: ");
    gotoxy(24, 12); printf("BAIRRO..............: ");
    gotoxy(24, 13); printf("CIDADE..............: ");
    gotoxy(24, 14); printf("ESTADO (UF).........: ");
    gotoxy(24, 15); printf("TELEFONE CONTATO....: ");
}
