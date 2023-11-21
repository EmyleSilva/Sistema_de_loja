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
** Insere um novo produto ao sistema
*/
Produtos *insereProduto(Produtos *ini_p);

/*
** Salva os produtos do arquivo no sistema
*/
Produtos *recuperaProdutos(Produtos *ini_p, long int codigo, char *descricao, float valor, int quant);

/*
** Encontra um produto na lista através do código
*/
Produtos *encontraProduto(Produtos *ini_p, long int codigo);

/*
** Validar descricao de produto
*/
char* verificaDescricao(Produtos *ini_p, char *descricao, char *nova_descricao);

/*
** Lista todos os produtos em estoque
**
*/
void listarProdutos(Produtos *ini_p);
#endif // PRODUTOS_H_INCLUDED
