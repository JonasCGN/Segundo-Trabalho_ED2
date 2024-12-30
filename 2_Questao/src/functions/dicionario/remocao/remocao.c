#include "./remocao.h"

int removendoPalavrasIngles(ArvVP *raiz,char *palavra,int unidade){
	int verifica = 0;

	if(raiz){
		if(raiz->info.unidade == unidade){
			if(removerPalavraIngles(&(raiz->info.palavrasIngles),palavra,unidade)){
				if(!(raiz->info.palavrasIngles)){
					printf("Como era a unica palavra o dicionario de entao %s foi deletado\n", raiz->info.palavra);
					removerNoArvVP(&raiz,raiz->info.palavra,unidade);
				}else{
					printf("Removido do dicionario de: %s\n", raiz->info.palavra);
				}
			}
			verifica = 1;
		}else if(strcmp(raiz->info.palavra,palavra) < 0){
			verifica = removendoPalavrasIngles(raiz->esq,palavra,unidade);
		}else{
			verifica = removendoPalavrasIngles(raiz->dir,palavra,unidade);	
		}
	}

	return verifica;
}

void menuRemoverPalavraIngles(ArvVP *arvVP){
	char palavra[50];
	int unidade;

	printf("Infome a palavra em ingles que deseja remover:");
	scanf("%[^\n]", palavra);

	printf("Infome a palavra em ingles que deseja remover:");
	scanf("%d", &unidade);
	setbuf(stdin,NULL);

	if(!removendoPalavrasIngles(arvVP,palavra,unidade)){
		printf("Nenhuma palavra foi encontrada!\n");
	}
}

void menuRemoverPalavraPortugues(ArvVP **arvVP){
	char palavra[50];
	int unidade;

	printf("Digite a palavra em portugues que queria remover:\n");
	scanf("%[^\n]",palavra);

	printf("Infome a palavra em ingles que deseja remover:");
	scanf("%d", &unidade);

	removerNoArvVP(arvVP, palavra,unidade);
}