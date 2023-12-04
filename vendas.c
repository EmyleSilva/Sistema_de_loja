#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vendas.h"
#include "produtos.h"
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

            excluirItens(aux, quant_itens, 1);
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
            printf("\n\t%li - %s \t%.2f - %d - %.2f\n", aux->cod, aux->descricao, aux->valor, quant_itens, valorTotal);

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
        printf("\n\t%d - %li - %s - R$%.2f - %d - R$%.2f",
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
        mostra_erro_e_encerra("\n\tERRO INTERNO: Memória insuficiente\n");
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
            printf("\tCódigo: %li\n", aux->codigo);
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

