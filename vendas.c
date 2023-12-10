#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vendas.h"
#include "produtos.h"
#include "arquivos.h"
#include "interface.h"

//-------------------------------------------------------------
// Realiza uma venda, e retorna um vetor com todos os produtos
// comprados.
//-------------------------------------------------------------

Itens* realizaVenda(Produtos *ini_p, float *totalVenda, int *quantidade_prod){
    printf("\n\tATENÇÃO: Para finalizar a venda, pressione 0\n");
    int quant_itens = 0;
    long int codigo = 0;
    float valorTotal = 0.0;

    Itens *produtos = (Itens *)malloc(sizeof(Itens));
    Produtos *aux = NULL;

    do{
        printf("\n\tCódigo do produto: ");
        scanf("%li%*c", &codigo);

        if(codigo){
            aux = encontraProduto(ini_p, codigo);
            while(!aux){
                printf("\n\tProduto não cadastrado. Tente Novamente.");
                printf("\n\tCódigo do produto: ");
                scanf("%li%*c", &codigo);
                aux = encontraProduto(ini_p, codigo);
            }

            printf("\tQuantidade: ");
            scanf("%d%*c", &quant_itens);

            excluirItens(aux, quant_itens, T_VENDAS);
            valorTotal = aux->valor * quant_itens;

            produtos[(*quantidade_prod)].prodItem.cod = codigo;
            produtos[(*quantidade_prod)].quantidadeItem = quant_itens;
            produtos[(*quantidade_prod)].valorTotalItem = valorTotal;
            produtos[(*quantidade_prod)].prodItem.valor = aux->valor;
            int cont = 0;
            for(cont; aux->descricao[cont]; cont++)
                produtos[(*quantidade_prod)].prodItem.descricao[cont] = aux->descricao[cont];
            produtos[(*quantidade_prod)].prodItem.descricao[cont] = '\0';

            (*totalVenda)+=valorTotal;
            (*quantidade_prod)++;

            limpaTela();
            printf("\n\tATENÇÃO: Para finalizar a venda, pressione 0\n");
            for(int i = 0; i < (*quantidade_prod); i++){
                printf("\n\t%li - %s \t%.2f - %d - %.2f\n",produtos[i].prodItem.cod, produtos[i].prodItem.descricao,
                                                           produtos[i].prodItem.valor, produtos[i].quantidadeItem, produtos[i].valorTotalItem);
            }

            produtos = (Itens *)realloc(produtos, ((*quantidade_prod) + 1)*sizeof(Itens));

        }else{
            if((*totalVenda))
                mostrarNotaFiscal(produtos, (*quantidade_prod), (*totalVenda));
        }
    }while(codigo);

    if(produtos[0].prodItem.cod){
        return produtos;
    }else{
        return NULL;
    }

}

void mostrarNotaFiscal(Itens *produtos, int tam, float totalVenda){
    limpaTela();
    printf("\n\t============================ Venda Finalizada ============================\n");
    printf("\n\tNota Fiscal\n");
    printf("\t----------------------------------------------------------------------\n");
    printf("\tItem - codigo - descrição - Preço uni. - Quant. - Preço Tot.");
    for(int i = 0; i < tam; i++){
        printf("\n\t%d - %li - %s - R$%.2f - %d - R$%.2f\n",
        i+1, produtos[i].prodItem.cod, produtos[i].prodItem.descricao, produtos[i].prodItem.valor, produtos[i].quantidadeItem, produtos[i].valorTotalItem);
    }
    printf("\n\tValor total da venda: R$%.2f\n", totalVenda);
}

//-------------------------------------------------------------
// Cadastra a venda realizada na lista encadeada de vendas
//-------------------------------------------------------------

Vendas* cadastraVenda(Vendas *ini_v, Itens *prods, int tamProds, float totalVenda, int *quant_v){
    Vendas *novo = (Vendas *)malloc(sizeof(Vendas));
    if(novo){
        novo->codigo = (*quant_v) + 1;
        dataHora(&novo->dia, &novo->mes, &novo->ano, &novo->hora, &novo->minutos, &novo->segundos);
        novo->item = prods;
        novo->tamItem = tamProds;
        novo->total = totalVenda;

        novo->prox = ini_v;
    }else{
        mostra_erro_e_encerra(ERRO_MEMORIA);
    }
    return novo;
}

//-------------------------------------------------------------
// Mostra na tela todas as vendas realizadas
//-------------------------------------------------------------

