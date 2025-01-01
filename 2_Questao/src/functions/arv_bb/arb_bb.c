#include "./arv_bb.h"

int inserirPalavraIngles(PalavraIngles **ingles, InfoArvBB info,int unidade){
    int insere = 1;
    
    if(!(*ingles)){
        PalavraIngles *novaPalavra = (PalavraIngles*)malloc(sizeof(PalavraIngles));
        
        novaPalavra->info = info;
        inserirUnidadeLista(&(novaPalavra->info.unidades),unidade);

        novaPalavra->esq = NULL;
        novaPalavra->dir = NULL;

        *ingles = novaPalavra;
    }else{
        if(strcmp(info.palavraIngles,(*ingles)->info.palavraIngles) < 0){
            insere = inserirPalavraIngles(&(*ingles)->esq,info,unidade);
        }else if(strcmp(info.palavraIngles,(*ingles)->info.palavraIngles) > 0){
            insere = inserirPalavraIngles(&(*ingles)->dir,info,unidade);
        }else{
            inserirUnidadeLista(&((*ingles)->info.unidades),unidade);
            insere = 0;
        }
    }

    return insere;
}

static int ehFolha(PalavraIngles* raiz){
    return (raiz->esq == NULL && raiz->dir == NULL);
}

static PalavraIngles* soUmFilho(PalavraIngles*raiz){
    PalavraIngles*aux;
    aux = NULL;

    if(raiz->dir == NULL){
        aux = raiz->esq;
    }else if(raiz->esq == NULL){
        aux = raiz->dir;
    }

    return aux;
}

static PalavraIngles* menorFilho(PalavraIngles*raiz){
    PalavraIngles*aux;
    aux = raiz;

    if(raiz){
        if(raiz->esq)
            aux = menorFilho(raiz->esq);
    }

    return aux;
}

static int verificaPalavraUnidade(PalavraIngles*raiz,PalavraIngles *palavra){
	return (raiz == palavra);
}

int removerPalavraIngles(PalavraIngles**raiz, PalavraIngles *palavra){
    PalavraIngles*endFilho;
    int existe = 0;

    if((*raiz)){

        if(verificaPalavraUnidade(*raiz,palavra)){
            existe = 1;

            PalavraIngles*aux = *raiz;
            if(ehFolha(*raiz)){
                free(aux);
                *raiz = NULL;
            }else if((endFilho = soUmFilho(*raiz)) != NULL){
                free(aux);
                *raiz = endFilho;
            }else {
                endFilho = menorFilho((*raiz)->dir);
                
                (*raiz)->info = endFilho->info;

                removerPalavraIngles(&(*raiz)->dir,endFilho);
            }
        }else if(strcmp(palavra->info.palavraIngles, (*raiz)->info.palavraIngles) < 0)
            existe = removerPalavraIngles(&(*raiz)->esq, palavra);
        else
            existe = removerPalavraIngles(&(*raiz)->dir, palavra);
    }

    return existe;
}

int removePalavraInglesUnidade(PalavraIngles **raiz,int unidade){
    int verifica = 0;

    if(*raiz){
        
        if(buscarUnidadeLista((*raiz)->info.unidades,unidade)){
            if((verifica = removerUnidadeLista(&((*raiz)->info.unidades),unidade))){
                if(!((*raiz)->info.unidades))
                    verifica = removerPalavraIngles(raiz,(*raiz));
            }
        }else{
            verifica = removePalavraInglesUnidade(&(*raiz)->esq,unidade);
            if(!verifica){
                verifica = removePalavraInglesUnidade(&(*raiz)->dir,unidade);
            }
        }
    }
    return verifica;
}

int verificaInglesUnidade(PalavraIngles* raiz,int unidade){
    int verifica = 0;

    if(raiz){
        
        if(buscarUnidadeLista(raiz->info.unidades,unidade)){
            verifica = 1;
        }else{
            verifica = verificaInglesUnidade(raiz->esq,unidade);
            if(!verifica){
                verifica = verificaInglesUnidade(raiz->dir,unidade);
            }
        }
    }
    return verifica;
}

void exibeInglesUnidade(PalavraIngles* raiz,int unidade){
    if(raiz){
        
        if(buscarUnidadeLista(raiz->info.unidades,unidade)){
            printf("%s -> ",raiz->info.palavraIngles);
        }else{
            exibeInglesUnidade(raiz->esq,unidade);
            exibeInglesUnidade(raiz->dir,unidade);
        }
    }
}

void exibirENOrdem(PalavraIngles* raiz){
    if(raiz){
        exibirENOrdem(raiz->esq);
        printf("%s -> ", raiz->info.palavraIngles);
        exibirENOrdem(raiz->dir);
    }
}

void liberaArvoreBB(PalavraIngles*raiz){
    if(raiz){
        liberaArvoreBB(raiz->esq);
        liberaArvoreBB(raiz->dir);
        free(raiz);
        raiz = NULL;
    }
}