#ifndef INTERFACE_H_INCLUDEDE
#define INTERFACE_H_INCLUDEDE

/*
** Defines usados nas mensagens finais das operações
** indicando se a operação foi finalizada corretamente,
** se a ação foi cancelada pelo usuário, ou se houve alguma
** falha durante a execução
*/
#define FINALIZADA 0
#define CANCELADA 1
#define FALHOU 2

/*
** Defines usados para indicar erros que forçam a
** interrupção do programa.
*/
#define ERRO_MEMORIA "Erro Interno: Memoria Insuficiente"
#define ERRO_ARQ_R "Erro Interno: Erro ao abrir arquivo para leitura"
#define ERRO_ARQ_W "Erro Interno: Erro ao abrir arquivo"

//----------------------------------------------------------------------------
//Exibe um menu na tela
//----------------------------------------------------------------------------
void menu(char opcoes[][50], int quant);

//----------------------------------------------------------------------------
// Exibe na tela os títulos das funções
//----------------------------------------------------------------------------
void titulo(char titulos[]);

//----------------------------------------------------------------------------
//Exibe na tela uma mensagem especificando um erro, e encerra o programa
//----------------------------------------------------------------------------
void mostra_erro_e_encerra(char tipo[]);

//----------------------------------------------------------------------------
//Exibe uma mensagem informando o status da operação, se foi finalizada,
//cancelada ou ainda se falhou.
//----------------------------------------------------------------------------
void mensagem_final(int status_operação);

//----------------------------------------------------------------------------
//Exibe uma mensagem quando o usuário seleciona uma opção que não existe
//no menu.
//----------------------------------------------------------------------------
void validacao_menu();

//----------------------------------------------------------------------------
//Exibe na tela uma mensagem de confirmação da finalização, e
//encerra o programa.
//----------------------------------------------------------------------------
void finaliza_programa();

//----------------------------------------------------------------------------
//Limpa a tela
//----------------------------------------------------------------------------
void limpaTela();

#endif // INTERFACE_H_INCLUDEDE
