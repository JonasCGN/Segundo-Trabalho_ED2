#include "./arv_vp.h"

PalavraPortugues* criaNo(Data valor){
	PalavraPortugues* no = (PalavraPortugues*)malloc(sizeof(PalavraPortugues));

	no->info = valor;
	no->dir = NULL;
	no->esq = NULL;
	no->cor = VERMELHO;

	return no;
}

int cor(PalavraPortugues *no){
	int cor = PRETO;
	
	if(no){
		cor = no->cor;
	}

	return cor;
}

void rotacaoEsq(PalavraPortugues **no){
	PalavraPortugues *aux;

	aux = (*no)->dir;
	
	(*no)->dir = aux->esq;
	aux->esq = (*no);

	int cor = (*no)->cor;
	(*no)->cor = aux->cor;
	aux->cor = cor;

	*no = aux;
}

void rotacaoDir(PalavraPortugues **no){
	PalavraPortugues *aux;

	aux = (*no)->esq;
	
	(*no)->esq = aux->dir;
	aux->dir = (*no);

	int cor = (*no)->cor;
	(*no)->cor = aux->cor;
	aux->cor = cor;

	*no = aux;
}

void inverteCor(PalavraPortugues **no){
	if((*no)){
		(*no)->cor = ((cor(*no) == VERMELHO) ? PRETO : VERMELHO);
	}
}

void trocaCor(PalavraPortugues **no){
	inverteCor(no);
	inverteCor(&(*no)->esq);
	inverteCor(&(*no)->dir);
}

void balancear(PalavraPortugues **raiz){
	if(*raiz){
		if(cor((*raiz)->dir) == VERMELHO && cor((*raiz)->esq) == PRETO)
			rotacaoEsq(raiz);
		
		if((*raiz)->esq && cor((*raiz)->esq) == VERMELHO && cor((*raiz)->esq->esq) == VERMELHO)
			rotacaoDir(raiz);

		if(cor((*raiz)->esq) == VERMELHO && cor((*raiz)->dir) == VERMELHO)
			trocaCor(raiz);
	}
}

PalavraPortugues* inserePalavraPortugues(PalavraPortugues **raiz, PalavraPortugues* no){
	PalavraPortugues *existe;
	existe = NULL;

	if(!(*raiz)){
		*raiz = no;
		existe = *raiz;
	}else{
		if(strcmp(no->info.palavraPortugues, (*raiz)->info.palavraPortugues) < 0)
			existe = inserePalavraPortugues(&(*raiz)->esq,no);
		else if(strcmp(no->info.palavraPortugues, (*raiz)->info.palavraPortugues) > 0)
			existe = inserePalavraPortugues(&(*raiz)->dir,no);
		else
			existe = *raiz;
		
		balancear(raiz);
	}

	return existe;
}

void inserePortuguesIngles(PalavraPortugues **raiz, Data info){
	inserePalavraPortugues(raiz,criaNo(info));
	(*raiz)->cor = PRETO;
}

void moveEsqVermelha(PalavraPortugues **raiz){
	trocaCor(raiz);

	if((*raiz)->dir && cor((*raiz)->dir->esq) == VERMELHO){
		rotacaoDir(&((*raiz)->dir));
		rotacaoEsq(&(*raiz));
		trocaCor(raiz);
	}
}

void moveDirVermelha(PalavraPortugues **raiz){
	trocaCor(raiz);

	if((*raiz)->esq && cor((*raiz)->esq->esq) == VERMELHO){
		rotacaoDir(&(*raiz));
		trocaCor(raiz);
	}
}

void removeMenor(PalavraPortugues **raiz){
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

PalavraPortugues *procuraMenor(PalavraPortugues *raiz){
	PalavraPortugues *menor;
	menor = raiz;

	if(raiz)
		if(raiz->esq)
			menor = procuraMenor(raiz->esq);
	

	return menor;
}

static int verificaPalavraUnidade(PalavraPortugues *raiz,char *palavra){
	return (strcmp(raiz->info.palavraPortugues, palavra) == 0);
}

int removerNoPalavraPortugues(PalavraPortugues **raiz, char *valor){
	int existe = 0;

	if(*raiz){
		if(strcmp(valor, (*raiz)->info.palavraPortugues) < 0){
			if((*raiz)->esq && cor((*raiz)->esq) == PRETO && cor((*raiz)->esq->esq) == PRETO)
				moveEsqVermelha(raiz);

			existe = removerNoPalavraPortugues(&(*raiz)->esq,valor);
		}else{
			if(cor((*raiz)->esq) == VERMELHO)
				rotacaoDir(raiz);
			
			if(verificaPalavraUnidade(*raiz,valor) && (*raiz)->dir == NULL){

				free(*raiz);
				*raiz = NULL;
				
				existe = 1;
			}else{
				if((*raiz)->dir && cor((*raiz)->dir) == PRETO && cor((*raiz)->dir->esq) == PRETO)
					moveDirVermelha(raiz);

				if(verificaPalavraUnidade(*raiz,valor)){
					
					PalavraPortugues *aux;
					aux = procuraMenor((*raiz)->dir);
					
					(*raiz)->info = aux->info;
					removeMenor(&(*raiz)->dir);

					existe = 1;
				}else{
					existe = removerNoPalavraPortugues(&(*raiz)->dir, valor);
				}
			}
		}
	}

	if(!existe)
		balancear(raiz);

	return existe;
}

void removePortuguesIngles(PalavraPortugues **raiz, char *valor){
	removerNoPalavraPortugues(raiz,valor);
	if(*raiz){
		(*raiz)->cor = PRETO;
	}
}

void exibirArvore(PalavraPortugues *raiz){
	if(raiz){
		exibirArvore(raiz->esq);
		printf("Cor - %d\n", raiz->cor);
		printf("Valor - %s\n", raiz->info.palavraPortugues);
		exibirArvore(raiz->dir);
	}
}

void liberarPalavraPortugues(PalavraPortugues *raiz){
	if(raiz){
		liberarPalavraPortugues(raiz->esq);
		liberarPalavraPortugues(raiz->dir);

		liberaArvoreBB(raiz->info.traducaoIngles);

		free(raiz);
		raiz = NULL;
	}
}