#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include "interface.h"

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
    //char aux[100];

    if(novo){
        novo->cod = defineCodigoProd(ini_p);
        //novo->cod = 1;
        printf("\n\tInforme o nome do produto: ");
        scanf("%99[^\n]%*c", novo->descricao);

        //verificaDescricao(ini_p, aux, &novo->descricao);

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
/*char* verificaDescricao(Produtos *ini_p, char *descricao, char *nova_descricao){
    if(ini_p == NULL){
        int i = 0;
        for(i = 0; descricao[i]; i++)
            (*nova_descricao[i]) = descricao[i];
       (*nova_descricao[i]) = '\0';

        return;
    }
    int verificador = 1;
    Produtos *aux = ini_p;
    do{
        while(aux){
            verificador = 1;
            for(int i = 0; descricao[i]; i++){
                if(descricao[i] != aux->descricao[i]){
                    verificador*=0;
                    break;
                }
            }
            if(!verificador){
            int i = 0;

            for(i = 0; descricao[i]; i++)
                (*nova_descricao[i]) = descricao[i];
            (*nova_descricao[i]) = '\0';

            return;
            }

            printf("\n\tA descrição já está em uso em outro produto. Tente novamente\n");
            printf("\tNova Descrição: "); scanf("%99[^\n]%*c", descricao);
            aux = aux->prox;
        }
    }while(verificador);
}*/

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



