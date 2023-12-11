/**
* @file interface.c
* @brief Implementação das funções de interface.
* @see interface.h
*
*/

#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

//----------------------------------------------------------------------------
//Exibe um menu na tela
//----------------------------------------------------------------------------
void menu(char opcoes[][50], int quant){
    for(int i = 0; i < quant; i++){
        printf("\n\t%d - %s\n", i+1, opcoes[i]);
    }
    printf("\n\tOPÇÃO: ");
}

//----------------------------------------------------------------------------
// Exibe na tela os títulos das funções
//----------------------------------------------------------------------------
void titulo(char titulos[]){
    printf("\n\n\t *************************** %s *************************** \n\n", titulos);
}

//----------------------------------------------------------------------------
//Limpa a tela
//----------------------------------------------------------------------------
void limpaTela(){
    system("clear || cls");
}

//----------------------------------------------------------------------------
//Exibe na tela uma mensagem especificando um erro, e encerra o programa
//----------------------------------------------------------------------------
void mostra_erro_e_encerra(char tipo[]){
    printf("\n\t%s", tipo);
    exit(1);
}

//----------------------------------------------------------------------------
//Exibe uma mensagem informando o status da operação, se foi finalizada,
//cancelada ou ainda se falhou.
//----------------------------------------------------------------------------
void mensagem_final(int status_operação){
    //0 - Finalizada
    //1 - Cancelada
    //2 - Falhou
    if(status_operação == FINALIZADA){
        printf("\n\t\t============================================================\n");
        printf("\n\t\t|                                                          |\n");
        printf("\n\t\t|                Operação Finalizada                       |\n");
        printf("\n\t\t|                Aperte ENTER para continuar....           |\n");
        printf("\n\t\t|                                                          |\n");
        printf("\n\t\t============================================================\n\n");
    }else if(status_operação == CANCELADA){
        printf("\n\t\t============================================================\n");
        printf("\n\t\t|                                                          |\n");
        printf("\n\t\t|                Operação Cancelada                        |\n");
        printf("\n\t\t|                Aperte ENTER para continuar....           |\n");
        printf("\n\t\t|                                                          |\n");
        printf("\n\t\t============================================================\n\n");
    }else{
        printf("\n\t\t============================================================\n");
        printf("\n\t\t|                                                          |\n");
        printf("\n\t\t|                Operação Falhou                           |\n");
        printf("\n\t\t|                Aperte ENTER para continuar....           |\n");
        printf("\n\t\t|                                                          |\n");
        printf("\n\t\t============================================================\n\n");
    }
    scanf("%*c");
    system("clear || cls");
}

//----------------------------------------------------------------------------
//Exibe uma mensagem quando o usuário seleciona uma opção que não existe
//no menu.
//----------------------------------------------------------------------------
void validacao_menu(){
    system("clear || cls");
    printf("\n\t\t============================================================\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|               ERRO: OPÇÃO INEXISTENTE!                   |\n");
    printf("\t\t|                     Tente Novamente                      |\n");
    printf("\t\t|               Aperte ENTER para continuar....            |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t============================================================\n\n");
    scanf("%*c");
    system("clear || cls");
}


//----------------------------------------------------------------------------
//Exibe na tela uma mensagem de confirmação da finalização, e
//encerra o programa.
//----------------------------------------------------------------------------
void finaliza_programa(){
    system("clear || cls");
    printf("\n\t\t============================================================\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t|                     Programa Finalizado!                 |\n");
    printf("\t\t|                                                          |\n");
    printf("\t\t============================================================\n\n");
    exit(1);
}

