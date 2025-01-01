#include "arv_2_3.h"

static int ehFolha(PalavraPortugues *no){
	return no->esq == NULL;
}

PalavraPortugues* criaNo(Data info, PalavraPortugues *filhoEsq, PalavraPortugues *filhoCen){
	PalavraPortugues *no;
	no = (PalavraPortugues*)malloc(sizeof(PalavraPortugues));
	if(!no){
		printf("Nao foi possivel criar no\n");
	}

	no->info1 = info;
	no->esq = filhoEsq;
	no->cen = filhoCen;

	no->n_infos = 1;

	return no;
}

void adicionaChave(PalavraPortugues *no,Data info,PalavraPortugues *filho){
	
	if(strcmp(info.palavraPortugues, no->info1.palavraPortugues) > 0){
		no->info2 = info;
		no->dir = filho;
	}else{
		no->info2 = no->info1;
		no->dir = no->cen;
		no->info1 = info;
		no->cen = filho;
	}

	no->n_infos = 2;
}

PalavraPortugues* quebraNo(PalavraPortugues **no,Data valor,Data *promove,PalavraPortugues **filho){
	PalavraPortugues *maior;
	
	if(strcmp(valor.palavraPortugues, (*no)->info2.palavraPortugues) > 0){
		*promove = (*no)->info2;
		if(filho)
			maior = criaNo(valor, (*no)->dir, *filho);
		else
			maior = criaNo(valor, (*no)->dir, NULL);

	}else if(strcmp(valor.palavraPortugues, (*no)->info1.palavraPortugues) > 0){
		*promove = valor;
		
		if(filho)
			maior = criaNo((*no)->info2,*filho,(*no)->dir);
		else
			maior = criaNo((*no)->info2,NULL,(*no)->dir);

	}else{
		*promove = (*no)->info1;
		maior = criaNo((*no)->info2,(*no)->cen,(*no)->dir);
		(*no)->info1 = valor;
		if(filho)
			(*no)->cen = *filho;
		else
			(*no)->cen = NULL;
	}

	(*no)->n_infos = 1;
	return maior;
}


static int comparaPalavraNo(Data info1,Data info2,Data info3){
	return strcmp(info1.palavraPortugues,info2.palavraPortugues) == 0 || strcmp(info1.palavraPortugues,info3.palavraPortugues) == 0;
}

static PalavraPortugues* noPalavra(Data info,PalavraPortugues *no,PalavraPortugues *maiorNo){
	PalavraPortugues *noInserido;

	if(strcmp(info.palavraPortugues,no->info1.palavraPortugues) == 0){
		noInserido = no;
	}else if(strcmp(info.palavraPortugues,(maiorNo)->info1.palavraPortugues) == 0){
		noInserido = maiorNo;
	}else{
		noInserido = NULL;
	}

	return noInserido;
}

static int comparaPalavraUnidade(Data info1,Data info2){
	return strcmp(info1.palavraPortugues, info2.palavraPortugues) < 0;
}

PalavraPortugues* inserirPalavraPortugues(PalavraPortugues **no, Data info, Data *promove, PalavraPortugues **pai,PalavraPortugues **noInserido){
	PalavraPortugues *maiorNo;
	Data promove1;
	maiorNo = NULL;

	if(*no == NULL){
		*no = criaNo(info,NULL,NULL);
		*noInserido = (*no);
	}else{
		if(comparaPalavraNo(info,(*no)->info1,(*no)->info2)){
			*noInserido = (*no);
		}else if(ehFolha(*no)){
			if((*no)->n_infos == 1){
				adicionaChave(*no, info, NULL);
				// *noInserido = *no;
				if(comparaPalavraNo(info,(*no)->info1,(*no)->info2)){
					*noInserido = (*no);
				}
			}else{
				maiorNo = quebraNo(no, info, promove,NULL);
				*noInserido = noPalavra(info,*no,maiorNo);

				if(!(*pai)){
					*no = criaNo(*promove, *no, maiorNo);
					maiorNo = NULL;
				}
				
				if(strcmp(info.palavraPortugues,(*no)->info1.palavraPortugues) == 0){
					*noInserido = *no;
				}
			}
		}else{
			if(comparaPalavraUnidade(info,(*no)->info1)){
				maiorNo = inserirPalavraPortugues(&((*no)->esq), info, promove, no,noInserido);
			}else{
				if(((*no)->n_infos == 1) || comparaPalavraUnidade(info,(*no)->info2)){
					maiorNo = inserirPalavraPortugues(&((*no)->cen), info, promove,no,noInserido);
				}else if((*no)->n_infos == 2 && comparaPalavraUnidade((*no)->info2,info)){
					maiorNo = inserirPalavraPortugues(&((*no)->dir), info, promove,no,noInserido);
				}else{
					*noInserido = (*no);
				}
			}

			if(maiorNo){
				if((*no)->n_infos == 1){
					adicionaChave(*no, *promove, maiorNo);

					if(comparaPalavraNo(info,(*no)->info1,(*no)->info2)){
						*noInserido = (*no);
					}
					
					maiorNo = NULL;
				}else{
					maiorNo = quebraNo(no, *promove, &promove1, &maiorNo);
					*promove = promove1;

					*noInserido = noPalavra(info,*no,maiorNo);

					if(!(*pai)){
						*no = criaNo(promove1, *no,maiorNo);
						maiorNo = NULL;
					}

					if(strcmp(info.palavraPortugues,(*no)->info1.palavraPortugues) == 0){
						*noInserido = *no;
					}
				}
			}
		}
	}
	
	return maiorNo;
}

