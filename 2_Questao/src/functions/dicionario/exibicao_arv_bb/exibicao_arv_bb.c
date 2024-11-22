#include "./exibicao_arv_bb.h"

void exibePalavraIngles(InglesPortugues *raiz){
	if(raiz){
		exibePalavraIngles(raiz->esq);
		printf("Ingles \t\t %s\n", raiz->info.palavra);
		printf("Unidade \t %d\n", raiz->info.unidade);
		exibePalavraIngles(raiz->dir);
	}
}

void exibePalavrasInglesUnidade(InglesPortugues *raiz, int unidade){
	if(raiz){
		exibePalavrasInglesUnidade(raiz->esq,unidade);
		if(unidade == raiz->info.unidade){
			printf("Ingles \t\t %s\n", raiz->info.palavra);
			printf("Unidade \t %d\n", raiz->info.unidade);
		}
		exibePalavrasInglesUnidade(raiz->dir,unidade);
	}
}