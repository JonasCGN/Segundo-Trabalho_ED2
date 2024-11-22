#include "./arv_bb.h"

int inserirPalavraIngles(InglesPortugues **ingles, char *palavra){
    int insere = 1;
    
    if(!(*ingles)){
        InglesPortugues *novaPalavra = (InglesPortugues*)malloc(sizeof(InglesPortugues));
        
        novaPalavra->palavra = palavra;
        novaPalavra->esq = NULL;
        novaPalavra->dir = NULL;

        *ingles = novaPalavra;
    }else{
        if(strcmp(palavra,(*ingles)->palavra) < 0){
            insere = inserirCurso(&(*ingles)->esq,palavra);
        }else if(strcmp(palavra,(*ingles)->palavra) > 0){
            insere = inserirCurso(&(*ingles)->dir,palavra);
        }else{
            insere = 0;
        }
    }

    return insere;
}