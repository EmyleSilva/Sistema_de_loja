/*
** Sistema criado para manutenção de um sistema de loja
** O sistema tem como funções: armazenar clientes, produtos
** e realizar vendas.
**
** última atualização: 29/11/2023
** Autor: Emyle Silva
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "produtos.h"
#include "vendas.h"
#include "arquivos.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    Produtos *ini_produtos = NULL;
    Vendas   *ini_vendas   = NULL;

    char nomeArq_p[20] = "produtos.txt";
    char nomeArq_v[20] = "vendas.txt";

    int opt_menu = 0, opt_p = 0, opt_v = 0, opt_e = 0;
    int quant_p = 0, quant_v = 0; //Controle de quantidadde para manipulação de arquivos.
    int aux = 0, confirma = 0;
    long int auxCodigo = 0;

    ini_produtos = inicializaProdutos(nomeArq_p, &quant_p);
    ini_vendas = inicializaVendas(&ini_vendas, &quant_v, nomeArq_v);

    //Variaveis para opções de menu
    char menuPrincipal[][50] = {"Produtos", "Vendas", "Encerrar"}; //3 opções
    char menuProdutos[][50] = {"Adicionar Produtos", "Estoque", "Retornar"};//3 opções
    char menuEstoque[][50] = {"Listar Produtos", "Adicionar Itens", "Excluir Itens", "Consultar Preço", "Retornar"}; //5 opções
    char menuVendas[][50] = {"Realizar Venda", "Listar Vendas" ,"Retornar"}; //3 opções

    //Inicio do menu
    do{
        limpaTela();
        menu(menuPrincipal, 3);
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
                        salvarProdutos(nomeArq_p, ++quant_p, ini_produtos);
                        mensagem_final(0);
                    break;

                    case 2: //MENU DE ESTOQUE
                        do{
                            limpaTela();
                            menu(menuEstoque, 5);
                            scanf("%d%*c", &opt_e);

                            switch(opt_e){
                                case 1: //Lista os produtos em estoque
                                    limpaTela();
                                    listarProdutos(ini_produtos);
                                    mensagem_final(0);
                                break;

                                case 2:{ //Adiciona itens ao estoque
                                    limpaTela();
                                    printf("\n\tInforme o código do produto: ");
                                    printf("\n\tCódigo: "); scanf("%li%*c", &auxCodigo);
                                    Produtos *auxEstoque = encontraProduto(ini_produtos, auxCodigo);

                                    if(auxEstoque){
                                        printf("\n\tDescrição do produto: %s", auxEstoque->descricao);
                                        printf("\n\tQuantidade atual em estoque: %d\n", auxEstoque->quant);

                                        printf("\n\tDigite a quantidade a ser adicionada: ");
                                        scanf("%d%*c", &aux);

                                        printf("\n\tATENÇÃO: Confirme a operação.\n");
                                        printf("\tAperte 1 para prosseguir, 2 para cancelar a operação. ");
                                        scanf("%d%*c", &confirma);

                                        if(confirma == 1) {
                                            adicionarItens(auxEstoque, aux);
                                            salvarProdutos(nomeArq_p, quant_p, ini_produtos);
                                            mensagem_final(0);
                                        }else{
                                            mensagem_final(1);
                                        }
                                    }else{
                                        printf("\n\tProduto não cadastrado no sistema.\n");
                                        printf("\n\tRealize o cadastro do produto e tente novamente");
                                        free(auxEstoque);
                                        mensagem_final(2);
                                    }
                                break;
                                }
                                case 3: {//Excluir itens do estoque
                                    limpaTela();
                                    printf("\n\tInforme o código do produto: ");
                                    printf("\n\tCódigo: "); scanf("%li%*c", &auxCodigo);
                                    Produtos *auxEstoque = encontraProduto(ini_produtos, auxCodigo);

                                    if(auxEstoque){
                                        printf("\n\tDescrição do produto: %s", auxEstoque->descricao);
                                        printf("\n\tQuantidade atual em estoque: %d\n", auxEstoque->quant);

                                        printf("\n\tDigite a quantidade a ser excluida: ");
                                        scanf("%d%*c", &aux);

                                        printf("\n\tATENÇÃO: Se o número a ser excluido for maior que o valor em estoque, \n\ta quantidade será zerada.");
                                        printf("\n\tConfirme a operação.\n");
                                        printf("\tAperte 1 para prosseguir, 2 para cancelar a operação. ");
                                        scanf("%d%*c", &confirma);

                                        if(confirma == 1) {
                                            excluirItens(auxEstoque, aux);
                                            salvarProdutos(nomeArq_p, quant_p, ini_produtos);
                                            mensagem_final(0);
                                        }else{
                                            mensagem_final(1);
                                        }
                                    }else{
                                        printf("\n\tProduto não cadastrado no sistema.\n");
                                        printf("\n\tRealize o cadastro do produto e tente novamente");
                                        free(auxEstoque);
                                        mensagem_final(2);
                                    }
                                break;
                                }
                                case 4://Consulta de preço (pelo código)
                                    limpaTela();
                                    consultaPreco(ini_produtos);
                                break;

                                case 5: //Retorna ao menu de produtos
                                    opt_e = 0;
                                break;

                                default:
                                    validacao_menu();
                                break;
                            }

                        }while(opt_e);
                    break;//FIM DO MENU DE ESTOQUE

                    case 3: //Retornar ao menu principal
                        opt_p = 0;
                    break;

                    default: //validação do menu de produtos
                        validacao_menu();
                    break;
                }
            }while(opt_p);

            break; //break case 1- menu principal

            case 2: //VENDAS

                do{
                    limpaTela();
                    menu(menuVendas, 3);
                    scanf("%d%*c", &opt_v);

                    switch(opt_v){
                        case 1:{
                            limpaTela();
                            float totalVenda = 0.0;
                            int quant_prod = 0;
                            Itens *nvenda = realizaVenda(ini_produtos, &totalVenda, &quant_prod);
                            ini_vendas = cadastraVenda(ini_vendas, nvenda, quant_prod ,totalVenda);
                            salvarVendas(nomeArq_v, ++quant_v, ini_vendas);
                            mensagem_final(0);
                            break;
                        }

                        case 2:
                            limpaTela();
                            listarVendas(ini_vendas);
                            mensagem_final(0);
                        break;

                        case 3:
                            opt_v = 0;
                        break;

                        default:
                            validacao_menu();
                        break;
                    }

                }while(opt_v);

            break;

            case 3: //ENCERRAR
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
