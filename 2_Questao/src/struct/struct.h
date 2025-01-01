#pragma once

typedef struct listaUnidade{
    int unidade;

    struct listaUnidade *prox;
}ListaUnidade;

typedef struct infoArvBB{
    char palavraIngles[50];
    ListaUnidade *unidades;
}InfoArvBB;

typedef struct palavraIngles{
    InfoArvBB info;

    struct palavraIngles *dir,*esq;
}PalavraIngles;

typedef struct data{
    char palavraPortugues[50];

    PalavraIngles *traducaoIngles;
}Data;

typedef struct  palavraPortugues{
	Data info;

	int cor;
	struct palavraPortugues *esq,*dir;
}PalavraPortugues;