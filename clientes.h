#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct clientes{
    long int codigo;
    char nome[200];
    struct clientes *prox;
}Clientes;

/*
** Cria um cliente
*/
Clientes* adicionaCliente(Clientes *ini_c);

/*
** Gera um código aleatório
*/
long int geraCodigoCliente();

/*
** Define um código para o cliente
*/
long int defineCodigoCliente(Clientes *ini_c);

/*
** Busca um cliente na lista
*/
Clientes *encontraCliente(Clientes *ini_c, long int codigo);

/*
** Verifica se o nome digitado já está no sistema
*/
char* verificaNome(Clientes *ini_c, char *nome);

/*
** Função que recupera clientes dos arquivos e cria lista encadeada
*/
Clientes *recuperaClientes(Clientes *ini_c, long int codigo, char *nome);


/*
** Lista os clientes cadastrados
*/
void listarClientes(Clientes *ini_c);

#endif // CLIENTES_H_INCLUDED
