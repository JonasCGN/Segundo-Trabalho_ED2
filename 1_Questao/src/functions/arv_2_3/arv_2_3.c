#include "arv_2_3.h"

int ehFolha(PalavraPortugues *no){
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

PalavraPortugues* inserirPalavraPortugues(PalavraPortugues **no, Data info, Data *promove, PalavraPortugues **pai){
	PalavraPortugues *maiorNo;
	Data promove1;
	maiorNo = NULL;

	if(*no == NULL){
		*no = criaNo(info,NULL,NULL);
	}else{
		if(ehFolha(*no)){
			if((*no)->n_infos == 1){
				adicionaChave(*no, info, NULL);
			}else{
				maiorNo = quebraNo(no, info, promove,NULL);
				if(!(*pai)){
					*no = criaNo(*promove, *no, maiorNo);
					maiorNo = NULL;
				}
			}
		}else{
			if(strcmp(info.palavraPortugues, (*no)->info1.palavraPortugues) < 0){
				maiorNo = inserirPalavraPortugues(&((*no)->esq), info, promove, no);
			}else{
				if(((*no)->n_infos == 1) || (strcmp(info.palavraPortugues, (*no)->info2.palavraPortugues) < 0)){
					maiorNo = inserirPalavraPortugues(&((*no)->cen), info, promove,no);
				}else{
					maiorNo = inserirPalavraPortugues(&((*no)->dir), info, promove,no);
				}
			}

			if(maiorNo){
				if((*no)->n_infos == 1){
					adicionaChave(*no, *promove, maiorNo);
					maiorNo = NULL;
				}else{
					maiorNo = quebraNo(no, *promove, &promove1, &maiorNo);
					*promove = promove1;
					if(!(*pai)){
						*no = criaNo(promove1, *no,maiorNo);
						maiorNo = NULL;
					}
				}
			}
		}
	}
	
	return maiorNo;
}

void exibirPreordem(PalavraPortugues *ptIn){
	if(ptIn){
		printf("%s -> ", ptIn->info1.palavraPortugues);
		if(ptIn->n_infos == 2){
			printf("%s -> ", ptIn->info2.palavraPortugues);
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

		printf("%s\n", ptIn->info1.palavraPortugues);

		exibirEmOrdem(ptIn->cen);
		if(ptIn->n_infos == 2){
			printf("%s\n", ptIn->info2.palavraPortugues);
			exibirEmOrdem(ptIn->dir);
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