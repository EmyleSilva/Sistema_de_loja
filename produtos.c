/**
* @file produtos.c
* @brief Implementação das funções de produtos.
* @see produtos.h
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"
#include "produtos.h"
#include "interface.h"

//------------------------------------------------------
// Verifica se o código já foi usado, e, pede um novo
// caso já esteja em uso
//------------------------------------------------------
long int validaCodigoProd(Produtos *ini_p, long int codigo){
    Produtos *aux = encontraProduto(ini_p, codigo);

    while(aux != NULL){
        printf("\n\tO código digitado já está em uso. Tente novamente\n\t");
        printf("Novo código: "); scanf("%li%*c", &codigo);
        aux = encontraProduto(ini_p, codigo);
    }
    return codigo;
}

//------------------------------------------------------
// Insere um novo produto no inicio da lista
//------------------------------------------------------
Produtos* insereProduto(Produtos *ini_p){
    Produtos *novo = (Produtos *)malloc(sizeof(Produtos));
    char aux[100];

    if(novo){
        printf("\n\tInforme o código do produto: ");
        scanf("%li%*c", &novo->cod);
        novo->cod = validaCodigoProd(ini_p, novo->cod);

        printf("\n\tInforme o nome do produto: ");
        scanf("%99[^\n]%*c", aux);

        strcpy(novo->descricao, verificaDescricao(ini_p, aux));

        printf("\tInforme o preço do produto: ");
        scanf("%f%*c", &novo->valor);

        novo->quant = 0;

        novo->prox = ini_p;
    }else{
        mostra_erro_e_encerra(ERRO_MEMORIA);
    }

    return novo;

}

//-----------------------------------------------------------
// Inicializa o programa com os dados dos arquivos (Produtos)
//-----------------------------------------------------------
Produtos *recuperaProdutos(Produtos *ini_p, long int codigo, char *descricao, float valor, int quant){
    Produtos *novo = (Produtos *)malloc(sizeof(Produtos));
    int i = 0;

    if(novo){
        novo->cod = codigo;
        novo->valor = valor;
        novo->quant = quant;

        for(i = 0; descricao[i]; i++)
            novo->descricao[i] = descricao[i];
        novo->descricao[i] = '\0';

        novo->prox = ini_p;

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
// Valida a descrição de um produto na hora da inserção
// em caso de nome repetido, solicita ao usuario um novo
// valor.
//--------------------------------------------------------
char* verificaDescricao(Produtos *ini_p, char *descricao){
    if(ini_p == NULL){
        return descricao;
    }

    int verificador;

    do{

        Produtos *aux = ini_p;
        verificador = 0;

        while(aux){
            if(strcmp(descricao, aux->descricao) == 0){
                 printf("\n\tA descrição já está em uso em outro produto. Tente novamente\n");
                 printf("\tNova Descrição: ");
                 scanf("%99[^\n]%*c", descricao);
                 verificador = 1;
                 break;
            }

            aux = aux->prox;
        }

    }while(verificador);

    return descricao;
}

//--------------------------------------------------------
// Procedimento para adicionar os itens de um produto ao
// estoque (recebe os valores para adição de itens)
//--------------------------------------------------------
Produtos* atualizaEstoqueAdd(Produtos *ini_produtos, int *confirma, int *quant_ad){
    long int auxCodigo = 0;

    printf("\n\tInforme o código do produto: ");
    printf("\n\tCódigo: "); scanf("%li%*c", &auxCodigo);
    Produtos *auxEstoque = encontraProduto(ini_produtos, auxCodigo);

    if(auxEstoque){
        printf("\n\tDescrição do produto: %s", auxEstoque->descricao);
        printf("\n\tQuantidade atual em estoque: %d\n", auxEstoque->quant);

        printf("\n\tDigite a quantidade a ser adicionada: ");
        scanf("%d%*c", quant_ad);

        printf("\n\tATENÇÃO: Confirme a operação.\n");
        printf("\tAperte 1 para prosseguir, 2 para cancelar a operação. ");
        scanf("%d%*c", confirma);

        return auxEstoque;
    }else{
        return NULL;
    }
}

//--------------------------------------------------------
// Adicionar itens (quantidade) a um produto em estoque
//--------------------------------------------------------
void adicionarItens(Produtos *produto, int quant){
    produto->quant += (produto->quant == -1) ? (quant + 1) : quant;
}

//--------------------------------------------------------
// Procedimento para excluir os itens de um produto em
// estoque (recebe os valores para exclusão de itens)
//--------------------------------------------------------
Produtos* atualizaEstoqueDel(Produtos *ini_p, int *confirma, int *quant_del){
    long int auxCodigo = 0;

    printf("\n\tInforme o código do produto: ");
    printf("\n\tCódigo: "); scanf("%li%*c", &auxCodigo);
    Produtos *auxEstoque = encontraProduto(ini_p, auxCodigo);

    if(auxEstoque){
        printf("\n\tDescrição do produto: %s", auxEstoque->descricao);
        printf("\n\tQuantidade atual em estoque: %d\n", auxEstoque->quant);

        printf("\n\tDigite a quantidade a ser excluida: ");
        scanf("%d%*c", quant_del);

        printf("\n\tATENÇÃO: Se o número a ser excluido for maior que o valor em estoque, \n\ta quantidade será zerada.");
        printf("\n\tConfirme a operação.\n");
        printf("\tAperte 1 para prosseguir, 2 para cancelar a operação. ");
        scanf("%d%*c", confirma);

        return auxEstoque;
    }else{
        return NULL;
    }
}
//--------------------------------------------------------
// Excluir itens (quantidade) de um produto em estoque
//--------------------------------------------------------
void excluirItens(Produtos *produto, int quant, int tipo_operacao){
    switch(tipo_operacao){
        case T_ESTOQUE:
            produto->quant = (quant > produto->quant) ? 0 : (produto->quant)-quant;
        break;

        case T_VENDAS:
            produto->quant = (quant > produto->quant) ? -1 : (produto->quant)-quant;
        break;
    }
}

//--------------------------------------------------------
// Mostra o preço de um produto para o usuario
//--------------------------------------------------------
void consultaPreco(Produtos *ini_p){
    long int auxCodigo = 0;

    printf("\n\tDigite o código do produto: ");
    scanf("%li%*c", &auxCodigo);

    Produtos *auxEstoque = encontraProduto(ini_p, auxCodigo);
    if(auxEstoque){
        printf("\n\tDescrição: %s", auxEstoque->descricao);
        printf("\n\tPREÇO: R$ %.2f\n", auxEstoque->valor);
        mensagem_final(FINALIZADA);
    }else{
        printf("\n\tProduto não cadastrado no sistema.\n");
        printf("\n\tRealize o cadastro do produto e tente novamente");
        mensagem_final(FALHOU);
    }
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

//--------------------------------------------------------
// Busca produtos com estoque irregular
//--------------------------------------------------------
int buscarEstoqueIrregular(Produtos *ini_p){
    Produtos *aux = ini_p;
    Produtos *avisos = NULL;
    int tam_p = 0;

    while(aux){
        if(aux->quant == -1){
            avisos = (Produtos *)realloc(avisos, (tam_p+1) * sizeof(Produtos));
            avisos[tam_p].cod = aux->cod;
            strcpy(avisos[tam_p].descricao, aux->descricao);
            avisos[tam_p].quant = aux->quant;
            avisos[tam_p].valor = aux->valor;

            tam_p++;
        }
        aux = aux->prox;
    }

    if(avisos == NULL) return 0;
    salvarAvisosEstoque(avisos, tam_p);
    return tam_p;
}

//--------------------------------------------------------
// Mostra na tela os avisos de irregularidade de estoque
//--------------------------------------------------------
void mostraAvisosEstoque(int tam_p){
    Produtos *a = lerArquivoAvisos(&tam_p);

    printf("\n\tATENÇÃO!! Os seguintes produtos tiveram saídas maiores do que \n\to registro de estoque no sistema.\n");
    printf("\n\tVerifique seu estoque.");
    printf("\n\tProdutos com estoque irregular: \n\n");
    for(int i = 0; i < tam_p; i++){
        printf("\t%li - %s - R$%.2f - (%d)\n", a[i].cod, a[i].descricao, a[i].valor, a[i].quant);
    }
    printf("\n\n");
}
