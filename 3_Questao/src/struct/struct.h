#pragma once

typedef struct data{
    int ini,fim;
    int blocoIni,blocoFim;
    int status;
}Data;

typedef struct unidade{
    Data info1,info2;

    int n_infos;
    struct unidade *esq,*cen,*dir;
}Unidade;