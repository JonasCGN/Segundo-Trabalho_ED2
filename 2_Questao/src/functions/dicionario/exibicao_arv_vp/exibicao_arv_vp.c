#include "./exibicao_arv_vp.h"

void exibeArvoreVP(PalavraPortugues *raiz, int unidade){
	if(raiz){
		exibeArvoreVP(raiz->esq,unidade);
		
		if(verificaInglesUnidade(raiz->info.traducaoIngles,unidade)){
			printf("-----------------------------------------\n");
			printf("Portugues \t %s\n", raiz->info.palavraPortugues);
			exibePalavrasInglesUnidade(raiz->info.traducaoIngles,unidade);
			printf("-----------------------------------------\n");
		}

		exibeArvoreVP(raiz->dir,unidade);
	}
}

void exibePalavraPortuguesIngles(PalavraPortugues *raiz, char *palavra){
	if(raiz){
		exibePalavraPortuguesIngles(raiz->esq,palavra);
		if(strcmp(palavra, raiz->info.palavraPortugues) == 0){
			printf("-----------------------------------------\n");
			printf("Portugues \t %s\n", raiz->info.palavraPortugues);
			exibePalavraIngles(raiz->info.traducaoIngles);
			printf("-----------------------------------------\n");
		}

		exibePalavraPortuguesIngles(raiz->dir,palavra);
	}
}

void exibeTodasPalavras(PalavraPortugues *raiz){
	if(raiz){
		exibeTodasPalavras(raiz->esq);
		printf("-----------------------------------------\n");
		printf("Portugues: %s\n",raiz->info.palavraPortugues);
		exibePalavraIngles(raiz->info.traducaoIngles);
		printf("-----------------------------------------\n");
		exibeTodasPalavras(raiz->dir);
	}
}