#include "remover.h"

static int palavraMaior(char *info1,char *info2){
    return strcmp(info1,info2) > 0;
}

static int palavraMenor(char *info1,char *info2){
    return strcmp(info1,info2) < 0;
}

static int eh_folha(PalavraPortugues no)
{
    return no.esq == NULL;
}

static int eh_info1(PalavraPortugues no, char *info)
{
    return strcmp(info,no.info1.palavraPortugues) == 0;
}

static int eh_info2(PalavraPortugues no, char * info)
{
    return no.n_infos == 2 && strcmp(info,no.info2.palavraPortugues) == 0;
}

static int calcular_altura(PalavraPortugues *no)
{
    int altura = -1;

    if(no != NULL)
        altura = 1 + calcular_altura(no->esq);

    return altura;
}

static int possivel_remover(PalavraPortugues *raiz)
{
    int possivel = 0;

    if(raiz != NULL)
    {
        possivel = raiz->n_infos == 2;

        if(!possivel)
        {
            possivel = possivel_remover(raiz->cen);

            if(!possivel)
                possivel = possivel_remover(raiz->esq);
        }
    }

    return possivel;
}

static void no23_desalocar(PalavraPortugues **no)
{
    free(*no);
    *no = NULL;
}

static void no23_adicionar_info(PalavraPortugues *no, Data info, PalavraPortugues *filho_maior)
{
    if( palavraMaior(info.palavraPortugues,no->info1.palavraPortugues))
    {
        no->info2 = info;
        no->dir = filho_maior;
    }
    else
    {
        no->info2 = no->info1;
        no->dir = no->cen;
        no->cen = filho_maior;
        no->info1 = info;
    }
    no->n_infos = 2;
}

PalavraPortugues *no23_juntar(PalavraPortugues *filho1, Data info, PalavraPortugues *maior, PalavraPortugues **raiz)
{
    no23_adicionar_info(filho1, info, maior);

    (*raiz)->n_infos--;

    if((*raiz)->n_infos == 0)
        no23_desalocar(raiz);

    return filho1;
}

static Data *no23_maior_info(PalavraPortugues *raiz)
{
    return raiz->n_infos == 2 ? &(raiz->info2) : &(raiz->info1);
}

static int balanceamento(PalavraPortugues **raiz, PalavraPortugues *filho1, PalavraPortugues **filho2, Data info, PalavraPortugues **maior)
{
    int balanceou = 0;
    if(*filho2 == NULL || (*filho2)->n_infos == 0)
    {
        if(*filho2 != NULL)
            no23_desalocar(filho2);

        *maior = no23_juntar(filho1, info, *maior, raiz);
        balanceou = 1;
    }
    return balanceou;
}

int arvore23_rebalancear(PalavraPortugues **raiz, char *info, PalavraPortugues **maior)
{
    int balanceou = 0;
    if(*raiz != NULL)
    {
        if(!eh_folha(**raiz))
        {
            if(palavraMenor(info,(*raiz)->info1.palavraPortugues))
                balanceou = arvore23_rebalancear(&((*raiz)->esq), info, maior);
            else if((*raiz)->n_infos == 1 || info < (*raiz)->info2.palavraPortugues)
            {
                if((*raiz)->esq->n_infos == 2 && !possivel_remover((*raiz)->cen))
                    balanceou = -1;
                else
                    balanceou = arvore23_rebalancear(&((*raiz)->cen), info, maior);
            }
            else
            {
                if((*raiz)->cen->n_infos == 2 && !possivel_remover((*raiz)->dir))
                    balanceou = -1;
                else
                    balanceou = arvore23_rebalancear(&((*raiz)->dir), info, maior);
            }

            if(balanceou != -1)
            {
                if((*raiz)->n_infos == 1)
                    balanceou = balanceamento(raiz, (*raiz)->esq, &((*raiz)->cen), (*raiz)->info1, maior);
                else if((*raiz)->n_infos == 2)
                    balanceou = balanceamento(raiz, (*raiz)->cen, &((*raiz)->dir), (*raiz)->info2, maior);
            }
            
        }
    }

    return balanceou;
}

static PalavraPortugues *arvore23_buscar_menor_filho(PalavraPortugues *raiz, PalavraPortugues **pai)
{
    PalavraPortugues *filho;
    filho = raiz;

    while(!eh_folha(*filho))
    {
        *pai = filho;
        filho = filho->esq;
    }

    return filho;
}

static PalavraPortugues *arvore23_buscar_maior_filho(PalavraPortugues *raiz, PalavraPortugues **pai, Data **maior_valor)
{
    PalavraPortugues *filho;
    filho = raiz;

    while(!eh_folha(*filho))
    {
        *pai = filho;
        if(filho->n_infos == 1)
            filho = filho->cen;
        else
            filho = filho->dir;
    }

    if(filho != NULL)
        *maior_valor = no23_maior_info(filho);

    return filho;
}

