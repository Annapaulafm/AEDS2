#include "../include/biblioteca.h"

void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

//ADICIONA UM LIVRO NOVO AO ACERVO (PELO TECLADO)
int adicionar_livro(Livro *livro, patricia *arvore, int *proximoId){
    char linha[32];

    printf("Adicione um livro novo: \n");

    printf("Titulo: ");
    fgets(livro->titulo, M, stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(livro->autor, M, stdin);
    livro->autor[strcspn(livro->autor, "\n")] = '\0';

    printf("Ano de publicacao: ");
    scanf("%d", &livro->ano);
    /*fgets(linha, sizeof(linha), stdin);
    if (sscanf(linha, "%d", &livro->ano) != 1){
        printf("Ano invalido.\n");
        return 0;
    }*/

    printf("Quantidade de exemplares: ");
    scanf("%d", &livro->quantidade);
    /*fgets(linha, sizeof(linha), stdin);
    if(sscanf(linha, "%d", livro->quantidade) != 1){
        printf("Quantidade invalida. \n");
        return 0;
    }*/

    livro->total = livro->quantidade;

    livro->id = gerar_id(proximoId);
    return inserir_patricia(arvore, livro);
}

void listar_acervo(patricia *arvore){
    printf("====================== LIVROS NO ACERVO DA BIBLIOTECA ======================\n");
    imprimir_patricia(arvore);
}

//ALGUGAR LIVRO
int alugar_livro(patricia *arvore, Chave id){
    Livro *livro = buscar_patricia(arvore, id);

    //SE O LIVRO NÃO EXISTIR NO ACERVO DA BIBLIOTECA
    if(livro == NULL){
        printf("Livro nao existe no acervo. \n");
        return 0;
    }

    //SE LIVRO ESTIVER ESGOTADO
    if(!registrar_emprestimo(livro)){
        printf("Todas as copias deste livro ja foram alugadas. \n");
        return 0;
    }else{
        //LIVRO ALUGADO 
        printf("Livro alugado com sucesso!\n");
        imprimir_livro(livro);
        return 1;
    }
}

//DEVOLVER LIVRO
int devolver_livro(patricia *arvore, Chave id){
    Livro *livro = buscar_patricia(arvore, id);

    //SE O LIVRO NÃO EXISTIR NO ACERVO DA BIBLIOTECA
    if(livro == NULL){
        printf("Livro nao existe no acervo. \n");
        return 0;
    }

    //NÃO CONSEGUE RESGISTRAR A DEVOLUÇÃO
    if(!registrar_devolucao(livro)){
        printf("Nao foi possivel registrar a devolução. \n");
        return 0;
    }

    registrar_devolucao(livro);
    printf("Livro devolvido com sucesso!\n");
    imprimir_livro(livro);
    return 1;
}