void listarVendas(Vendas *ini_v){
    int cont = 0;
    if(ini_v){
        Vendas *aux = ini_v;

        for(; aux ; aux = aux->prox){
            cont++;
            printf("\n\t-------------------- Venda %d --------------------\n", cont);
            printf("\tCódigo: %d\n", aux->codigo);
            printf("\tData: %d/%d/%d\n", aux->dia, aux->mes, aux->ano);
            printf("\tHora: %d:%d:%d\n", aux->hora, aux->minutos,aux->segundos);
            for(int i = 0; i < aux->tamItem ; i++){
                printf("\n\tItem %d: %li - %s\n", i+1,aux->item[i].prodItem.cod, aux->item[i].prodItem.descricao);
                printf("\t\tValor uni.: R$%.2f \tQuant.: %d \t", aux->item[i].prodItem.valor, aux->item[i].quantidadeItem);
                printf("Valor tot.: R$%.2f\n", aux->item[i].valorTotalItem);
            }
            printf("\n\tValor total da compra: R$ %.2f\n", aux->total);
        }
    }
    printf("\n\t%d Vendas encontrados.\n", cont);
}

//-------------------------------------------------------------
// Recupera a data e hora atual
//-------------------------------------------------------------
void dataHora(int *dia, int *mes, int *ano, int *hora, int *minutos, int *segundos){
    struct tm *t;
    time_t s;

    time(&s);
    t = localtime(&s);

    (*dia) = t->tm_mday;
    (*mes) = t->tm_mon + 1;
    (*ano) = t->tm_year + 1900;
    (*hora) = t->tm_hour;
    (*minutos) = t->tm_min;
    (*segundos) = t->tm_sec;
}

//------------------------------------------------------------
// Gera os nomes dos arquivos para relatórios mensais do
// faturamento de vendas
//------------------------------------------------------------
char* geraNomeRelatorio(int mes){
    char *nomeArq[] = {
        "",
        "relatorios/janeiro.txt",
        "relatorios/fevereiro.txt",
        "relatorios/março.txt",
        "relatorios/abril.txt",
        "relatorios/maio.txt",
        "relatorios/junho.txt",
        "relatorios/julho.txt",
        "relatorios/agosto.txt",
        "relatorios/setembro.txt",
        "relatorios/outubro.txt",
        "relatorios/novembro.txt",
        "relatorios/dezembro.txt"
    };

    return nomeArq[mes];

}

//-------------------------------------------------------------
// Recupera os dados de vendas para gerar relátório
//-------------------------------------------------------------
void gerarRelatorioFaturamento(Vendas *ini_vendas, int mes){
    Vendas *aux = ini_vendas;
    Vendas *relatorio = NULL;

    float total_periodo = 0.0;
    int tamV = 0;
    char *nomeArq = geraNomeRelatorio(mes);
    while(aux){
        if(aux->mes == mes) {
            relatorio = (Vendas *)realloc(relatorio, (tamV+1) * sizeof(Vendas));
            relatorio[tamV].codigo = aux->codigo;
            relatorio[tamV].dia = aux->dia;
            relatorio[tamV].mes = aux->mes;
            relatorio[tamV].ano = aux->ano;
            relatorio[tamV].hora = aux->hora;
            relatorio[tamV].minutos = aux->minutos;
            relatorio[tamV].segundos = aux->segundos;
            relatorio[tamV].total = aux->total;
            tamV++;
            total_periodo += aux->total;
        }
        aux = aux->prox;
    }

    if(relatorio){
        salvarRelatorio(nomeArq, relatorio, tamV, total_periodo, mes);
    }

}

//-------------------------------------------------------------
// Mostra na tela o relatorio de faturamento do mes
//-------------------------------------------------------------
void mostrarRelatorioFaturamento(int mes){
    FILE *fp;
    char *nomeArq = geraNomeRelatorio(mes);
    int tamV = 0;
    float total_periodo = 0.0;

    fp = fopen(nomeArq, "r");
    if(fp == NULL){
        printf("\n\n\tNenhuma venda realizada no periodo informado\n");
    }else{
        Vendas *r = lerArquivoRelatorio(nomeArq, &tamV, &total_periodo);

        limpaTela();
        printf("\n\tRelatório de Faturamento mensal -> Mês: %d\n\n", mes);
        printf("\tCodigo Venda \t\tData e hora \t\tValor Venda\n");
        for(int i = 0; i < tamV; i++){
            printf("\t%d \t\t%d/%d/%d %2d:%2d:%2d \t\t%.2f\n", r[i].codigo, r[i].dia, r[i].mes, r[i].ano, r[i].hora,
                    r[i].minutos, r[i].segundos, r[i].total);
        }
        printf("\tTotal de vendas do mês: %d\n", tamV);
        printf("\tFaturamento do mês: %.2f\n\n", total_periodo);
    }
}




