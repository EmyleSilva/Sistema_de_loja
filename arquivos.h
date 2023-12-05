#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED

#include "produtos.h"
#include "vendas.h"

/*
** Funções que inicializam os produtos e vendas;
** Quando o sistema é aberto, a função inicia o mesmo
** com valores recuperados dos respectivos arquivos.
*/
Produtos* inicializaProdutos(char *nomeArq, int *quant);
Vendas* inicializaVendas(Vendas **ini_v, int *quant_v, char *nomeArq);
/*
** Função que passa os valores dos arquivos para as
** listas encadeadas do sistema
*/
Produtos *iniciaListaProd(Produtos *ini_prod, Produtos *aux, int quant);

/*
** Lê os valores armazenados nos arquivos, e salva em um vetor
** que é retornado para que os demais procedimentos possam ser
** realizados
*/
Produtos* lerArquivosProdutos(char *nomeArq, int quantidade_p);
Vendas* lerArquivoRelatorio(char *nomeArq, int *tamV, float *total_periodo);

/*
** Procedimentos que salvam os valores do sistema em arquivos
** durante a execução
*/
void salvarProdutos(char *nomeArq, int quant_p, Produtos *ini_p);
void salvarVendas(char *nomeArq, int quant_v, Vendas *ini_v);
void salvarRelatorio(char *nomeArq, Vendas *r, int tamV, float total_periodo, int mes);


#endif // ARQUIVOS_H_INCLUDED
