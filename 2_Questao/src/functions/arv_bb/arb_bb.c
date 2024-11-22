#include "./arv_bb.h"

int inserirPalavraIngles(InglesPortugues **raiz, InfoArvBB info){
    int insere = 1;
    
    if(!(*raiz)){
        InglesPortugues *novaPalavra = (InglesPortugues*)malloc(sizeof(InglesPortugues));
        
        novaPalavra->info = info;
        novaPalavra->esq = NULL;
        novaPalavra->dir = NULL;

        *raiz = novaPalavra;
    }else{
        if(strcmp(info.palavra,(*raiz)->info.palavra) < 0)
            insere = inserirPalavraIngles(&(*raiz)->esq, info);
        else if(strcmp(info.palavra,(*raiz)->info.palavra) > 0)
            insere = inserirPalavraIngles(&(*raiz)->dir, info);
        else if(info.unidade != (*raiz)->info.unidade)
			insere = inserirPalavraIngles(&((*raiz)->esq),info);
        else
            insere = 0;
    }

    return insere;
}

static int ehFolha(InglesPortugues *raiz){
    return (raiz->esq == NULL && raiz->dir == NULL);
}

static InglesPortugues *soUmFilho(InglesPortugues *raiz){
    InglesPortugues *aux;
    aux = NULL;

    if(raiz->dir == NULL){
        aux = raiz->esq;
    }else if(raiz->esq == NULL){
        aux = raiz->dir;
    }

    return aux;
}

static InglesPortugues *menorFilho(InglesPortugues *raiz){
    InglesPortugues *aux;
    aux = raiz;

    if(raiz){
        if(raiz->esq)
            aux = menorFilho(raiz->esq);
    }

    return aux;
}

int removerPalavraIngles(InglesPortugues **raiz, char *palavra){
    InglesPortugues *endFilho;
    int existe = 0;

    if((*raiz)){

        if(strcmp(palavra, (*raiz)->info.palavra) == 0){
            existe = 1;

            InglesPortugues *aux = *raiz;
            if(ehFolha(*raiz)){
                free(aux);
                *raiz = NULL;
            }else if((endFilho = soUmFilho(*raiz)) != NULL){
                free(aux);
                *raiz = endFilho;
            }else {
                endFilho = menorFilho((*raiz)->dir);
                
                (*raiz)->info = endFilho->info;

                removerPalavraIngles(&(*raiz)->dir,endFilho->info.palavra);
            }
        }else if(strcmp(palavra, (*raiz)->info.palavra) < 0)
            existe = removerPalavraIngles(&(*raiz)->esq, palavra);
        else
            existe = removerPalavraIngles(&(*raiz)->dir, palavra);
    }

    return existe;
}