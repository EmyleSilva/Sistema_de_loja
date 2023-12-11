/**
* @file produtos.h
* @brief Declaração de funções utilizadas para manipular produtos.
*/

#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED

/**
* @brief Definição de tipo de operação
*
* Definição usada para especificar que a operação
* está sendo executada durante uma atualização
* direta do estoque.
*/
#define T_ESTOQUE 0

/**
* @brief Definição de tipo de operação
*
* Definição usada para específicar que a operação
* está sendo executada durante a realização
* de uma venda.
*/
#define T_VENDAS 1

/**
* @brief Struct de produtos.
*
* Struct que representa os produtos do sistema, organizados
* em forma de lista encadeada. Contém as informações
* principais dos produtos, além do estoque (variavel quant).
*/
typedef struct produtos{
    long int cod;        /** < Código do produto. */
    char descricao[100]; /** < Descrição do produto. */
    int quant;           /** < Quantidade em estoque. */
    float valor;         /** < Preço do produto. */
    struct produtos *prox; /** < Ponteiro que aponta para o próximo produto da lista. */
}Produtos;

/**
* @brief Valida os códigos de produtos.
*
* Verifica se o código inserido pelo usuário para um produto
* já está sendo utilizado em algum outro produto. Caso esteja
* pede ao usuário que indique outro código.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param codigo Codigo do produto a ser verificado.
*
* @return Um código de produto válido.
*/
long int validaCodigoProd(Produtos *ini_p, long int codigo);

/**
* @brief Insere um Produto.
*
* A função insere um novo produto ao inicio da lista.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
*
* @return O novo ponteiro para o inicio da lista de produtos.
*/
Produtos *insereProduto(Produtos *ini_p);

/**
* @brief Salva os produtos dos arquivos no sistema.
*
* Salva na lista encadeada os produtos que foram recuperados
* durante a inicialização do programa. Mantém o sistema
* persistente ao atualizar os valores salvos antes do
* programa ser encerrado.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param codigo Codigo do produto.
* @param descricao Descrição do produto.
* @param valor Preço do produto.
* @param quant A quantidade em estoque do produto.
*
* @return O novo ponteiro para o inicio da lista.
*/
Produtos *recuperaProdutos(Produtos *ini_p, long int codigo, char *descricao, float valor, int quant);

/**
* @brief Busca um produto na lista.
*
* Faz uma pesquisa na lista em busca do produto
* requerido pelo usuário.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param codigo Codigo do produto que está sendo pesquisado.
*
* @return O produto buscado, ou NULL caso o produto não exista.
*/
Produtos *encontraProduto(Produtos *ini_p, long int codigo);

/**
* @brief Valida descrição do produto.
*
* Verifica se a descrição do produto inserida pelo usuário
* já está sendo usada em outro produto. Caso esteja, solicita
* ao usuário uma nova descrição.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param descricao Ponteiro para a descrição do produto adicionado.
*
* @return Uma descrição válida para o produto.
*/
char* verificaDescricao(Produtos *ini_p, char *descricao);

/**
* @brief Inicia a entrada de estoque.
*
* Busca as informações necessárias para a atualização de estoque
* A função busca o produto a ser atualizado. Recebe a quantidade
* de entrada do estoque por referência e confirma se o usuário
* deseja prosseguir com a operação.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param confirma Variavel de confirmação da operação, atualizada por referência.
* @param quant_ad Quantidade de entrada de estoque, atualizada por referência.
*
* @return O produto em que a operação de entrada de estoque será realizada.
*/
Produtos* atualizaEstoqueAdd(Produtos *ini_p, int *confirma, int *quant_ad);

/**
* @brief Inicia a saida de estoque.
*
* Busca as informações necessárias para a atualização de estoque
* A função busca o produto a ser atualizado. Recebe a quantidade
* de saída do estoque por referência e confirma se o usuário
* deseja prosseguir com a operação.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param confirma Variavel de confirmação da operação, atualizada por referência.
* @param quant_del Quantidade de saída de estoque, atualizada por referência.
*
* @return O produto em que a operação de saída de estoque será realizada.
*/
Produtos* atualizaEstoqueDel(Produtos *ini_p, int *confirma, int *quant_del);

/**
* @brief Adiciona Itens ao estoque.
*
* Atualiza o estoque adicionando a quantidade de itens indicada pelo usuario.
* A operação verifica se o estoque está sendo regularizado (quando a quantidade
* atual é igual a -1, nesse caso, 'adiciona' uma unidade a mais. Caso contrário,
* o estoque estava regular, e a adição é feita normalmente.
*
* @param produto Ponteiro para o produto que terá o estoque atualizado.
* @param qunat Quantidade a ser adicionada.
*
*/
void adicionarItens(Produtos *produto, int quant);

/**
* @brief Deleta Itens do estoque.
*
* Atualiza o estoque excluindo a quantidade de itens indicada pelo usuario.
* A operação pode ser realizada a partir do estoque ou durante a realização
* de uma venda. O tipo da operação é definido pela constante T_ESTOQUE ou
* T_VENDA.
*
* Caso seja chamada durante o estoque: Verifica se a quantidade que o usuário
* deseja deletar é maior do que a quantidade já registrada. Caso não seja,
* deleta a quantidade pedida, caso contrário, o estoque é zerado.
*
* Caso seja chamada durante a venda: Verifica se a quantidade comprada é maior
* do que a quantidade registrada. Caso seja, marca o produto como irregular
* ao definir a quantidade como -1, caso contrário, atualiza o estoque com a saída
* da venda.
*
* @param produto Ponteiro para o produto que terá o estoque atualizado.
* @param qunat Quantidade a ser excluida.
*
*/
void excluirItens(Produtos *produto, int quant, int tipo_operacao);

/**
* @brief Consulta preço
*
* Consulta o preço de um produto específicado pelo usuário (busca através do
* código do produto.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
*/
void consultaPreco(Produtos *ini_p);

/**
* @brief Mostrar os produtos cadastrados.
*
* Lista na tela todos os produtos que estão cadastrados no sistema.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
*/
void listarProdutos(Produtos *ini_p);

/**
* @brief Busca estoque irregular.
* @see excluirItens.
*
* Busca na lista os produtos que ficaram com estoque irregular (-1)
* durante uma venda.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
*
* @return Quantidade de produtos que estão irregulares.
*/
int buscarEstoqueIrregular(Produtos *ini_p);

/**
* @brief Mostra avisos de estoque irregular.
* @see buscarEstoqueIrregular.
*
* Mostra para o usuário um relatório com as informações dos
* produtos que estão com estoque irregular, e informa a necessidade
* de regularização do estoque.
*
* @param tam_p Quantidade de produtos irregulares.
*/
void mostraAvisosEstoque(int tam_p);
#endif // PRODUTOS_H_INCLUDED
