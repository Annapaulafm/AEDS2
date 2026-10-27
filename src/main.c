#include "../include/patricia.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    //ABRE O ARQUIVO LIVROS.TX
    FILE *arq = fopen("data/livros.txt", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    
    //CRIA LIVROS
    Livro livro;
    while(criar_livro(arq, &livro)){
        printf("%d | %s | %s | %d | %d\n",livro.id, livro.titulo, livro.autor, livro.ano, livro.quantidade);
    }

    fclose(arq);
    return 0;
}