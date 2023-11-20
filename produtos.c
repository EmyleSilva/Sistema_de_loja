#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include "interface.h"

//------------------------------------------------------
// Inicializa a lista de produtos com NULL
//------------------------------------------------------
Produtos *inicializa_p(){
    return NULL;
}

//------------------------------------------------------
// A função retorna um código (long int) para o produto
//------------------------------------------------------
long int geraCodigo(){
    return 1000+(rand()%1000);
}

//------------------------------------------------------
// Verifica se o código gerado para um produto já está
// em uso, retorna o mesmo codigo ou um novo
//------------------------------------------------------
long int defineCodigoProd(Produtos *ini_p){
    long int codigo = geraCodigo();
    Produtos *aux = encontraProduto(ini_p, codigo);

    while(aux != NULL){
        codigo = geraCodigo();
        aux = encontraProduto(ini_p, codigo);
    }
    return codigo;
}

//------------------------------------------------------
// Insere um novo produto no inicio da lista
//------------------------------------------------------
Produtos* insereProduto(Produtos *ini_p){
    Produtos *novo = (Produtos *)malloc(sizeof(Produtos));
    if(novo){
        novo->cod = defineCodigoProd(ini_p);
        //novo->cod = 1;
        printf("\n\tInforme o nome do produto: ");
        scanf("%99[^\n]%*c", novo->descricao);

        printf("\tInforme o preço do produto: ");
        scanf("%f%*c", &novo->valor);

        printf("\tInforme a quantidade inicial em estoque: ");
        scanf("%d%*c", &novo->quant);

        novo->prox = ini_p;
    }else{
        mostra_erro_e_encerra("Erro interno: Memoria insuficiente");
    }

    return novo;

}

//--------------------------------------------------------
// Encontra um elemento na lista através do código,
// e o retona.
//--------------------------------------------------------
Produtos *encontraProduto(Produtos *ini_p, long int codigo){
    Produtos *aux = ini_p;

    if(aux == NULL) return NULL;

    while(aux->prox != NULL && aux->cod != codigo){
        aux = aux->prox;
    }

    if(aux->cod == codigo)return aux;
    return NULL;
}

//--------------------------------------------------------
// Lista todos os produtos registrados
//--------------------------------------------------------
void listarProdutos(Produtos *ini_p){
    Produtos *aux = ini_p;
    int cont = 0;
    if(ini_p){
        for(; aux; aux=aux->prox){
            cont++;
            printf("\n\t-------------------- Produto %d --------------------\n", cont);
            printf("\t%li - Descricao: %s\n", aux->cod, aux->descricao);
            printf("\tPreço: %.2f\n", aux->valor);
            printf("\tQuantidade: %d\n", aux->quant);
        }
    }
    printf("\n\t%d Produtos encontrados.\n", cont);
}



