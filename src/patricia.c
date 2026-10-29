#include "../include/patricia.h"

_Static_assert(B > 0, "D deve ser positivo");
_Static_assert(
    B <= (int)(sizeof(Chave) * CHAR_BIT),
    "D nao pode exceder o numero de bits de chave_t");

struct patricia_no
{
    patricia_tipo_no tipo;
    union
    {
        struct
        {
            // NÓ INTERNO
            int indice;
            patricia_no *esq;
            patricia_no *dir;
        } interno;
        struct
        {
            // NÓ EXTERNO
            Livro livro;
        } externo;
    } dados;
};

struct patricia
{
    patricia_no *raiz;
    size_t tamanho;
};

static int chave_valida(Chave chave)
{
    const int largura = (int)(sizeof(Chave) * CHAR_BIT);
    if (B == largura)
        return 1;
    return chave <= (UINT_MAX >> (largura - B));
}

int patricia_bit(int i, Chave chave)
{
    return (chave >> (B - i)) & 1u;
}

//CRIA UMA FOLHA QUE ARMAZENA UM LIVRO COMPLETO
static patricia_no *cria_no_externo(const Livro *livro)
{
    patricia_no *novo = malloc(sizeof(patricia_no));
    if (novo == NULL)
    {
        return NULL;
    }
    novo->tipo = PATRICIA_EXTERNO;
    novo->dados.externo.livro = *livro;
    return novo;
}

//CRIA UM NÓ EXTERNO 
static patricia_no *cria_no_interno(int indice, patricia_no *esq, patricia_no *dir)
{
    patricia_no *novo = malloc(sizeof(patricia_no));
    if (novo == NULL)
    {
        return NULL;
    }
    novo->tipo = PATRICIA_INTERNO;
    novo->dados.interno.indice = indice;
    novo->dados.interno.esq = esq;
    novo->dados.interno.dir = dir;
    return novo;
}
//CRIA UMA ÁRVORE VAZIA
patricia *cria_patricia(void)
{
    return calloc(1, sizeof(patricia));
}
//PECORRE A PATRICA ATÉ CCHEGAR EM UMA FOLHA 
static patricia_no *encontra_folha(patricia_no *no, Chave chave)
{
    if (no == NULL)
    {
        return NULL;
    }
    if (no->tipo == PATRICIA_EXTERNO)
    {
        return no;
    }
    if (patricia_bit(no->dados.interno.indice, chave) == 0)
    {
        return encontra_folha(no->dados.interno.esq, chave);
    }
    else
    {
        return encontra_folha(no->dados.interno.dir, chave);
    }
}

//INSERE UM NOVO NÓ NA POSIÇÃO CORRETA DA ÁRVORE
static patricia_no *insere_entre(const Livro *livro, patricia_no *no, int indice, int *sucesso)
{
    Chave chave = (Chave)livro->id;

    if (no->tipo == PATRICIA_EXTERNO ||
        indice < no->dados.interno.indice)
    {

        patricia_no *folha = cria_no_externo(livro);

        if (folha == NULL)
        {
            *sucesso = 0;
            return no;
        }

        patricia_no *novo;

        if (patricia_bit(indice, chave) == 0)
            novo = cria_no_interno(indice, folha, no);
        else
            novo = cria_no_interno(indice, no, folha);

        if (novo == NULL)
        {
            free(folha);
            *sucesso = 0;
            return no;
        }

        return novo;
    }

    if (patricia_bit(no->dados.interno.indice, chave) == 0)
    {
        patricia_no *filho = insere_entre(
            livro, no->dados.interno.esq, indice, sucesso);

        if (*sucesso)
            no->dados.interno.esq = filho;
    }
    else
    {
        patricia_no *filho = insere_entre(
            livro, no->dados.interno.dir, indice, sucesso);

        if (*sucesso)
            no->dados.interno.dir = filho;
    }

    return no;
}

//INSERE UM LIVRO USANDO O ID COMO A CHAVE
int inserir_patricia(patricia *arvore, Livro *livro)
{
    if (arvore == NULL || livro == NULL || livro->id < 0)
        return 0;

    Chave chave = (Chave)livro->id;

    if (!chave_valida(chave))
    {
        return 0;
    }
    // Caso a arvore esteja vazia.
    if (arvore->raiz == NULL)
    {
        arvore->raiz = cria_no_externo(livro);

        if (arvore->raiz == NULL)
        {
            return 0;
        }
        arvore->tamanho++;
        return 1;
    }

    //ENCONTRA A FOLHA QUE CORRESPONDE AO CAMINHO DA CHAVE
    patricia_no *folha = encontra_folha(arvore->raiz, chave);
    // Nao permite IDs duplicados.
    if (folha->dados.externo.livro.id == livro->id)
        return 0;

    Chave chave_folha =
        (Chave)folha->dados.externo.livro.id;

    //ENCONTRA O PRIMIERO BIT DIFERENTE
    int indice = 1;
    while (indice <= B && patricia_bit(indice, chave) == patricia_bit(indice, chave_folha))
    {
        indice++;
    }
    if (indice > B)
        return 0;
    int sucesso = 1;
    patricia_no *nova_raiz = insere_entre(livro, arvore->raiz, indice, &sucesso);
    if (!sucesso)
    {
        return 0;
    }
    arvore->raiz = nova_raiz;
    arvore->tamanho++;
    return 1;
}

