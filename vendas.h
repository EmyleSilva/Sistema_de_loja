#ifndef VENDAS_H_INCLUDED
#define VENDAS_H_INCLUDED

#include "produtos.h"

typedef struct itens{
    struct produtos prodItem;
    int quantidadeItem;
    float valorTotalItem;
}Itens;

typedef struct vendas{
    int codigo;
    struct itens *item;
    int tamItem;
    int dia;
    int mes;
    int ano;
    int hora;
    int seg;
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

#endif // VENDAS_H_INCLUDED
