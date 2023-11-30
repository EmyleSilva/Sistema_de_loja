#ifndef VENDAS_H_INCLUDED
#define VENDAS_H_INCLUDED

#include "produtos.h"

typedef struct itens{
    struct produtos prodItem;
    int quantidadeItem;
    float valorTotalItem;
}Itens;

typedef struct vendas{
    int tamItem;
    int codigo;
    struct itens *item;
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
    int segundos;
    float total;
    struct vendas *prox;
}Vendas;

/*
** Função que realiza uma venda;
** a venda não é salva durante sua execução, sua função
** é retornar um vetor com todos os produtos vendidos.
*/
Itens* realizaVenda(Produtos *ini_p, float *totalVenda, int *quantidade_prod);

/*
** Verifica se a quantidade de saida de um produto
** é possivel (se existe a quantidade necessária em estoque)
*/
int verificaEstoque(Produtos *prod, int quantidade_prod);

/*
** A cadastra a venda (todos os itens vendidos)
** além de registrar o código da venda, data/hora e valor total
*/
Vendas* cadastraVenda(Vendas *ini_v, Itens *prods, int tamProds, float totalVenda);

/*
** Mostra todas as vendas na tela.
*/
void listarVendas(Vendas *ini_v);

/*
** Atribui data e hora de uma venda
*/
void dataHora(int *dia, int *mes, int *ano, int *hora, int *minutos,int *segundos);

/*
** Mostra a nota com todos os itens comprados durante a venda
*/
void mostrarNotaFiscal(Itens *produtos, int tam, float totalVenda);

#endif // VENDAS_H_INCLUDED
