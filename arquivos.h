/**
* @file arquivos.h
* @brief Declaração de funções utilizadas para operações de arquivos.
*
*/


#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED

#include "produtos.h"
#include "vendas.h"

/**
* @brief Inicializa a lista de Produtos.
*
* Verifica se o arquivo de produtos existe. Caso exista,
* lê a quantidade de produtos armazenados para que as
* operações de recuperação dos dados possam ser feitas.
* A função é chamada antes do ínicio do menu, para que
* o sistema seja iniciado com os valores corretos.
*
* @param nomeArq Ponteiro para o nome do arquivo de produtos.
* @param quant Ponteiro para a quantidade de produtos salvos.
*
* @return Um ponteiro para o inicio da lista de produtos inicializada ou NULL.
*/
Produtos* inicializaProdutos(char *nomeArq, int *quant);

/**
* @brief Inicializa a lista de Vendas.
*
* Verifica se o arquivo de vendas existe. Caso exista,
* lê a quantidade de vendas armazenadas para que as
* operações de recuperação dos dados possam ser feitas.
* A função é chamada antes do ínicio do menu, para que
* o sistema seja iniciado com os valores corretos.
*
* @param ini_v Um ponteiro para o ponteiro do inicio da lista de vendas.
* @param quant_v Ponteiro para a quantidade de vendas salvas.
* @param nomeArq Ponteiro para o nome do arquivo de vendas.
*
* @return Um ponteiro para o inicio da lista de vendas inicializada ou NULL.
*/
Vendas* inicializaVendas(Vendas **ini_v, int *quant_v, char *nomeArq);

/*
** Função que passa os valores dos arquivos para as
** listas encadeadas do sistema
*/
/**
* @brief Inicia a lista de produtos.
*
* Utiliza um laço para passar todos os valores recuperados do
* arquivo de produtos para uma lista encadeada.
* @see recuperaProdutos
*
* @param ini_prod Ponteiro para o inicio da lista de produtos.
* @param aux Ponteiro para um vetor que armazena os produtos recuperados do arquivo.
* @param quant Quantidade de produtos recuperados.
*
* @return Um ponteiro para o inicio da lista de vendas.
*/
Produtos *iniciaListaProd(Produtos *ini_prod, Produtos *aux, int quant);

/**
* @brief Lê os valores armazenados no arquivo de produtos.
*
* @param nomeArq Nome do arquivo de produtos.
* @param quantidade_p Quantidade de produtos salvos no arquivo.
*
* @see Produtos
* @return Um vetor do tipo Produtos com os valores recuperados do arquivo.
*
*/
Produtos* lerArquivosProdutos(char *nomeArq, int quantidade_p);

/**
* @brief Lê os valores armazenados no arquivo de Relatórios.
*
* @param nomeArq Nome do arquivo de relatórios.
* @param tamV Ponteiro para a variavel que armazena o tamanho do vetor de vendas do período.
* @param total_periodo Ponteiro para variavel que armazena o valor do faturamento do mês.
*
* @return Um vetor do tipo Vendas com os valores que fazem parte do período salvo.
*
*/
Vendas* lerArquivoRelatorio(char *nomeArq, int *tamV, float *total_periodo);

/**
* @brief Lê os valores armazenados no arquivo de avisos de estoque.
*
* Recupera do arquivo de avisos todos os produtos que foram salvos
* com notificação de estoque irregular.
*
* @see buscarEstoqueIrregular
* @see mostraAvisosEstoque
*
* @return Um vetor com itens de estoque irregular recuperados do arquivo.
*/
Produtos *lerArquivoAvisos(int *tam_p);

/**
* @brief Salva em um arquivo os produtos cadastrados no sistema.
*
* @param nomeArq Ponteiro para o nome do arquivo em que os produtos serão salvos.
* @param quant_p Quantidade de produtos cadastrados no sistema.
* @param ini_p Ponteiro para o inicio da lista de produtos.
*/
void salvarProdutos(char *nomeArq, int quant_p, Produtos *ini_p);

/**
* @brief Salva em um arquivo as vendas cadastradas no sistema.
*
* @param nomeArq Ponteiro para o nome do arquivo em que as vendas serão salvas.
* @param quant_v Quantidade de vendas cadastradas no sistema.
* @param ini_v Ponteiro para o inicio da lista de vendas.
*/
void salvarVendas(char *nomeArq, int quant_v, Vendas *ini_v);

/**
* @brief Salva em um arquivo o relatório de faturamento mensal.
*
* @param nomeArq Ponteira para o nome do arquivo em que o relatório será salvo.
* @see geraNomeRelatorio
*
* @param r Ponteiro para o vetor que armazena as vendas do periodo selecionado.
* @param tamV Tamanho do vetor que contém as vendas do periodo selecionado.
* @param total_periodo Valor do faturamento mensal.
* @param mes Inteiro que indica a qual mês o relatório gerado se refere.
*/
void salvarRelatorio(char *nomeArq, Vendas *r, int tamV, float total_periodo, int mes);

/**
* @brief Salva os avisos de estoque irregular.
*
* Quando há algum item com estoque irregular, as notificações de regularização
* são salvas em um arquivo.
*
* @param avisos Ponteiro para um vetor com todos os produtos que estão com estoque irregular.
* @param tam_p Tamanho do vetor que guarda os itens irregulares.
*/
void salvarAvisosEstoque(Produtos *avisos, int tam_p);

#endif // ARQUIVOS_H_INCLUDED
