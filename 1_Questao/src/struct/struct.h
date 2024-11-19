#pragma once

typedef struct inglesPortugues{
    char *palavra;
    struct inglesPortugues *dir,*esq;
    int unidade;
}InglesPortugues;

typedef struct info{
    char *palavraPortugues;
    InglesPortugues *traducaoIngles;
}Info;

typedef struct portuguesIngles{
    Info info1,info2;

    int qtdInfo;
    struct portuguesIngles *esq,*cen,*dir;
}PortugesIngles;