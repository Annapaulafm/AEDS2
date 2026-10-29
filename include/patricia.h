#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "livro.h"

#define B 6

typedef unsigned int Chave;

typedef enum
{
    PATRICIA_INTERNO,
    PATRICIA_EXTERNO
}patricia_tipo_no;

typedef struct patricia_no patricia_no;
typedef struct patricia patricia;

int patricia_bit(int i, Chave chave);
patricia *cria_patricia(void);
int inserir_patricia(patricia *arvore, Livro *livro);
Livro *buscar_patricia(patricia *arvore, Chave id);
int remover_patricia(patricia *arvore, Chave id);
void imprimir_patricia(patricia *arvore);
void destruir_patricia(patricia *arvore);

#endif