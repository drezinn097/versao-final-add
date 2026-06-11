#include "sistema.h"


void ler_string(char *str, int tamanho) {
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = 0; // Remove o Enter do final
}
