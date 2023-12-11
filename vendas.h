/**
* @file vendas.h
* @brief Declaração de funções utilizadas para manipular vendas.
*/

#ifndef VENDAS_H_INCLUDED
#define VENDAS_H_INCLUDED

/**
* @see produtos.h
*/
#include "produtos.h"

/**
* @brief Struct que representa um item vendido.
*
* Formado pela quantidade de itens vendidos, o
* preço total, e também, as informaçẽs gerais
* de um produto.
* @see Produtos
*/
typedef struct itens{
    struct produtos prodItem; /** <Representa o produto (item) vendido */
    int quantidadeItem;       /** <A quantidade de saida desse item */
    float valorTotalItem;     /** <O valor total do produto durante a venda */
}Itens;

/**
* @brief Struct que representa uma venda.
*
* Guarda as informações referentes às vendas realizadas,
* em forma de lista encadeada.
*/
typedef struct vendas{
    int tamItem;        /** <Quantidade de itens vendidos (tamanho do vetor de itens)*/
    int codigo;         /** <Código da venda */
    struct itens *item; /** <Vetor do tipo Itens ( @see Itens ), armazena os produtos vendidos */
    int dia;            /** <Dia em que a venda foi realizada. */
    int mes;            /** <Mês em que a venda foi realizada. */
    int ano;            /** <Ano em que a venda foi realizada. */
    int hora;           /** <Hora em que a venda foi realizada. */
    int minutos;        /** <Minuto em que a venda foi realizada. */
    int segundos;       /** <Segundo em que a venda foi realizada. */
    float total;        /** <Valor total da venda. */
    struct vendas *prox;/** <Ponteiro para a próxima venda de lista */
}Vendas;

/**
* @brief Realiza uma venda
*
* Adiciona todos os produtos passados no caixa à venda, e
* faz a saida de estoque - produtos que estão sendo vendidos.
*
* @param ini_p Ponteiro para o inicio da lista de produtos.
* @param totalVenda Ponteiro para a variavel que armazena o valor total da venda.
* @param quantidade_prod Ponteiro para a variavel que armazena a quantidade de produtos vendidos
*
* @return Retorna um vetor com todos os produtos vendidos.
*/
Itens* realizaVenda(Produtos *ini_p, float *totalVenda, int *quantidade_prod);

/**
* @brief Cadastra a venda
*
* Recupera os itens vendidos e cadastra a venda adicionando o
* vetor junto com as demais informações de vendas na lista.
* @see Vendas
*
* @param ini_v Ponteiro para o inicio da lista de vendas.
* @param prods Vetor com os produtos vendidos.
* @param tamProds Tamanho do vetor prods.
* @param totalVenda Valor total da venda realizada.
* @param quant_v Ponteiro para variavel de quantidade de vendas.
*
* @return O novo ponteiro de inicio da lista de vendas.
*/
Vendas* cadastraVenda(Vendas *ini_v, Itens *prods, int tamProds, float totalVenda, int *quant_v);

/**
* @brief Mostrar as vendas
*
* Mostra na tela todas as vendas realizadas.
*
* @param ini_v Ponteiro para o inicio da lista de vendas.
*
*/
void listarVendas(Vendas *ini_v);

/**
* @brief Defini data e hora de uma venda
*
* Recupera a data e hora da máquina local para
* definir a data/hora de uma venda. Os valores são definidos
* por referência.
*
* @param dia Ponteiro para o dia da venda.
* @param mes Ponteiro para o mes da venda.
* @param ano Ponteiro para o ano da venda.
* @param hora Ponteiro para a hora da venda.
* @param minutos Ponteiro para os minutos da venda.
* @param segundos Ponteiro para os segundos da venda.
*
*/
void dataHora(int *dia, int *mes, int *ano, int *hora, int *minutos,int *segundos);

/**
* @brief Mostra a nota fiscal da venda.
*
* Quando uma venda é finalizada, a nota fiscal com
* o detalhamento dos produtos vendidos e demais
* informações é mostrada na tela.
*
* @param produtos Ponteiro para o vetor de Itens vendidos.
* @param tam Tamanho do vetor de produtos.
* @param totalVenda Valor total da venda.
*
*/
void mostrarNotaFiscal(Itens *produtos, int tam, float totalVenda);

/**
* @brief Gera nome de arquivo para relatório de faturamentos
*
* O nome é gerado de acordo com o mês selecionado para geramento
* de relatório.
* O nome tem o formato 'relatorios/mes.txt', por isso, a pasta
* relatorios deve existir no diretório do sistema.
*
* @param mes Um inteiro que representa o mês selecionado.
*
* @return O nome do arquivo correspondente ao mês.
*/
char* geraNomeRelatorio(int mes);

/**
* @brief Gera o relatório de faturamento mensal.
*
* Busca na lista todas as vendas que foram realizadas
* no período selecionado. As salva em um vetor, e logo
* após, chama uma segunda função para salvar o relatório
* em um arquivo do mês correspondente.
*
* @see gerarRelatorioFaturamento
* @see salvarRelatorio
* @see geraNomeRelatorio
*
* @param ini_vendas Ponteiro para o inicio da lista de vendas.
* @param mes Mês de referência para o geramento de relatório.
*/
void gerarRelatorioFaturamento(Vendas *ini_vendas, int mes);

/**
* @brief Mostra na tela o relatório de faturamento do mês
*
* Busca as informações no arquivo de relatório correspondente
* ao mês buscado, e exibe o relatório na tela.
*
* @param mes Mês de referência para o leitura do arquivo de relatório.
*/
void mostrarRelatorioFaturamento(int mes);

#endif // VENDAS_H_INCLUDED
