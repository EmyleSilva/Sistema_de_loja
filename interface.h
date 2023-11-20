#ifndef INTERFACE_H_INCLUDEDE
#define INTERFACE_H_INCLUDEDE

//----------------------------------------------------------------------------
//Exibe um menu na tela
//----------------------------------------------------------------------------
void menu(char opcoes[][50], int quant);
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
