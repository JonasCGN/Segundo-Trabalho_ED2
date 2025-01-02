#include "./remocao.h"

static int eh_folha(Unidade no)
{
    return no.esq == NULL;
}

static int eh_info1(Unidade no, int info)
{
    return info == no.info1.ini;
}

static int eh_info2(Unidade no, int info)
{
    return no.n_infos == 2 && info == no.info2.ini;
}

static int calcular_altura(Unidade *no)
{
    int altura = -1;

    if(no != NULL)
        altura = 1 + calcular_altura(no->esq);

    return altura;
}

static int possivel_remover(Unidade *raiz)
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

Unidade *no23_alocar()
{
    Unidade *no;
    no = (Unidade *)malloc(sizeof(Unidade));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore");
        exit(EXIT_FAILURE);
    }

    return no;
}

void no23_desalocar(Unidade **no)
{
    free(*no);
    *no = NULL;
}

Unidade *no23_criar(Data info, Unidade *filho_esquerdo, Unidade *filho_centro)
{
    Unidade *no;
    no = no23_alocar();

    no->info1 = info;
    no->esq = filho_esquerdo;
    no->cen = filho_centro;
    no->dir = NULL;
    no->n_infos = 1;
    return no;
} 

static Unidade *no23_quebrar(Unidade *no, Data info, Data *promove, Unidade *filho_maior)
{
    Unidade *maior;
    if(info.ini > no->info2.ini)
    {
        *promove = no->info2;
        maior = no23_criar(info, no->dir, filho_maior);
    }
    else if(info.ini > no->info1.ini)
    {
        *promove = info;
        maior = no23_criar(no->info2, filho_maior, no->dir);
    }
    else
    {
        *promove = no->info1;
        maior = no23_criar(no->info2, no->cen, no->dir);
        no->info1 = info;
        no->cen = filho_maior;
    }
    no->n_infos = 1;

    return maior;
}


static void no23_adicionar_info(Unidade *no, Data info, Unidade *filho_maior)
{
    if(info.ini > no->info1.ini)
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

static Unidade *no23_juntar(Unidade *filho1, Data info, Unidade *maior, Unidade **raiz)
{
    no23_adicionar_info(filho1, info, maior);

    (*raiz)->n_infos--;

    if((*raiz)->n_infos == 0)
        no23_desalocar(raiz);

    return filho1;
}

Data no23_maior_info(Unidade *raiz)
{
    return raiz->n_infos == 2 ? raiz->info2 : raiz->info1;
}

Unidade *arvore23_criar()
{
    return NULL;
}

Unidade *arvore23_buscar(Unidade *raiz, int info)
{
    Unidade *no;
    no = NULL;

    if(raiz != NULL)
    {
        if(eh_info1(*raiz, info) || eh_info2(*raiz, info))
            no = raiz;
        else if(info < raiz->info1.ini)
            no = arvore23_buscar(raiz->esq, info);
        else if(raiz->n_infos == 1 || info < raiz->info2.ini)
            no = arvore23_buscar(raiz->cen, info);
        else
            no = arvore23_buscar(raiz->dir, info);
    }

    return no;
}

Unidade *arvore23_buscar_menor_filho(Unidade *raiz, Unidade **pai)
{
    Unidade *filho;
    filho = raiz;

    while(!eh_folha(*filho))
    {
        *pai = filho;
        filho = filho->esq;
    }

    return filho;
}

Unidade *arvore23_buscar_maior_filho(Unidade *raiz, Unidade **pai, Data *maior_valor)
{
    Unidade *filho;
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

Unidade *arvore23_buscar_pai(Unidade *raiz, int info)
{
    Unidade *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(info < raiz->info1.ini)
                pai = arvore23_buscar_pai(raiz->esq, info);
            else if(raiz->n_infos == 1 || info < raiz->info2.ini)
                pai = arvore23_buscar_pai(raiz->cen, info);
            else
                pai = arvore23_buscar_pai(raiz->dir, info);

            if(pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

Unidade *arvore23_buscar_maior_pai(Unidade *raiz, int info)
{
    Unidade *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(info < raiz->info1.ini)
                pai = arvore23_buscar_maior_pai(raiz->esq, info);
            else if(raiz->n_infos == 1 || info < raiz->info2.ini)
                pai = arvore23_buscar_maior_pai(raiz->cen, info);
            else
                pai = arvore23_buscar_maior_pai(raiz->dir, info);

            if(pai == NULL && ((raiz->n_infos == 1 && raiz->info1.ini > info) || (raiz->n_infos == 2 && raiz->info2.ini > info)))
                pai = raiz;
        }
    }

    return pai;
}

Unidade *arvore23_buscar_menor_pai(Unidade *raiz, int info)
{
    Unidade *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(info < raiz->info1.ini)
                pai = arvore23_buscar_menor_pai(raiz->esq, info);
            else if(raiz->n_infos == 1 || info < raiz->info2.ini)
                pai = arvore23_buscar_menor_pai(raiz->cen, info);
            else
                pai = arvore23_buscar_menor_pai(raiz->dir, info);

            if(pai == NULL && raiz->info1.ini < info)
                pai = raiz;
        }
    }

    return pai;
}

