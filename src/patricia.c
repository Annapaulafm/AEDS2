#include "../include/patricia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

_Static_assert(B > 0, "D deve ser positivo");
_Static_assert(
    B <= (int)(sizeof(Chave) * CHAR_BIT),
    "D nao pode exceder o numero de bits de chave_t"
);
//================================== IMPLEMENTAÇÃO FUNÇÕES DE LIVRO =============================================================

//LÊ O ARQUIVO LIVROS.TXT E CRIA OS LIVROS
int criar_livro(FILE *arq, Livro *livro){
    //GUARDA A LINHA LIDA DO ARQUIVO
    char linha[2 * M + 64]; 

    if (fgets(linha, sizeof(linha), arq) == NULL){
        return 0;
    }

    // TIRA O \N
    linha[strcspn(linha, "\r\n")] = '\0';

    int lidos = sscanf(linha, "%99[^;];%99[^;];%d;%d",livro->titulo, livro->autor,&livro->ano, &livro->quantidade);

    return lidos == 4;
}


//================================== IMPLEMENTAÇÃO FUNÇÕES PATRICIA =============================================================

struct patrica_no{
    patricia_tipo_no tipo;
    union {
        struct{
            //NÓ INTERNO
            int indice;
            patricia_no *esq;
            patricia_no *dir;
        }interno;
        struct{
            //NÓ EXTERNO
            Chave chave;
        }externo;
    }dados; 
};

struct patricia{
    patricia *raiz;
    size_t tamanho;
};




