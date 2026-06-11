#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include "structs.h"

// --- UTILS & INTERFACE ---
void gotoxy(int x, int y);
void set_cor(int texto, int fundo);
void tela();
void limpar_msg();
void exibir_msg(char *msg, int sucesso);
void limpar_buffer();
void ler_string(char *str, int tamanho);

// --- PERSISTENCIA ---
void carregar_dados(ListaBancos *B, ListaContas *C, ListaMovimentacoes *M);
void salvar_dados(ListaBancos *B, ListaContas *C, ListaMovimentacoes *M);

// --- CONTAS ---
void menu_cadastro_contas(ListaContas *L);
ContaBancaria* pesquisa_conta(ListaContas *L, int cod);
void inserir_conta_inicio(ListaContas *L);
void inserir_conta_posicao(ListaContas *L);
void inserir_conta_final(ListaContas *L);
void alterar_conta(ListaContas *L);
void excluir_conta_inicio(ListaContas *L);
void excluir_conta_posicao(ListaContas *L);
void excluir_conta_final(ListaContas *L);
void consultar_contas(ListaContas *L);

// --- BANCOS E MOVIMENTACOES (Protótipos mantidos para a próxima fase) ---
void menu_cadastro_bancos(ListaBancos *L);
void menu_movimentacoes(ListaContas *L, ListaMovimentacoes *M);

#endif
