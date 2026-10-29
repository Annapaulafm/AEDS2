#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 100

typedef struct Livro
{
    int id;
    char titulo[M];
    char autor[M];
    int ano;             //ANO DA PUBLICAÇÃO
    int quantidade;     //QUANTIDADE DISPONÍVEL EM ESTOQUE
    int total;          //QUANTOS LIVROS EXISTEM NO ESTOQUE
}Livro;

int gerar_id(int *proximoId);
int criar_livro(FILE *arq, Livro *livro, int *proximoId);
void imprimir_livro(Livro *livro);
int registrar_emprestimo(Livro *livro);
int registrar_devolucao(Livro* livro);

#endif