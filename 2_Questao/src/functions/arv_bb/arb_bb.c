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

static int verificaPalavraUnidade(InglesPortugues *raiz,char *palavra, int unidade){
	return (strcmp(raiz->info.palavra, palavra) == 0 && raiz->info.unidade == unidade);
}

int removerPalavraIngles(InglesPortugues **raiz, char *palavra,int unidade){
    InglesPortugues *endFilho;
    int existe = 0;

    if((*raiz)){

        if(verificaPalavraUnidade(*raiz,palavra,unidade)){
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

                removerPalavraIngles(&(*raiz)->dir,endFilho->info.palavra,endFilho->info.unidade);
            }
        }else if(strcmp(palavra, (*raiz)->info.palavra) < 0)
            existe = removerPalavraIngles(&(*raiz)->esq, palavra, unidade);
        else
            existe = removerPalavraIngles(&(*raiz)->dir, palavra, unidade);
    }

    return existe;
}

void removeArvoreBB(InglesPortugues *raiz,int unidade){
    if(raiz){
        removeArvoreBB(raiz->esq,unidade);
        removeArvoreBB(raiz->dir,unidade);
        if(raiz->info.unidade == unidade)
            removerPalavraIngles(&raiz,raiz->info.palavra,unidade);
        
    }
}

void liberaArvoreBB(InglesPortugues *raiz){
    if(raiz){
        liberaArvoreBB(raiz->esq);
        liberaArvoreBB(raiz->dir);
        free(raiz);
        raiz = NULL;
    }
}