static PalavraPortugues *arvore23_buscar_pai(PalavraPortugues *raiz, char *info)
{
    PalavraPortugues *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(palavraMenor(info,raiz->info1.palavraPortugues))
                pai = arvore23_buscar_pai(raiz->esq, info);
            else if(raiz->n_infos == 1 || palavraMenor(info,raiz->info2.palavraPortugues))
                pai = arvore23_buscar_pai(raiz->cen, info);
            else
                pai = arvore23_buscar_pai(raiz->dir, info);

            if(pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

static PalavraPortugues *arvore23_buscar_maior_pai(PalavraPortugues *raiz, char *info)
{
    PalavraPortugues *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(palavraMenor(info,raiz->info1.palavraPortugues))
                pai = arvore23_buscar_maior_pai(raiz->esq, info);
            else if(raiz->n_infos == 1 || palavraMenor(info,raiz->info2.palavraPortugues))
                pai = arvore23_buscar_maior_pai(raiz->cen, info);
            else
                pai = arvore23_buscar_maior_pai(raiz->dir, info);

            if(pai == NULL && ((raiz->n_infos == 1 && palavraMaior(raiz->info1.palavraPortugues,info)) || (raiz->n_infos == 2 && palavraMaior(raiz->info2.palavraPortugues,info))))
                pai = raiz;
        }
    }

    return pai;
}

static PalavraPortugues *arvore23_buscar_menor_pai(PalavraPortugues *raiz, char *info)
{
    PalavraPortugues *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(palavraMenor(info,raiz->info1.palavraPortugues))
                pai = arvore23_buscar_menor_pai(raiz->esq, info);
            else if(raiz->n_infos == 1 || palavraMenor(info,raiz->info2.palavraPortugues))
                pai = arvore23_buscar_menor_pai(raiz->cen, info);
            else
                pai = arvore23_buscar_menor_pai(raiz->dir, info);

            if(pai == NULL && palavraMenor(raiz->info1.palavraPortugues,info))
                pai = raiz;
        }
    }

    return pai;
}

static PalavraPortugues *arvore23_buscar_menor_pai_2_infos(PalavraPortugues *raiz, char *info)
{
    PalavraPortugues *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(palavraMenor(info,raiz->info1.palavraPortugues))
                pai = arvore23_buscar_menor_pai_2_infos(raiz->esq, info);
            else if(raiz->n_infos == 1 || palavraMenor(info,raiz->info2.palavraPortugues))
                pai = arvore23_buscar_menor_pai_2_infos(raiz->cen, info);
            else
                pai = arvore23_buscar_menor_pai_2_infos(raiz->dir, info);

            if(pai == NULL && raiz->n_infos == 2 && palavraMenor(raiz->info2.palavraPortugues,info))
                pai = raiz;
        }
    }

    return pai;
}

