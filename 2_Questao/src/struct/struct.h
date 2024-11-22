#pragma once

typedef struct infoArvBB{
    char palavra[50];
    int unidade;
}InfoArvBB;


typedef struct inglesPortugues{
    InfoArvBB info;

    struct inglesPortugues *esq,*dir;
}InglesPortugues;

typedef struct info{
    char palavra[50];
    int unidade;
    InglesPortugues *palavrasIngles;
}Info;

typedef struct  arvVP{
	Info info;

	int cor;
	struct arvVP *esq,*dir;
}ArvVP;