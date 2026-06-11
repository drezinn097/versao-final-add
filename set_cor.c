#include "sistema.h"


void set_cor(int texto, int fundo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (fundo << 4) | texto);
}
