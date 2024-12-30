#include "./arv_vp.h"

ArvVP* criaNo(Info valor){
	ArvVP* no = (ArvVP*)malloc(sizeof(ArvVP));

	no->info = valor;
	no->dir = NULL;
	no->esq = NULL;
	no->cor = VERMELHO;

	return no;
}

int cor(ArvVP *no){
	int cor = PRETO;
	
	if(no){
		cor = no->cor;
	}

	return cor;
}

void rotacaoEsq(ArvVP **no){
	ArvVP *aux;

	aux = (*no)->dir;
	
	(*no)->dir = aux->esq;
	aux->esq = (*no);

	int cor = (*no)->cor;
	(*no)->cor = aux->cor;
	aux->cor = cor;

	*no = aux;
}

void rotacaoDir(ArvVP **no){
	ArvVP *aux;

	aux = (*no)->esq;
	
	(*no)->esq = aux->dir;
	aux->dir = (*no);

	int cor = (*no)->cor;
	(*no)->cor = aux->cor;
	aux->cor = cor;

	*no = aux;
}

void inverteCor(ArvVP **no){
	if((*no)){
		(*no)->cor = ((cor(*no) == VERMELHO) ? PRETO : VERMELHO);
	}
}

void trocaCor(ArvVP **no){
	inverteCor(no);
	inverteCor(&(*no)->esq);
	inverteCor(&(*no)->dir);
}

void balancear(ArvVP **raiz){
	if(*raiz){
		if(cor((*raiz)->dir) == VERMELHO && cor((*raiz)->esq) == PRETO)
			rotacaoEsq(raiz);
		
		if((*raiz)->esq && cor((*raiz)->esq) == VERMELHO && cor((*raiz)->esq->esq) == VERMELHO)
			rotacaoDir(raiz);

		if(cor((*raiz)->esq) == VERMELHO && cor((*raiz)->dir) == VERMELHO)
			trocaCor(raiz);
	}
}

ArvVP* insereArvVP(ArvVP **raiz, ArvVP* no){
	ArvVP *existe;
	existe = NULL;

	if(!(*raiz)){
		*raiz = no;
		existe = *raiz;
	}else{
		if(strcmp(no->info.palavra, (*raiz)->info.palavra) < 0)
			existe = insereArvVP(&(*raiz)->esq,no);
		else if(strcmp(no->info.palavra, (*raiz)->info.palavra) > 0)
			existe = insereArvVP(&(*raiz)->dir,no);
		else
			existe = *raiz;
		
		balancear(raiz);
	}

	return existe;
}

void inserePortuguesIngles(ArvVP **raiz, Info info){
	insereArvVP(raiz,criaNo(info));
	(*raiz)->cor = PRETO;
}

void moveEsqVermelha(ArvVP **raiz){
	trocaCor(raiz);

	if((*raiz)->dir && cor((*raiz)->dir->esq) == VERMELHO){
		rotacaoDir(&((*raiz)->dir));
		rotacaoEsq(&(*raiz));
		trocaCor(raiz);
	}
}

void moveDirVermelha(ArvVP **raiz){
	trocaCor(raiz);

	if((*raiz)->esq && cor((*raiz)->esq->esq) == VERMELHO){
		rotacaoDir(&(*raiz));
		trocaCor(raiz);
	}
}

void removeMenor(ArvVP **raiz){
	if(!((*raiz)->esq)){
		free(*raiz);
		*raiz = NULL;
	}else{
		if(cor((*raiz)->esq) == PRETO && cor((*raiz)->esq->esq) == PRETO)
			moveEsqVermelha(raiz);
		
		removeMenor(&(*raiz)->esq);
		balancear(raiz);
	}
}

ArvVP *procuraMenor(ArvVP *raiz){
	ArvVP *menor;
	menor = raiz;

	if(raiz)
		if(raiz->esq)
			menor = procuraMenor(raiz->esq);
	

	return menor;
}

static int verificaPalavraUnidade(ArvVP *raiz,char *palavra, int unidade){
	return (strcmp(raiz->info.palavra, palavra) == 0 && raiz->info.unidade == unidade);
}

int removerNoArvVP(ArvVP **raiz, char *valor,int unidade){
	int existe = 0;

	if(*raiz){
		if(strcmp(valor, (*raiz)->info.palavra) < 0){
			if((*raiz)->esq && cor((*raiz)->esq) == PRETO && cor((*raiz)->esq->esq) == PRETO)
				moveEsqVermelha(raiz);

			existe = removerNoArvVP(&(*raiz)->esq,valor,unidade);
		}else{
			if(cor((*raiz)->esq) == VERMELHO)
				rotacaoDir(raiz);
			
			if(verificaPalavraUnidade(*raiz,valor,unidade) && (*raiz)->dir == NULL){
				removeArvoreBB((*raiz)->info.palavrasIngles,unidade);

				free(*raiz);
				*raiz = NULL;
				
				existe = 1;
			}else{
				if((*raiz)->dir && cor((*raiz)->dir) == PRETO && cor((*raiz)->dir->esq) == PRETO)
					moveDirVermelha(raiz);

				if(verificaPalavraUnidade(*raiz,valor,unidade)){
					removeArvoreBB((*raiz)->info.palavrasIngles,unidade);
					
					ArvVP *aux;
					aux = procuraMenor((*raiz)->dir);
					
					(*raiz)->info = aux->info;
					removeMenor(&(*raiz)->dir);

					existe = 1;
				}else{
					existe = removerNoArvVP(&(*raiz)->dir, valor,unidade);
				}
			}
		}
	}

	if(!existe)
		balancear(raiz);

	return existe;
}

void removePortuguesIngles(ArvVP **raiz, char *valor,int unidade){
	removerNoArvVP(raiz,valor,unidade);
	if(*raiz){
		(*raiz)->cor = PRETO;
	}
}

void exibirArvore(ArvVP *raiz){
	if(raiz){
		exibirArvore(raiz->esq);
		printf("Cor - %d\n", raiz->cor);
		printf("Valor - %s\n", raiz->info.palavra);
		exibirArvore(raiz->dir);
	}
}

void liberarArvVP(ArvVP *raiz){
	if(raiz){
		liberarArvVP(raiz->esq);
		liberarArvVP(raiz->dir);

		liberaArvoreBB(raiz->info.palavrasIngles);

		free(raiz);
		raiz = NULL;
	}
}