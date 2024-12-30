#pragma once

typedef struct listaUnidade{
    int unidade;

    struct listaUnidade *prox;
}ListaUnidade;

typedef struct palavraIngles{
    char *palavraIngles;

    struct palavraIngles *dir,*esq;
}PalavraIngles;

typedef struct data{
    char *palavraPortugues;
    int unidade;

    PalavraIngles *traducaoIngles;
}Data;

typedef struct palavraPortugues{
    Data info1,info2;

    int n_infos;
    struct palavraPortugues *esq,*cen,*dir;
}PalavraPortugues;