/*
** Sistema criado para manutenção de um sistema de loja
** O sistema tem como funções: armazenar clientes, produtos
** e realizar vendas.
**
** última atualização: 19/11/2023
** Autor: Emyle Silva
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Produtos *ini_produtos = inicializa_p();

    /*
    ** Verifica se existem dados já salvos em arquivos
    ** Abre os produos/clientes/vendas para visualização no sistema
    */


    //Variaveis para opções de menu
    char menuPrincipal[][50] = {"Produtos", "Clientes", "Vendas", "Encerrar"}; //4 opções
    char menuProdutos[][50] = {"Adicionar Produtos", "Estoque", "Retornar"};//3 opções

    //Variaveis gerais do menu
    int opt_menu = 0, opt_p = 0, opt_c = 0, opt_v = 0;
    int quant_p = 0, quant_c = 0, quant_v = 0; //Controle de quantidadde para manipulação de arquivos.

    //Inicio do menu
    do{
        limpaTela();
        menu(menuPrincipal, 4);
        scanf("%d%*c", &opt_menu);

        switch(opt_menu){
            case 1: //PRODUTOS

            //Menu de produtos
            do{
                limpaTela();
                menu(menuProdutos, 3);
                scanf("%d%*c", &opt_p);

                switch(opt_p){
                    case 1: //Adicionar produtos
                        limpaTela();
                        ini_produtos = insereProduto(ini_produtos);
                        mensagem_final(0);
                    break;

                    case 2: //Listar produtos em estoque
                        limpaTela();
                        listarProdutos(ini_produtos);
                        mensagem_final(0);
                    break;

                    case 3: //Retornar ao menu principal
                        opt_p = 0;
                    break;

                    default: //validação do menu de produtos
                        validacao_menu();
                    break;
                }
            }while(opt_p);

            break; //break case 1- menu principal

            case 2: //CLIENTES
            break;

            case 3: //VENDAS
            break;

            case 4: //ENCERRAR
                opt_menu = 0;
                finaliza_programa();
            break;

            default: //Validação do menu Principal
                validacao_menu();
            break;
        }
    }while(opt_menu);

    return 0;
}
