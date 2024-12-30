#include "./arv_bb.h"

int inserirPalavraIngles(PalavraIngles **ingles, char *palavra){
    int insere = 1;
    
    if(!(*ingles)){
        PalavraIngles *novaPalavra = (PalavraIngles*)malloc(sizeof(PalavraIngles));
        
        novaPalavra->palavraIngles = palavra;
        novaPalavra->esq = NULL;
        novaPalavra->dir = NULL;

        *ingles = novaPalavra;
    }else{
        if(strcmp(palavra,(*ingles)->palavraIngles) < 0){
            insere = inserirPalavraIngles(&(*ingles)->esq,palavra);
        }else if(strcmp(palavra,(*ingles)->palavraIngles) > 0){
            insere = inserirPalavraIngles(&(*ingles)->dir,palavra);
        }else{
            insere = 0;
        }
    }

    return insere;
}