static Unidade *arvore23_buscar_menor_pai_2_infos(Unidade *raiz, int info)
{
    Unidade *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(info < raiz->info1.ini)
                pai = arvore23_buscar_menor_pai_2_infos(raiz->esq, info);
            else if(raiz->n_infos == 1 || info < raiz->info2.ini)
                pai = arvore23_buscar_menor_pai_2_infos(raiz->cen, info);
            else
                pai = arvore23_buscar_menor_pai_2_infos(raiz->dir, info);

            if(pai == NULL && raiz->n_infos == 2 && raiz->info2.ini < info)
                pai = raiz;
        }
    }

    return pai;
}

static int movimento_onda(Data saindo, Data *entrada, Unidade *pai, Unidade **origem, Unidade **raiz, Unidade **maior, int (*funcao_remover)(Unidade **, int, Unidade *, Unidade **, Unidade **))
{
    int removeu = funcao_remover(raiz, saindo.ini, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}


void arvore23_desalocar(Unidade **raiz)
{
    if(*raiz != NULL)
    {
        arvore23_desalocar(&((*raiz)->esq));
        arvore23_desalocar(&((*raiz)->cen));

        if((*raiz)->n_infos == 2)
            arvore23_desalocar(&((*raiz)->dir));

        no23_desalocar(raiz);
    }
}

Unidade *arvore23_inserir(Unidade **raiz, Data info, Unidade *pai, Data *promove)
{
    Unidade *maior;
    maior = NULL;

    if(*raiz == NULL)
        *raiz = no23_criar(info, NULL, NULL);
    else
    {
        if(eh_folha(**raiz))
        {
            if((*raiz)->n_infos == 1)
                no23_adicionar_info(*raiz, info, NULL);
            else
            {
                maior = no23_quebrar(*raiz, info, promove, NULL);
                if(pai == NULL)
                {
                    *raiz = no23_criar(*promove, *raiz, maior);
                    maior = NULL;
                }
            }
        }
        else
        {
            if(info.ini < (*raiz)->info1.ini)
                maior = arvore23_inserir(&((*raiz)->esq), info, *raiz, promove);
            else if((*raiz)->n_infos == 1 || info.ini < (*raiz)->info2.ini)
                maior = arvore23_inserir(&((*raiz)->cen), info, *raiz, promove);
            else
                maior = arvore23_inserir(&((*raiz)->dir), info, *raiz, promove);

            if(maior != NULL)
            {
                if((*raiz)->n_infos == 1)
                {
                    no23_adicionar_info(*raiz, *promove, maior);
                    maior = NULL;
                }
                else
                {
                    Data promove_aux;
                    maior = no23_quebrar(*raiz, *promove, &promove_aux, maior);
                    *promove = promove_aux;
                    if(pai == NULL)
                    {
                        *raiz = no23_criar(promove_aux, *raiz, maior);
                        maior = NULL;
                    }
                }
            }
        }
    }

    return maior;
}

static int arvore23_remover_no_interno1(Unidade **origem, Unidade* raiz, Data *info, Unidade *filho1, Unidade *filho2, Unidade **maior)
{
    int removeu;
    Unidade *filho, *pai;
    Data info_filho;

    pai = raiz;

    filho = arvore23_buscar_maior_filho(filho1, &pai, &info_filho);

    if(filho->n_infos == 2)
    {
        *info = info_filho;
        filho->n_infos = 1;
    }
    else
    {
        filho = arvore23_buscar_menor_filho(filho2, &pai);
        removeu = movimento_onda(filho->info1, info, pai, origem, &filho, maior, arvore23_remover1);
    }

    return removeu;
}

static int arvore23_remover_no_interno2(Unidade **origem, Unidade* raiz, Data *info, Unidade *filho1, Unidade *filho2, Unidade **maior)
{
    int removeu;
    Unidade *filho, *pai;
    Data info_filho;

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
        removeu = movimento_onda(info_filho, info, pai, origem, &filho, maior, arvore23_remover2);
    }

    return removeu;
}

