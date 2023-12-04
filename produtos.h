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
** Devolve um código único para um novo produto
*/
long int validaCodigoProd(Produtos *ini_p, long int codigo);

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
char* verificaDescricao(Produtos *ini_p, char *descricao);

/*
** Adiciona itens ao estoque
*/
void adicionarItens(Produtos *produto, int quant);

/*
** Exclui itens do estoque
*/
void excluirItens(Produtos *produto, int quant, int tipo_operacao);

/*
** Mostra o preço de um produto para o usuario
*/
void consultaPreco(Produtos *ini_p);

/*
** Lista todos os produtos em estoque
**
*/
void listarProdutos(Produtos *ini_p);
#endif // PRODUTOS_H_INCLUDED
