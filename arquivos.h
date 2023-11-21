#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED

#include "produtos.h"

Produtos* inicializaProdutos(char *nomeArq, int *quant);
Produtos *iniciaListaProd(Produtos *ini_prod, Produtos *aux, int quant);
Produtos* lerArquivosProdutos(char *nomeArq, int quantidade_p);
FILE* salvarProdutos(char *nomeArq, int quant_p, Produtos *ini_p);

#endif // ARQUIVOS_H_INCLUDED
