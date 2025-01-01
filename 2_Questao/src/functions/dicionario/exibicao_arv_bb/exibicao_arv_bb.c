#include "./exibicao_arv_bb.h"

void exibePalavraIngles(PalavraIngles *raiz){
	if(raiz){
		exibePalavraIngles(raiz->esq);
		printf("Ingles \t\t %s ", raiz->info.palavraIngles);
		exibirLista(raiz->info.unidades);
		printf("\n");
		exibePalavraIngles(raiz->dir);
	}
}

void exibePalavrasInglesUnidade(PalavraIngles *raiz, int unidade){
	if(raiz){
		exibePalavrasInglesUnidade(raiz->esq,unidade);
		if(buscarUnidadeLista(raiz->info.unidades,unidade)){
			printf("Ingles \t\t %s\n", raiz->info.palavraIngles);
		}
		exibePalavrasInglesUnidade(raiz->dir,unidade);
	}
}