#include "./remocao.h"

// a 3 pelo que entendi remove a inglês de todas as português
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
		if(!(verifica = removeUnidadeIngles((&((*raiz)->info1.traducaoIngles)),palavra,unidade))){
			verifica = removeUnidadeIngles((&((*raiz)->info2.traducaoIngles)),palavra,unidade);
		}

		if(verifica){
			if(!(*raiz)->info1.traducaoIngles){
				arvore23_remover(raiz,(*raiz)->info1.palavraPortugues);
			}else if(!(*raiz)->info2.traducaoIngles){
				arvore23_remover(raiz,(*raiz)->info2.palavraPortugues);
			}
		}

		if(!verifica)
			verifica = removendoPalavrasIngles(&((*raiz)->esq),palavra,unidade);
		if(!verifica)
			verifica = removendoPalavrasIngles(&((*raiz)->cen),palavra,unidade);
		if(!verifica)
			verifica = removendoPalavrasIngles(&((*raiz)->dir),palavra,unidade);
	}

	return verifica;
}

void menuRemoverPalavraIngles(PalavraPortugues *arv23){
	char palavra[50];
	int unidade;

	printf("Infome a palavra em ingles que deseja remover:");
	scanf("%[^\n]", palavra);

	printf("Infome a unidade que deseja remover:");
	scanf("%d", &unidade);
	setbuf(stdin,NULL);

	if(removendoPalavrasIngles(&arv23,palavra,unidade)){
		printf("A informacao:\nPalavra: %s\nUnidade: %d\n",palavra,unidade);
		printf("Unidade correspondente a palavra informada removido com sucesso!\n");
	}else{
		printf("Nenhuma palavra foi encontrada!\n");
	}
}

int removeInglesPortugues(PalavraPortugues **raiz,char *palavra,int unidade){
	int verifica = 0;

	if(*raiz){
		if(strcmp(palavra,(*raiz)->info1.palavraPortugues) == 0){
			verifica = removePalavraInglesUnidade(&(*raiz)->info1.traducaoIngles,unidade);
		}else if(strcmp(palavra,(*raiz)->info2.palavraPortugues) == 0){
			verifica = removePalavraInglesUnidade(&(*raiz)->info2.traducaoIngles,unidade);
		}
		
		if(verifica){
			if(!(*raiz)->info1.traducaoIngles){
				arvore23_remover(raiz,(*raiz)->info1.palavraPortugues);
			}else if(!(*raiz)->info2.traducaoIngles){
				arvore23_remover(raiz,(*raiz)->info2.palavraPortugues);
			}
		}

		if(!verifica)
			verifica = removeInglesPortugues(&((*raiz)->esq),palavra,unidade);
		if(!verifica)
			verifica = removeInglesPortugues(&((*raiz)->cen),palavra,unidade);
		if(!verifica)
			verifica = removeInglesPortugues(&((*raiz)->dir),palavra,unidade);
	}

	return verifica;
}

// a 4 pelo que entendi remove a unidade de todas as inglês de uma palavra português
void menuRemoverPalavraPortugues(PalavraPortugues **arv23){
	char palavra[50];
	int unidade;

	printf("Digite a palavra em portugues que queria remover:\n");
	scanf("%[^\n]",palavra);

	printf("Infome a unidade que deseja remover:");
	scanf("%d", &unidade);

	if(removeInglesPortugues(arv23,palavra,unidade)){
		printf("A informacao:\nPalavra: %s\nUnidade: %d\n",palavra,unidade);
		printf("Palavras correspondente da unidade a palavra informada removida com sucesso!\n");
	}else{
		printf("Palavra nao encontrada ou unidade incorreta!\n");
	}
}