//BUSCA UM LIVRO PELO ID, RETORNA NULL SE NÃO ENCONTRAR 
Livro *buscar_patricia(patricia *arvore, Chave id)
{
    if (arvore == NULL || arvore->raiz == NULL || !chave_valida(id))
    {
        return NULL;
    }
    patricia_no *folha = encontra_folha(arvore->raiz, id);
    if (folha != NULL && folha->dados.externo.livro.id >= 0 && (Chave)folha->dados.externo.livro.id == id)
    {
        return &folha->dados.externo.livro;
    }
    return NULL;
}

//REMOVE UM LIVRO PELO ID 
int remover_patricia(patricia *arvore, Chave id)
{
    if (arvore == NULL || arvore->raiz == NULL || !chave_valida(id))
    {
        return 0;
    }
    patricia_no *no = arvore->raiz;
    patricia_no *pai = NULL;

    //ENDEREÇO DO PONTEIRO QUE APONTA PARA O PAI 
    patricia_no **ligacao_pai = NULL;

    //PECORRE A ÁRVORE ATÉ CHEGAR A UMA FOLHA
    while (no->tipo == PATRICIA_INTERNO)
    {
        pai = no;
        ligacao_pai = &no;

        if (patricia_bit(no->dados.interno.indice, id) == 0)
        {
            no = no->dados.interno.esq;
        }
        else
        {
            no = no->dados.interno.dir;
        }
    }

    //CONFIRMA SE O ID REALMENTE EXISTE
    if (no->dados.externo.livro.id < 0 || (Chave)no->dados.externo.livro.id != id)
    {
        return 0;
    }
    //SE A ÁRVORE TINHA APENAS UMA FOLHA 
    if (pai == NULL)
    {
        free(no);
        arvore->raiz = NULL;
    }
    else
    {
        patricia_no *avo = NULL;
        patricia_no **ligacao_avo = NULL;

        //LOCALIZA O PONTEIRO QUE APONTA PARA O PAI 
        patricia_no *atual = arvore->raiz;

        while (atual != pai)
        {
            avo = atual;
            if (patricia_bit(atual->dados.interno.indice, id) == 0)
            {
                atual = atual->dados.interno.esq;
            }
            else
            {
                atual = atual->dados.interno.dir;
            }
        }

        if (avo != NULL)
        {
            if (avo->dados.interno.esq == pai)
            {
                ligacao_avo = &avo->dados.interno.esq;
            }
            else
            {
                ligacao_avo = &avo->dados.interno.dir;
            }
        }

        //O IRMÃO OCUPA O LUGAR DO PAI E DA FOLHA REMOVIDA 
        patricia_no *irmao;

        if (pai->dados.interno.esq == no)
        {
            irmao = pai->dados.interno.dir;
        }
        else
        {
            irmao = pai->dados.interno.esq;
        }
        if (ligacao_avo == NULL)
        {
            arvore->raiz = irmao;
        }
        else
        {
            *ligacao_avo = irmao;
        }
        free(no);
        free(pai);
    }

    arvore->tamanho--;

    return 1;
}

//IMPRIME TODAS AS FOLHAS DA ÁRVORE 
static void imprimir_nos(const patricia_no *no)
{
    if (no == NULL)
    {
        return;
    }
    if (no->tipo == PATRICIA_EXTERNO)
    {
        Livro *livro = (Livro *)&no->dados.externo.livro;
        imprimir_livro(livro);
        return;
    }

    imprimir_nos(no->dados.interno.esq);
    imprimir_nos(no->dados.interno.dir);
}

//IMPRIME TODOS OS LIVROS ARMAZENADOS 
void imprimir_patricia(patricia *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("A biblioteca esta vazia.\n");
        return;
    }

    imprimir_nos(arvore->raiz);
}

//LIBERA TODOS OS NÓS DA ÁRVORE 
static void destruir_nos(patricia_no *no)
{
    if (no == NULL)
    {
        return;
    }
    if (no->tipo == PATRICIA_INTERNO)
    {
        destruir_nos(no->dados.interno.esq);
        destruir_nos(no->dados.interno.dir);
    }

    free(no);
}

//DESTROI A PATRICIA E LIBERA A MEMÓRIA UTILIZADA 
void destruir_patricia(patricia *arvore)
{
    if (arvore == NULL)
    {
        return;
    }
    destruir_nos(arvore->raiz);
    free(arvore);
}