static int movimento_onda(Data saindo, Data *entrada, PalavraPortugues *pai, PalavraPortugues **origem, PalavraPortugues **raiz, PalavraPortugues **maior, int (*funcao_remover)(PalavraPortugues **, char*, PalavraPortugues *, PalavraPortugues **, PalavraPortugues **))
{
    int removeu = funcao_remover(raiz, saindo.palavraPortugues, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

static int arvore23_remover_no_interno1(PalavraPortugues **origem, PalavraPortugues* raiz, Data *info, PalavraPortugues *filho1, PalavraPortugues *filho2, PalavraPortugues **maior)
{
    int removeu;
    PalavraPortugues *filho, *pai;
    Data *info_filho;

    pai = raiz;

    filho = arvore23_buscar_maior_filho(filho1, &pai, &info_filho);

    if(filho->n_infos == 2)
    {
        *info = *info_filho;
        filho->n_infos = 1;
    }
    else
    {
        filho = arvore23_buscar_menor_filho(filho2, &pai);
        removeu = movimento_onda(filho->info1, info, pai, origem, &filho, maior, arvore23_remover1);
    }

    return removeu;
}

static int arvore23_remover_no_interno2(PalavraPortugues **origem, PalavraPortugues* raiz, Data *info, PalavraPortugues *filho1, PalavraPortugues *filho2, PalavraPortugues **maior)
{
    int removeu;
    PalavraPortugues *filho, *pai;
    Data *info_filho;

    pai = raiz;

    filho = arvore23_buscar_menor_filho(filho1, &pai);

    if(filho->n_infos == 2)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->n_infos = 1;
    }
    else
    {
        filho = arvore23_buscar_maior_filho(filho2, &pai, &info_filho);
        removeu = movimento_onda(*info_filho, info, pai, origem, &filho, maior, arvore23_remover2);
    }

    return removeu;
}

int arvore23_remover1(PalavraPortugues **raiz, char *info, PalavraPortugues *pai, PalavraPortugues **origem, PalavraPortugues **maior)
{
    int removeu = 0;

    if(*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2)
        {
            removeu = 1;
            if(eh_folha(**raiz))
            {
                if((*raiz)->n_infos == 2)
                {
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->n_infos = 1;
                }
                else
                {
                    if(pai == NULL)
                        no23_desalocar(raiz);
                    else
                    {
                        PalavraPortugues *pai_aux;
                        Data info_pai;
                        if(*raiz == pai->esq || (pai->n_infos == 2 && *raiz == pai->cen))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.palavraPortugues);
                            
                            if(*raiz == pai->esq)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover1);
                        }
                        else // Filho do centro (com pai de 1 info) ou da direita
                        {
                            pai_aux = arvore23_buscar_maior_pai(*origem, (*raiz)->info1.palavraPortugues);

                            PalavraPortugues *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.palavraPortugues);


                            if(pai_aux != NULL)
                            {
                                if(palavraMaior(pai_aux->info1.palavraPortugues,(*raiz)->info1.palavraPortugues))
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calcular_altura(menor_pai);
                            int altura_pai_aux = calcular_altura(pai_aux);

                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL && altura_menor_pai <= altura_pai_aux && palavraMaior(info_pai.palavraPortugues,menor_pai->info2.palavraPortugues) ))
                            {
                                *maior = pai;
                                (*raiz)->n_infos = 0;
                                removeu = -1;
                            }
                            else
                            {

                                PalavraPortugues *avo;
                                avo = arvore23_buscar_pai(*origem, info_pai.palavraPortugues);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, arvore23_remover1);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = arvore23_remover_no_interno1(origem, *raiz, &((*raiz)->info2), (*raiz)->cen, (*raiz)->dir, maior);
            else if(info1)
                removeu = arvore23_remover_no_interno1(origem, *raiz, &((*raiz)->info1), (*raiz)->esq, (*raiz)->cen, maior);
        }
        else
        {
            if(palavraMenor(info,(*raiz)->info1.palavraPortugues))
                removeu = arvore23_remover1(&(*raiz)->esq, info, *raiz, origem, maior);
            else if((*raiz)->n_infos == 1 || palavraMenor(info,(*raiz)->info2.palavraPortugues))
                removeu = arvore23_remover1(&(*raiz)->cen, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover1(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int arvore23_remover2(PalavraPortugues **raiz, char *info, PalavraPortugues *pai, PalavraPortugues **origem, PalavraPortugues **maior){
    int removeu = 0;

    if(*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2)
        {
            removeu = 1;
            if(eh_folha(**raiz))
            {
                if((*raiz)->n_infos == 2)
                {
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->n_infos = 1;
                }
                else
                {
                    if(pai == NULL)
                        no23_desalocar(raiz);
                    else
                    {
                        PalavraPortugues *pai_aux;
                        Data info_pai;
                        if(*raiz == pai->cen || (pai->n_infos == 2 && *raiz == pai->dir))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.palavraPortugues);
                            
                            if(*raiz == pai->cen)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover2);
                        }
                        else // Filho da esquerda
                        {
                            pai_aux = arvore23_buscar_menor_pai(*origem, (*raiz)->info1.palavraPortugues);

                            PalavraPortugues *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.palavraPortugues);

                            PalavraPortugues *avo;
                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {  
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if(pai_aux->n_infos == 2 && palavraMenor( pai_aux->info2.palavraPortugues,(*raiz)->info1.palavraPortugues))
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = arvore23_buscar_pai(*origem, info_pai.palavraPortugues);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, arvore23_remover2);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = arvore23_remover_no_interno2(origem, *raiz, &((*raiz)->info2), (*raiz)->dir, (*raiz)->cen, maior);
            else if(info1)
                removeu = arvore23_remover_no_interno2(origem, *raiz, &((*raiz)->info1), (*raiz)->cen, (*raiz)->esq, maior);
        }
        else
        {
            if(palavraMenor(info,(*raiz)->info1.palavraPortugues))
                removeu = arvore23_remover2(&(*raiz)->esq, info, *raiz, origem, maior);
            else if((*raiz)->n_infos == 1 || palavraMenor(info,(*raiz)->info2.palavraPortugues))
                removeu = arvore23_remover2(&(*raiz)->cen, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover2(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int arvore23_remover(PalavraPortugues **raiz, char *info)
{   
    PalavraPortugues *maior, *posicao_juncao;
    int removeu = arvore23_remover1(raiz, info, NULL, raiz, &posicao_juncao);

    if(removeu == -1)
    {
        removeu = 1;
        Data valor_juncao = *(no23_maior_info(posicao_juncao));
        maior = NULL;
        int removeu_aux = arvore23_rebalancear(raiz, valor_juncao.palavraPortugues, &maior);
        
        if(removeu_aux == -1)
        {
            PalavraPortugues *pai, *posicao_juncao2;
            Data *entrada;
            pai = arvore23_buscar_pai(*raiz, valor_juncao.palavraPortugues);

            if(eh_info1(*posicao_juncao, valor_juncao.palavraPortugues))
                entrada = &(posicao_juncao->cen->info1);
            else
                entrada = &(posicao_juncao->dir->info1);

            removeu_aux = movimento_onda(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, arvore23_remover2);

            if(removeu_aux == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = arvore23_buscar_pai(*raiz, valor_juncao.palavraPortugues);
                removeu_aux = movimento_onda(valor_juncao, &(posicao_juncao2->esq->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, arvore23_remover1);

                valor_juncao = *(no23_maior_info(posicao_juncao));
                maior = NULL;
                removeu_aux = arvore23_rebalancear(raiz, valor_juncao.palavraPortugues, &maior);
            }
        }

        if(*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}