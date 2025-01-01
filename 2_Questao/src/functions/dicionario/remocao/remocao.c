#include "./remocao.h"

int removeUnidadeIngles(PalavraIngles **raiz,char *palavra,int unidade){
	int verifica = 0;

	if(*raiz){
		if(strcmp(palavra,(*raiz)->info.palavraIngles) == 0){
			if(removerUnidadeLista(&((*raiz)->info.unidades),unidade)){
				verifica = 1;
				printf("Unidade removida com sucesso!\n");
			}

			if(!((*raiz)->info.unidades)){
				verifica = removerPalavraIngles(raiz,(*raiz));
			}

		}else{
			if(strcmp(palavra,(*raiz)->info.palavraIngles) < 0){
				verifica = removeUnidadeIngles(&((*raiz)->esq),palavra,unidade);
			}else if(strcmp(palavra,(*raiz)->info.palavraIngles) > 0){
				verifica = removeUnidadeIngles(&((*raiz)->dir),palavra,unidade);
			}
		}
		
	}

	return verifica;
}

int removendoPalavrasIngles(PalavraPortugues **raiz,char *palavra,int unidade){
	int verifica = 0;

	if(*raiz){
		verifica = removeUnidadeIngles((&((*raiz)->info.traducaoIngles)),palavra,unidade);

		if(verifica){
			if(!(*raiz)->info.traducaoIngles){
				removerNoPalavraPortugues(raiz,(*raiz)->info.palavraPortugues);
			}
		}

		if(!verifica)
			verifica = removendoPalavrasIngles(&((*raiz)->esq),palavra,unidade);
		if(!verifica)
			verifica = removendoPalavrasIngles(&((*raiz)->dir),palavra,unidade);
		
	}

	return verifica;
}

void menuRemoverPalavraIngles(PalavraPortugues *arvVP){
	char palavra[50];
	int unidade;

	printf("Infome a palavra em ingles que deseja remover:");
	scanf("%[^\n]", palavra);

	printf("Infome a unidade que deseja remover:");
	scanf("%d", &unidade);
	setbuf(stdin,NULL);

	if(removendoPalavrasIngles(&arvVP,palavra,unidade)){
		printf("A informacao:\nPalavra: %s\nUnidade: %d\n",palavra,unidade);
		printf("Unidade correspondente a palavra informada removido com sucesso!\n");
	}else{
		printf("Nenhuma palavra foi encontrada!\n");
	}
}

int removeInglesPortugues(PalavraPortugues **raiz,char *palavra,int unidade){
	int verifica = 0;

	if(*raiz){
		if(strcmp(palavra,(*raiz)->info.palavraPortugues) == 0){
			verifica = removePalavraInglesUnidade(&(*raiz)->info.traducaoIngles,unidade);
		}
		
		if(verifica){
			if(!(*raiz)->info.traducaoIngles){
				removerNoPalavraPortugues(raiz,(*raiz)->info.palavraPortugues);
			}
		}

		if(!verifica)
			verifica = removeInglesPortugues(&((*raiz)->esq),palavra,unidade);
		if(!verifica)
			verifica = removeInglesPortugues(&((*raiz)->dir),palavra,unidade);
	}

	return verifica;
}

void menuRemoverPalavraPortugues(PalavraPortugues **arvVP){
	char palavra[50];
	int unidade;

	printf("Digite a palavra em portugues que queria remover:\n");
	scanf("%[^\n]",palavra);

	printf("Infome a palavra em ingles que deseja remover:");
	scanf("%d", &unidade);

	if(removeInglesPortugues(arvVP,palavra,unidade)){
		printf("A informacao:\nPalavra: %s\nUnidade: %d\n",palavra,unidade);
		printf("Palavras correspondente da unidade a palavra informada removida com sucesso!\n");
	}else{
		printf("Palavra nao encontrada ou unidade incorreta!\n");
	}
}