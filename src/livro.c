#include "../include/livro.h"

int gerar_id(int *proximoId){
    return (*proximoId) ++;
}

//LÊ O ARQUIVO LIVROS.TXT E CRIA OS LIVROS
int criar_livro(FILE *arq, Livro *livro, int *proximoId){
    //GUARDA A LINHA LIDA DO ARQUIVO
    char linha[2 * M + 64];

    if (fgets(linha, sizeof(linha), arq) == NULL)
    {
        return 0;
    }

    //TIRA O \N
    linha[strcspn(linha, "\r\n")] = '\0';

    
    int lidos = sscanf(linha, "%99[^;];%99[^;];%d;%d;%d", livro->titulo, livro->autor, &livro->ano, &livro->quantidade, &livro->total);

    livro->id = gerar_id(proximoId);

    return lidos == 5;
}

void imprimir_livro(Livro *livro){
    printf(" %d | %s | %s | %d | %d | %d\n", livro->id, livro->titulo, livro->autor, livro->ano, livro->quantidade, livro->total);
}

//SE PEGAR EMPRESTADO QUANTIDADE DIMINUI 1
int registrar_emprestimo(Livro *livro){
    //SE TIVER LIVRO DISPONÍVEL RETORNA 1
    if(livro->quantidade > 0){
        livro->quantidade --;
        return 1;
    }else{
        //SE NÃO TIVER LIVRO DINSPONÍVEL RETORNA 0
        return 0;
    }
}

//SE DEVOLVER QUANTIDADDE AUMENTA 1
int registrar_devolucao(Livro* livro){
    //JA DEVOLVEU TODOS OS LIVROS
    if(livro->quantidade >= livro->total){
        return 0;
    }else{
        livro->quantidade ++;
        return 1;
    }
}