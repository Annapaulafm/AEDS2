#include "../include/patricia.h"
#include "../include/biblioteca.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
    //CRIA A ÁRVORE E OUTRAS VARIAVEIS
    patricia *arvore = cria_patricia();
    int id = 1;     
    int idAD;
    Livro livro;

    //ABRE O ARQUIVO LIVROS.TX
    FILE *arq = fopen("data/livros.txt", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    
    //INSERE OS LIVROS DO ARQUIVO NA PATRICIA
    while(criar_livro(arq, &livro, &id)){
        inserir_patricia(arvore, &livro);
    }

    //MENU
    int opcao;
    do{
        imprimir_menu();
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        //ADICIONA LIVRO NOVO AO ACERVO DA BIBLIOTECA 
        case CADASTRAR_LIVRO:
            adicionar_livro(&livro, arvore, &id);
            printf(" %d | %s | %s | %d | %d | %d\n", livro.id, livro.titulo, livro.autor, livro.ano, livro.quantidade, livro.total);
            break;
        //IMPRIMI TODOS OS LIVROS DO ACERVO
        case LISTAR_ACERVO:
            listar_acervo(arvore);
            break;;
        //ALUGAR LIVRO
        case ALUGAR_LIVRO:
            printf("Informe o id do livro que deseja alugar: ");
            scanf("%d", &idAD);
            alugar_livro(arvore, idAD);
            break;
        //DEVOLVER LIVRO
        case DEVOLVER_LIVRO:
            printf("Informe o id do livro que deseja devolver: ");
            scanf("%d", &idAD);
            devolver_livro(arvore, idAD);
            break;
        }
    }while (opcao != SAIR); 
    
    //FECHA ARQUIVO
    fclose(arq);

    //DESTROI ÁRVORE
    destruir_patricia(arvore);

    return 0;
}