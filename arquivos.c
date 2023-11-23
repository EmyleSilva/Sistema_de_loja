#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "produtos.h"
#include "clientes.h"
#include "vendas.h"
#include "interface.h"
FILE *fp_p, *fp_c;


//********************************************
//   Funções para manipulações de clientes
//********************************************

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
    for(int i = 0; i < quantidade_p; i++){
        fscanf(fp_p, "%li\n", &(aux[i].cod));
        fgets(buffer, sizeof(buffer), fp_p);
        sscanf(buffer, "%99[^\n]", aux[i].descricao);
        fscanf(fp_p, "%f", &(aux[i].valor));
        fscanf(fp_p, "%d\n", &(aux[i].quant));
    }

    return aux;
}

//--------------------------------------------
// Salva os produtos existentes em um arquivo
//--------------------------------------------
void salvarProdutos(char *nomeArq, int quant_p, Produtos *ini_p){
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
}

//********************************************
//   Funções para manipulações de clientes
//********************************************
void salvarClientes(char *nomeArq, int quant_c, Clientes *ini_c){
    FILE *fp_c;
    Clientes *aux = ini_c;

    if((fp_c = fopen(nomeArq, "w")) == NULL){
        mostra_erro_e_encerra("\n\tErro Interno: Não foi possivel abrir o arquivo.");
    }

    fprintf(fp_c, "%d\n\n", quant_c);
    for(; aux != NULL ; aux = aux->prox){
        fprintf(fp_c, "%li\n", aux->codigo);
        fprintf(fp_c, "%s\n", aux->nome);
    }

    fclose(fp_c);
}

//----------------------------------------------------
// Inicializa os clientes
//----------------------------------------------------
Clientes* inicializaClientes(char *nomeArq, int *quant){
    Clientes *aux;
    Clientes *ini_c = NULL;
    int quantidade_c;

    fp_c = fopen(nomeArq, "r");
    if(fp_c != NULL) {
        fscanf(fp_p, "%d\n\n", &quantidade_c);
        fclose(fp_c);
        (*quant) = quantidade_c;
        aux = lerArquivosClientes(nomeArq, quantidade_c);
        ini_c = iniciaListaClientes(ini_c, aux, quantidade_c);
        fclose(fp_c);
        return ini_c;
    }
    return NULL;
}

//--------------------------------------------
// Lê as informações do arquivo de clientes
//--------------------------------------------
Clientes* lerArquivosClientes(char *nomeArq, int quantidade_c){
    Clientes *aux = (Clientes *)malloc((quantidade_c) * sizeof(Clientes));
    long int lixo;
    char buffer[100];

    if((fp_c = fopen(nomeArq, "r")) == NULL){
        mostra_erro_e_encerra("\n\tErro ao abrir arquivo.");
    }
    fscanf(fp_c, "%d\n\n", &lixo);
    for(int i = 0; i < quantidade_c; i++){
        fscanf(fp_p, "%li\n", &(aux[i].codigo));
        fgets(buffer, sizeof(buffer), fp_c);
        sscanf(buffer, "%199[^\n]", aux[i].nome);
    }

    return aux;
}

//------------------------------------------------------------
// Chama uma função de clientes que inicia a lista encadeada
// com os valores recuperados dos arquivos
//------------------------------------------------------------
Clientes *iniciaListaClientes(Clientes *ini_c, Clientes *aux, int quant){
    for(int i = quant-1; i >= 0; i--)
        ini_c = recuperaClientes(ini_c, aux[i].codigo, aux[i].nome);
    return ini_c;
}
