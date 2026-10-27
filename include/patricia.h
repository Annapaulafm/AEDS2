#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>


#define M 100
#define B 6

typedef unsigned int Chave;

//ESTRUTURA DE LIVRO
typedef struct livro
{
    int id;
    char titulo[M];
    char autor[M];
    int ano;    //ANO DA PUBLICAÇÃO
    int quantidade;     //QUANTIDADE EM ESTOQUE
}Livro;

typedef enum
{
    PATRICIA_INTERNO,
    PATRICIA_EXTERNO
}patricia_tipo_no;

typedef struct patricia_no patricia_no;
typedef struct patricia patricia;

//FUNÇÕES LIVRO
int criar_livro(FILE *arq, Livro *livro);

//FUNÇÕES PATRICIA
#endif