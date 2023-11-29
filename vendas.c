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
    printf("\n\tATENÇÃO: Para finalizar a venda, pressione 0");
    int quant_itens = 0;
    int verificaQuant = 0;
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

            printf("\n\tQuantidade: ");
            scanf("%d%*c", &quant_itens);

            while(!(verificaQuant = verificaEstoque(aux, quant_itens))){
                printf("\n\tQuantidade em falta no estoque.");
                printf("\n\tTOTAL em estoque: %d. Tente novamente", aux->quant);
                printf("\n\tQuantidade: "); scanf("%d%*c", &quant_itens);
            }

            //excluirItens(aux, quantidade_prod); //TODO: Da certo, mas tem que atualizar os produtos apoś finalizar
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

            produtos = (Itens *)realloc(produtos, ((*quantidade_prod) + 1)*sizeof(Itens));

        }else{
            printf("\n\tVENDA ENCERRADA!!\n"); //TODO: LISTAR A VENDA E MOSTRAR VALOR TOTAL
        }
    }while(codigo);

    return produtos;
}


//-------------------------------------------------------------
// Cadastra a venda realizada na lista encadeada de vendas
//-------------------------------------------------------------

Vendas* cadastraVenda(Vendas *ini_v, Itens *prods, int tamProds, float totalVenda){
    Vendas *novo = (Vendas *)malloc(sizeof(Vendas));
    //TODO: Deixar Data e hora automaticos
    if(novo){
        novo->codigo = 1;
        novo->dia = 27;
        novo->mes = 11;
        novo->ano = 2023;
        novo->hora = 22;
        novo->seg = 3;
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
// Verifica se a quantidade a ser vendida está disponivel em
// estoque, retorna 0 caso não haja quantidade suficiente
//-------------------------------------------------------------

int verificaEstoque(Produtos *prod, int quantidade_prod){
    if(quantidade_prod > prod->quant){
        return 0;
    }
    return 1;
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
            printf("\tHora: %dh %ds\n", aux->hora, aux->seg);
            for(int i = 0; i < aux->tamItem ; i++){
                printf("\n\tItem %d: %li - %s\n", i+1,aux->item[i].prodItem.cod, aux->item[i].prodItem.descricao);
                printf("\t\tValor uni.: R$%.2f \tQuant.: %d \t", aux->item[i].prodItem.valor, aux->item[i].quantidadeItem);
                printf("Valor tot.: R$%.2f\n", aux->item[i].valorTotalItem);
            }
            printf("\n\tValor total da compra: R$ %.2f\n", aux->total);
        }
    }
    printf("\n\t%d Clientes encontrados.\n", cont);
}

