/**
* @file interface.h
* @brief Declaração das funções de interface.
*
*/

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

/**
* @brief Definição de status de operação
*
* A constante FINALIZADA define o status de uma operação que
* ocorreu de acordo com o fluxo esperado, sem nenhuma falha ou
* cancelamento.
*
*/
#define FINALIZADA 0

/**
* @brief Definição de status de operação
*
* A constante CANCELADA define o status de uma operação
* que foi cancelada pelo usuário.
*
*/
#define CANCELADA 1

/**
* @brief Definição de status de operação
*
* A constante FALHOU define o status de uma operação que
* foi cancelada devido a algum erro.
*
*/
#define FALHOU 2

/**
* @brief Definição de tipo de erro
*
* ERRO_MEMORIA mostra ao usuário quando o programa é
* encerrado devido a um erro relacionado a falta de memória,
* geralmente, chamada quando ocorre erro de alocação.
*
*/
#define ERRO_MEMORIA "Erro Interno: Memoria Insuficiente"

/**
* @brief Definição de tipo de erro
*
* ERRO_ARQ_R mostra ao usuário quando o programa é
* encerrado devido a um erro ao abrir um arquivo para leitura.
*
*/
#define ERRO_ARQ_R "Erro Interno: Erro ao abrir arquivo para leitura"

/**
* @brief Definição de tipo de erro
*
* ERRO_ARQ_W mostra ao usuário quando o programa é
* encerrado devido a um erro ao abrir/gerar um arquivo para escrita.
*
*/
#define ERRO_ARQ_W "Erro Interno: Erro ao abrir arquivo"

/**
* @brief Exibe um menu para o usuário.
*
* @param opcoes Vetor de strings com as opções do menu.
* @param quant Quantidade de opções que o menu possui.
*/
void menu(char opcoes[][50], int quant);

/**
* @brief Exibe o titulo da sessão em que o usuário se encontra
*
* @param titulos String para o titulo a ser exibido.
*
*/
void titulo(char titulos[]);

/**
* @brief Exibe na tela uma mensagem de erro e encerra o programa
*
* Quando um erro interno ocorre (ERRO_MEMORIA, ERRO_ARQ_W, ERRO_ARQ_R),
* e o programa precisa ser encerrado, o usuário é informado sobre o tipo
* de erro que aconteceu,e logo após o programa é finalizado.
*
* @param tipo Indica qual tipo de erro ocorreu.
*/
void mostra_erro_e_encerra(char tipo[]);

/**
* @brief Exibe uma mensagem no fim de cada operação informando o status final
*
* Informa ao usuario se a operação foi finalizada com sucesso (constante FINALIZADA)
* se a operação foi cancelada (constante CANCELADA) ou ainda se a operação falhou
* (constante FALHOU).
*
* @param status_operacao Constante que indica o status final da operação.
*
*/
void mensagem_final(int status_operacao);

/**
* @brief Exibe um alerta de validação para o menu.
*
* Quando o usuário seleciona uma opção que não existe no menu, a mensagem
* é mostrada informando ao usuário que uma opção válida precisa ser selecionada.
*
*/
void validacao_menu();

/**
* @brief Mostra mensagem de finalização e sai do programa.
*
*/
void finaliza_programa();

/**
* @brief Limpa a tela.
*
*/
void limpaTela();

#endif // INTERFACE_H_INCLUDEDE
