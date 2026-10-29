#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>

#include "patricia.h"

enum menu_opcoes{
    SAIR = 0,
    CADASTRAR_LIVRO,
    LISTAR_ACERVO,
    ALUGAR_LIVRO,
    DEVOLVER_LIVRO
};

static void imprimir_menu(void)
{
    printf("\n");
    printf("================================\n");
    printf("          BIBLIOTECA\n");
    printf("================================\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Listar acervo\n");
    printf("3 - Alugar livro\n");
    printf("4 - Devolver livro\n");
    printf("0 - Sair\n");
    printf("================================\n");
    printf("Opcao: ");
}

void limpar_buffer(void);
int adicionar_livro(Livro *livro, patricia *arvore, int *proximoId);
void listar_acervo(patricia *arvore);
int alugar_livro(patricia *arvore, Chave id);
int devolver_livro(patricia *arvore, Chave id);

//CADASTRO DE CLIENTE 
//LIMITE DE LIVROS ALUGADOS POR CLIENTE

#endif