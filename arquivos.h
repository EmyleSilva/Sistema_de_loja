#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED

#include "produtos.h"

/*
** Funções que inicializam os produtos e vendas;
** Quando o sistema é aberto, a função inicia o mesmo
** com valores recuperados dos respectivos arquivos.
*/
Produtos* inicializaProdutos(char *nomeArq, int *quant);
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

/*
** Procedimentos que salvam os valores do sistema em arquivos
** durante a execução
*/
void salvarProdutos(char *nomeArq, int quant_p, Produtos *ini_p);

#endif // ARQUIVOS_H_INCLUDED
