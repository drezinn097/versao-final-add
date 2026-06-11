#include "sistema.h"


void limpar_buffer() {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}
