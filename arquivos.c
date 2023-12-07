#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "produtos.h"
#include "vendas.h"
#include "interface.h"
FILE *fp_p;

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
    fscanf(fp_p, "%li\n\n", &lixo);
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
//   Funções para manipulações de vendas
//********************************************
void salvarVendas(char *nomeArq, int quant_v, Vendas *ini_v){
    FILE *fp_v;
    Vendas *aux = ini_v;

    if((fp_v = fopen(nomeArq, "wb"))==NULL){
        mostra_erro_e_encerra("Erro Interno: o arquivo não pode ser aberto.");
    }
    fwrite(&quant_v, sizeof(int), 1, fp_v);
    while(aux){
        fwrite(&aux->codigo, sizeof(long int), 1, fp_v);
        fwrite(&aux->tamItem, sizeof(int), 1, fp_v);

        for(int i = 0; i < aux->tamItem; i++){
            fwrite(&aux->item[i], sizeof(Itens), 1, fp_v);
        }

        fwrite(&aux->dia, sizeof(int), 1, fp_v);
        fwrite(&aux->mes, sizeof(int), 1, fp_v);
        fwrite(&aux->ano, sizeof(int), 1, fp_v);
        fwrite(&aux->hora, sizeof(int), 1, fp_v);
        fwrite(&aux->minutos, sizeof(int), 1, fp_v);
        fwrite(&aux->segundos, sizeof(int), 1, fp_v);
        fwrite(&aux->total, sizeof(float), 1, fp_v);
        aux = aux->prox;
    }
    fclose(fp_v);
}

Vendas* inicializaVendas(Vendas **ini_v, int *quant_v, char *nomeArq){
    FILE *fp_v = fopen(nomeArq, "rb");

    if(fp_v != NULL){

        fread(quant_v, sizeof(int), 1, fp_v);
        int quantidade = (*quant_v);

        while(quantidade){
            Vendas *novo = (Vendas *)malloc(sizeof(Vendas));
            if(novo){
                fread(&novo->codigo, sizeof(long int), 1, fp_v);
                fread(&novo->tamItem, sizeof(int), 1, fp_v);
                novo->item = (Itens *)malloc(novo->tamItem * sizeof(Itens));
                for(int i = 0; i < novo->tamItem; i++){
                    fread(&novo->item[i], sizeof(Itens), 1, fp_v);
                }
                fread(&novo->dia, sizeof(int), 1, fp_v);
                fread(&novo->mes, sizeof(int), 1, fp_v);
                fread(&novo->ano, sizeof(int), 1, fp_v);
                fread(&novo->hora, sizeof(int), 1, fp_v);
                fread(&novo->minutos, sizeof(int), 1, fp_v);
                fread(&novo->segundos, sizeof(int), 1, fp_v);
                fread(&novo->total, sizeof(float), 1, fp_v);

                novo->prox = *ini_v;
                *ini_v = novo;
                quantidade--;
            }else{
                mostra_erro_e_encerra("Erro Interno: Memória Insuficiente");
            }
        }
        fclose(fp_v);
        return *ini_v;
    }
    return NULL;
}


//********************************************
//   Funções para manipulações de relatorios
//********************************************

//--------------------------------------------
// Gera e salva o relatório de faturamento do
// mês
//--------------------------------------------
void salvarRelatorio(char *nomeArq, Vendas *r, int tamV, float total_periodo, int mes){
    FILE *fp;

    if((fp = fopen(nomeArq, "w")) == NULL){
        mostra_erro_e_encerra("Erro Interno: Erro ao criar arquivo.");
    }

    fprintf(fp, "Relatório de Faturamento mensal -> Mês: %d\n\n", mes);
    fprintf(fp, "Total de vendas do mês: %d\n", tamV);
    fprintf(fp, "Codigo Venda \t\tData e hora \t\tValor Venda\n");
    for(int i = 0; i < tamV; i++){
        fprintf(fp, "%d \t\t%d/%d/%d %d:%d:%d \t\t%.2f\n", r[i].codigo, r[i].dia, r[i].mes, r[i].ano, r[i].hora,
                r[i].minutos, r[i].segundos, r[i].total);
    }
    fprintf(fp, "Faturamento do mês: %.2f\n\n", total_periodo);

    fclose(fp);
}

//--------------------------------------------
// Lê o arquivo do faturamento do mes
//--------------------------------------------
Vendas* lerArquivoRelatorio(char *nomeArq, int *tamV, float *total_periodo){
    FILE *fp;

    if((fp = fopen(nomeArq, "r")) == NULL){
        mostra_erro_e_encerra("Erro Interno: Não foi possivel abrir o arquivo de leitura.");
    }

    int mes;

    fscanf(fp, "Relatório de Faturamento mensal -> Mês: %d\n\n", &mes);
    fscanf(fp, "Total de vendas do mês: %d\n", tamV);

    Vendas *r = (Vendas *)malloc((*tamV) * sizeof(Vendas));

    fscanf(fp, "Codigo Venda \t\tData e hora \t\tValor Venda\n");
    for(int i = 0; i < (*tamV); i++){
        fscanf(fp, "%d \t\t%d/%d/%d %d:%d:%d \t\t%f\n", &r[i].codigo, &r[i].dia, &r[i].mes, &r[i].ano, &r[i].hora,
                &r[i].minutos, &r[i].segundos, &r[i].total);
    }
    fscanf(fp, "Faturamento do mês: %f\n\n", total_periodo);

    fclose(fp);
    return r;
}

//--------------------------------------------
// Salva os avisos de irrgularidade de estoque
//--------------------------------------------
void salvarAvisosEstoque(Produtos *avisos, int tam_p){
    FILE *fp;

    if((fp = fopen("avisos.txt", "wb")) == NULL){
        mostra_erro_e_encerra("Erro Interno: Erro ao abrir arquivo.");
    }

    fwrite(&tam_p, sizeof(int), 1, fp);
    fwrite(avisos, sizeof(Produtos), tam_p, fp);

    fclose(fp);
}

//--------------------------------------------
// Lê e retorna os avisos salvos no arquivo
//--------------------------------------------
Produtos* lerArquivoAvisos(int *tam_p){
    FILE *fp = fopen("avisos.txt", "rb");

    if(fp){

        fread(tam_p, sizeof(int), 1, fp);
        Produtos *avisos = (Produtos *)malloc((*tam_p) * sizeof(Produtos));
        fread(avisos, sizeof(Produtos), (*tam_p), fp);
        fclose(fp);
        return avisos;
    }

    return NULL;
}



