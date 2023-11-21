#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"
#include "interface.h"
FILE *fp_p;

//----------------------------------------------------
// Inicializa os produtos
//----------------------------------------------------
Produtos* inicializaProdutos(char *nomeArq, int *quant){
    Produtos *aux;
    Produtos *ini_p = NULL;
    int quantidade_p;

    fp_p = fopen(nomeArq, "r");
    if(fp_p != NULL) {
        fscanf(fp_p, "%d\n\n", &quantidade_p);
        fclose(fp_p);
        (*quant) = quantidade_p;
        //printf("quantidade p: %d\n", quantidade_p);
        aux = lerArquivosProdutos(nomeArq, quantidade_p);
        ini_p = iniciaListaProd(ini_p, aux, quantidade_p);
        fclose(fp_p);
        return ini_p;
    }
    return NULL;
}

//------------------------------------------------------------
// Chama uma função de produtos que inicia a lista encadeada
// com os valores recuperados dos arquivos
//------------------------------------------------------------
Produtos *iniciaListaProd(Produtos *ini_prod, Produtos *aux, int quant){
    for(int i = quant-1; i >= 0; i--)
        ini_prod = recuperaProdutos(ini_prod, aux[i].cod, aux[i].descricao, aux[i].valor, aux[i].quant);
    return ini_prod;
}

//--------------------------------------------
// Lê as informações do arquivo de produtos
//--------------------------------------------
Produtos* lerArquivosProdutos(char *nomeArq, int quantidade_p){
    Produtos *aux = (Produtos *)malloc((quantidade_p) * sizeof(Produtos));
    long int lixo;
    char buffer[100];

    if((fp_p = fopen(nomeArq, "r")) == NULL){
        mostra_erro_e_encerra("\n\tErro ao abrir arquivo.");
    }
    fscanf(fp_p, "%d\n\n", &lixo);
    //printf("lixo: %d\n", lixo);
    for(int i = 0; i < quantidade_p; i++){
        fscanf(fp_p, "%li\n", &(aux[i].cod));
       // printf("codigo[%d]: %li\n", i, aux[i].cod);
        fgets(buffer, sizeof(buffer), fp_p);
        sscanf(buffer, "%99[^\n]", aux[i].descricao);
        //printf("descricao[%d]: %s\n", i, aux[i].descricao);
        fscanf(fp_p, "%f", &(aux[i].valor));
        //printf("valor[%d]: %.2f\n", i, aux[i].valor);
        fscanf(fp_p, "%d\n", &(aux[i].quant));
        //printf("quant[%d]: %d\n", i, aux[i].quant);
    }

    return aux;
}

//--------------------------------------------
// Salva os produtos existentes em um arquivo
//--------------------------------------------
FILE* salvarProdutos(char *nomeArq, int quant_p, Produtos *ini_p){
    FILE *fp_p;
    Produtos *aux = ini_p;

    if((fp_p = fopen(nomeArq, "w")) == NULL){
        mostra_erro_e_encerra("Erro Interno: O arquivo não pode ser aberto.");
    }

    fprintf(fp_p, "%d\n\n", quant_p);
    for(; aux != NULL ; aux = aux->prox){
        fprintf(fp_p, "%li\n", aux->cod);
        fprintf(fp_p, "%s\n", aux->descricao);
        fprintf(fp_p, "%.2f\n", aux->valor);
        fprintf(fp_p, "%d\n", aux->quant);
    }

    fclose(fp_p);

    return fp_p;
}

