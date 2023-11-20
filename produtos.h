#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED

typedef struct produtos{
    long int cod;
    char descricao[100];
    int quant;
    float valor;
    struct produtos *prox;
}Produtos;

/*
** Função gera um código para o produto
*/
long int geraCodigo();

/*
** Devolve um código único para um novo produto
*/
long int defineCodigoProd(Produtos *ini_p);

/*
** Iniciali a lista de produtos
*/
Produtos *inicializa_p();

/*
** Insere um novo produto ao sistema
*/
Produtos *insereProduto(Produtos *ini_p);

/*
** Encontra um produto na lista através do código
*/
Produtos *encontraProduto(Produtos *ini_p, long int codigo);

/*
** Lista todos os produtos em estoque
**
*/
void listarProdutos(Produtos *ini_p);
#endif // PRODUTOS_H_INCLUDED