void exibirPreordem(PalavraPortugues *ptIn){
	if(ptIn){
		exibeInfo(ptIn->info1);
		if(ptIn->n_infos == 2){
			exibeInfo(ptIn->info2);
		}

		exibirPreordem(ptIn->esq);
		exibirPreordem(ptIn->cen);
		if(ptIn->n_infos == 2)
			exibirPreordem(ptIn->dir);
	}
}

void exibirEmOrdem(PalavraPortugues *ptIn){
	if(ptIn){
		exibirEmOrdem(ptIn->esq);

		exibeInfo(ptIn->info1);

		exibirEmOrdem(ptIn->cen);
		if(ptIn->n_infos == 2){
			exibeInfo(ptIn->info2);
			exibirEmOrdem(ptIn->dir);
		}
	}
}

void exibeInfo(Data info){
	printf("------------------------------------\n");
	printf("%s\n", info.palavraPortugues);
	exibirENOrdem(info.traducaoIngles);
	printf("\n------------------------------------\n");
}

void exibeInfoUnidade(Data info,int unidade){
	printf("------------------------------------\n");
	printf("%s\n", info.palavraPortugues);
	exibeInglesUnidade(info.traducaoIngles,unidade);
	printf("\n------------------------------------\n");
}

void exibirEmOrdemUnidade(PalavraPortugues *ptIn,int unidade){
	if(ptIn){
		exibirEmOrdemUnidade(ptIn->esq,unidade);

		if(verificaInglesUnidade(ptIn->info1.traducaoIngles,unidade)){
			exibeInfoUnidade(ptIn->info1,unidade);
		}

		exibirEmOrdemUnidade(ptIn->cen,unidade);
		if(ptIn->n_infos == 2){
			if(verificaInglesUnidade(ptIn->info2.traducaoIngles,unidade)){
				exibeInfoUnidade(ptIn->info2,unidade);
			}
			exibirEmOrdemUnidade(ptIn->dir,unidade);
		}
	}
}

void exibePalavraPortuguesIngles(PalavraPortugues *ptBR,char *palavra){
	if(ptBR){
		if(strcmp(palavra,ptBR->info1.palavraPortugues) == 0){
			exibirENOrdem(ptBR->info1.traducaoIngles);
		}else if(ptBR->n_infos == 2 && strcmp(palavra,ptBR->info2.palavraPortugues) == 0){
			exibirENOrdem(ptBR->info2.traducaoIngles);
		}
		
		if(strcmp(palavra,ptBR->info1.palavraPortugues) < 0){
			exibePalavraPortuguesIngles(ptBR->esq,palavra);
		}else if(ptBR->n_infos == 1 || strcmp(palavra,ptBR->info2.palavraPortugues) < 0){
			exibePalavraPortuguesIngles(ptBR->cen,palavra);
		}else{
			exibePalavraPortuguesIngles(ptBR->dir,palavra);
		}
	}
}

void liberaArvore23(PalavraPortugues *raiz){
	if(raiz){
		liberaArvore23(raiz->esq);
		liberaArvore23(raiz->cen);
		if(raiz->n_infos == 2)
			liberaArvore23(raiz->dir);
		free(raiz);
	}
}