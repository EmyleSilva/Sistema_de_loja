#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "interface.h"

//-------------------------------------------
// Adiciona um clientes
//-------------------------------------------
Clientes* adicionaCliente(Clientes *ini_c){
    Clientes *novo = (Clientes *)malloc(sizeof(Clientes));
    char nome[200];

    if(novo){
        novo->codigo = defineCodigoCliente(ini_c);

        printf("\n\tDigite o nome do cliente: ");
        scanf("%199[^\n]%*c", &nome);

        strcpy(novo->nome, verificaNome(ini_c, nome));

        novo->prox = ini_c;

    }else{
        mostra_erro_e_encerra("Erro Interno: Memoria insuficiente");
    }

    return novo;
}

//-------------------------------------------
// Gera um código aleatório para cliente
//-------------------------------------------
long int geraCodigoCliente(){
    return 1000+(rand()%1000);
}

//-------------------------------------------
// Verifica se o código gerado é válido
//-------------------------------------------
long int defineCodigoCliente(Clientes *ini_c){
    long int codigo = geraCodigoCliente();
    Clientes *aux = encontraCliente(ini_c, codigo);

    while(aux != NULL){
        codigo = geraCodigoCliente();
        aux = encontraCliente(ini_c, codigo);
    }
    return codigo;
}

//-------------------------------------------
// Busca um cliente através de um código e
// o retorna, caso não encontre, retorna NULL
//-------------------------------------------
Clientes *encontraCliente(Clientes *ini_c, long int codigo){
    Clientes *aux = ini_c;

    if(aux == NULL) return NULL;

    while(aux->prox != NULL && aux->codigo != codigo){
        aux = aux->prox;
    }

    if(aux->codigo == codigo)return aux;
    return NULL;
}

//-------------------------------------------
// Verifica se um cliente com mesmo nome já
// foi cadastrado no sistema.
//-------------------------------------------
char* verificaNome(Clientes *ini_c, char *nome){
    if(ini_c == NULL){
        return nome;
    }

    int verificador;

    do{

        Clientes *aux = ini_c;
        verificador = 0;

        while(aux){
            if(strcmp(nome, aux->nome) == 0){
                 printf("\n\tO cliente já está cadastrado. Tente Novamente\n");
                 printf("\tNome: ");
                 scanf("%199[^\n]%*c", nome);
                 verificador = 1;
                 break;
            }

            aux = aux->prox;
        }

    }while(verificador);

    return nome;
}

//-----------------------------------------------------------
// Inicializa o programa com os dados dos arquivos (Clientes)
//-----------------------------------------------------------
Clientes *recuperaClientes(Clientes *ini_c, long int codigo, char *nome){
    Clientes *novo = (Clientes *)malloc(sizeof(Clientes));
    int i = 0;

    if(novo){
        novo->codigo = codigo;

        for(i = 0; nome[i]; i++)
            novo->nome[i] = nome[i];
        novo->nome[i] = '\0';

        novo->prox = ini_c;

    }

    return novo;
}

//--------------------------------------------------------
// Lista todos os produtos registrados
//--------------------------------------------------------
void listarClientes(Clientes *ini_c){
    Clientes *aux = ini_c;
    int cont = 0;
    if(ini_c){
        for(; aux; aux=aux->prox){
            cont++;
            printf("\n\t-------------------- Produto %d --------------------\n", cont);
            printf("\tCódigo: %li\n", aux->codigo);
            printf("\tNome: %s\n", aux->nome);
        }
    }
    printf("\n\t%d Clientes encontrados.\n", cont);
}




