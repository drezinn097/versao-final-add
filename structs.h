#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct ContaBancaria {
    int codigo_conta;
    char banco[50];
    char agencia[10];
    char numero_conta[20];
    char tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    char status[10]; // Vamos padronizar como "ATIVO" ou "INATIVO"
    struct ContaBancaria *prox;
} ContaBancaria;

typedef struct {
    ContaBancaria *Primeiro;
    ContaBancaria *Ultimo;
} ListaContas;

typedef struct Movimentacao {
    int sequencial;
    int codigo_conta;
    char dt_movimento[11];
    char tp_movimentacao[15];
    double vl_movimento;
    double vl_saldo;
    struct Movimentacao *ant;
    struct Movimentacao *prox;
} Movimentacao;

typedef struct {
    Movimentacao *Primeiro;
    Movimentacao *Ultimo;
} ListaMovimentacoes;

typedef struct Banco {
    int codigo_banco;
    char nome_banco[50];
    char cnpj[20];
    char numero_agencia[10];
    char endereco[50];
    char numero[10];
    char bairro[30];
    char cidade[30];
    char uf[3];
    char telefone[20];
    struct Banco *prox;
} Banco;

typedef struct {
    Banco *Primeiro;
    Banco *Ultimo;
} ListaBancos;

#endif
