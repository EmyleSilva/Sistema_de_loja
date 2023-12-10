#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED

/*
** Os defines T_ESTOQUE e T_VENDAS definem
** se o estoque está sendo atualizado durante
** ou no próprio estoque.
*/
#define T_ESTOQUE 0
#define T_VENDAS 1

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
** Recebem os dados referentes às atualizações de estoque
*/
Produtos* atualizaEstoqueAdd(Produtos *ini_p, int *confirma, int *quant_ad);
Produtos* atualizaEstoqueDel(Produtos *ini_p, int *confirma, int *quant_del);

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

/*
** Quando uma venda é realizada e há uma saída de estoque
** maior do que a quantidade registrada no sistema, o produto
** recebe um valor negativo, indicando necessidade de revisão
** no estoque. A função busca esses produtos e retorna o numero
** de irregularidades.
*/
int buscarEstoqueIrregular(Produtos *ini_p);

/*
** Mostra os avisos de irregularidade de estoque para o usuario
** tem como parâmetro a quantidade de produtos irregulares,
** para recuperar os dados do arquivo
*/
void mostraAvisosEstoque(int tam_p);
#endif // PRODUTOS_H_INCLUDED
