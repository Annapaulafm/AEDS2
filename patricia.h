#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>


#define M 100
#define B 6

typedef unsigned int Chave;

//ESTRUTURA DE LIVRO
typedef struct Livro
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
void imprimir_livro(Livro *livro);
int atualizar_quantidade(Livro *livro, int nova_qtd);
int registrar_emprestimo(Livro *livro);
int registrar_devolucao(Livro *livro);

//FUNÇÕES PATRICIA
int patricia_bit(int i, Chave chave);
patricia *cria_patricia(void);
int inserir_patricia(patricia *arvore, Livro *livro);
Livro *buscar_patricia(patricia *arvore, Chave id);
int remover_patricia(patricia *arvore, Chave id);
void imprimir_patricia(patricia *arvore);
void destruir_patricia(patricia *arvore);

#endif