int arvore23_remover1(Unidade **raiz, int info, Unidade *pai, Unidade **origem, Unidade **maior)
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
                        Unidade *pai_aux;
                        Data info_pai;
                        if(*raiz == pai->esq || (pai->n_infos == 2 && *raiz == pai->cen))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.ini);
                            
                            if(*raiz == pai->esq)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover1);
                        }
                        else // Filho do centro (com pai de 1 info) ou da direita
                        {
                            pai_aux = arvore23_buscar_maior_pai(*origem, (*raiz)->info1.ini);

                            Unidade *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.ini);


                            if(pai_aux != NULL)
                            {
                                if(pai_aux->info1.ini > (*raiz)->info1.ini)
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calcular_altura(menor_pai);
                            int altura_pai_aux = calcular_altura(pai_aux);

                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL && altura_menor_pai <= altura_pai_aux && info_pai.ini > menor_pai->info2.ini))
                            {
                                *maior = pai;
                                (*raiz)->n_infos = 0;
                                removeu = -1;
                            }
                            else
                            {

                                Unidade *avo;
                                avo = arvore23_buscar_pai(*origem, info_pai.ini);
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
            if(info < (*raiz)->info1.ini)
                removeu = arvore23_remover1(&(*raiz)->esq, info, *raiz, origem, maior);
            else if((*raiz)->n_infos == 1 || info < (*raiz)->info2.ini)
                removeu = arvore23_remover1(&(*raiz)->cen, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover1(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int arvore23_remover2(Unidade **raiz, int info, Unidade *pai, Unidade **origem, Unidade **maior)
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
                        Unidade *pai_aux;
                        Data info_pai;
                        if(*raiz == pai->cen || (pai->n_infos == 2 && *raiz == pai->dir))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.ini);
                            
                            if(*raiz == pai->cen)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover2);
                        }
                        else // Filho da esquerda
                        {
                            pai_aux = arvore23_buscar_menor_pai(*origem, (*raiz)->info1.ini);

                            Unidade *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.ini);

                            Unidade *avo;
                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {  
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if(pai_aux->n_infos == 2 && pai_aux->info2.ini < (*raiz)->info1.ini)
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = arvore23_buscar_pai(*origem, info_pai.ini);
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
            if(info < (*raiz)->info1.ini)
                removeu = arvore23_remover2(&(*raiz)->esq, info, *raiz, origem, maior);
            else if((*raiz)->n_infos == 1 || info < (*raiz)->info2.ini)
                removeu = arvore23_remover2(&(*raiz)->cen, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover2(&(*raiz)->dir, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int arvore23_remover(Unidade **raiz, int info)
{   
    Unidade *maior, *posicao_juncao;
    int removeu = arvore23_remover1(raiz, info, NULL, raiz, &posicao_juncao);

    if(removeu == -1)
    {
        removeu = 1;
        Data valor_juncao = no23_maior_info(posicao_juncao);
        maior = NULL;
        int removeu_aux = arvore23_rebalancear(raiz, valor_juncao.ini, &maior);
        
        if(removeu_aux == -1)
        {
            Unidade *pai, *posicao_juncao2;
            Data *entrada;
            pai = arvore23_buscar_pai(*raiz, valor_juncao.ini);

            if(eh_info1(*posicao_juncao, valor_juncao.ini))
                entrada = &(posicao_juncao->cen->info1);
            else
                entrada = &(posicao_juncao->dir->info1);

            removeu_aux = movimento_onda(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, arvore23_remover2);

            if(removeu_aux == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = arvore23_buscar_pai(*raiz, valor_juncao.ini);
                removeu_aux = movimento_onda(valor_juncao, &(posicao_juncao2->esq->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, arvore23_remover1);

                valor_juncao = no23_maior_info(posicao_juncao);
                maior = NULL;
                removeu_aux = arvore23_rebalancear(raiz, valor_juncao.ini, &maior);
            }
        }

        if(*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

static int balanceamento(Unidade **raiz, Unidade *filho1, Unidade **filho2, Data info, Unidade **maior)
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

int arvore23_rebalancear(Unidade **raiz, int info, Unidade **maior)
{
    int balanceou = 0;
    if(*raiz != NULL)
    {
        if(!eh_folha(**raiz))
        {
            if(info < (*raiz)->info1.ini)
                balanceou = arvore23_rebalancear(&((*raiz)->esq), info, maior);
            else if((*raiz)->n_infos == 1 || info < (*raiz)->info2.ini)
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

void arvore23_exibir_pre(Unidade *raiz)
{
    if(raiz != NULL)
    {
        printf("[1º] %d -> ", raiz->info1.ini);
        if(raiz->n_infos == 2)
            printf("[2º] %d -> ", raiz->info2.ini);

        arvore23_exibir_pre(raiz->esq);
        arvore23_exibir_pre(raiz->cen);
        if(raiz->n_infos == 2)
            arvore23_exibir_pre(raiz->dir);
    }
}

void arvore23_exibir_ordem(Unidade *raiz)
{
    if(raiz != NULL)
    {
        arvore23_exibir_ordem(raiz->esq);
        printf("[1º] %d -> ", raiz->info1.ini);
        arvore23_exibir_ordem(raiz->cen);

        if(raiz->n_infos == 2)
        {
            printf("[2º] %d -> ", raiz->info2.ini);
            arvore23_exibir_ordem(raiz->dir);
        }
    }
}

void arvore23_exibir_pos(Unidade *raiz)
{
    if(raiz != NULL)
    {
        arvore23_exibir_pos(raiz->esq);
        arvore23_exibir_pos(raiz->cen);
        if(raiz->n_infos == 2)
            arvore23_exibir_pos(raiz->dir);

        printf("[1º] %d -> ", raiz->info1.ini);
        if(raiz->n_infos == 2)
            printf("[2º] %d -> ", raiz->info2.ini);
    }
}