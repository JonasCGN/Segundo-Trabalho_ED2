#include "./exibicao_arv_vp.h"

void exibeArvoreVP(ArvVP *raiz, int unidade){
	if(raiz){
		exibeArvoreVP(raiz->esq,unidade);
		
		if(raiz->info.unidade == unidade){
			printf("-----------------------------------------\n");
			printf("Portugues \t %s\n", raiz->info.palavra);
			exibePalavrasInglesUnidade(raiz->info.palavrasIngles,unidade);
			printf("-----------------------------------------\n");
		}

		exibeArvoreVP(raiz->dir,unidade);
	}
}

void exibePalavraPortuguesIngles(ArvVP *raiz, char *palavra){
	if(raiz){
		exibePalavraPortuguesIngles(raiz->esq,palavra);
		if(strcmp(palavra, raiz->info.palavra) == 0){
			printf("-----------------------------------------\n");
			printf("Portugues \t %s\n", raiz->info.palavra);
			exibePalavraIngles(raiz->info.palavrasIngles);
			printf("-----------------------------------------\n");
		}

		exibePalavraPortuguesIngles(raiz->dir,palavra);
	}
}

void exibeTodasPalavras(ArvVP *raiz){
	if(raiz){
		exibeTodasPalavras(raiz->esq);
		printf("Portugues: %s\n",raiz->info.palavra);
		printf("Unidade: %d\n",raiz->info.unidade);
		exibePalavraIngles(raiz->info.palavrasIngles);
		exibeTodasPalavras(raiz->dir);
	}
}