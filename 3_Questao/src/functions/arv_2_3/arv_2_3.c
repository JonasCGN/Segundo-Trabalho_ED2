#include "arv_2_3.h"

int ehFolha(Unidade *no){
	return no->esq == NULL;
}

Unidade* criaNo(Data info, Unidade *filhoEsq, Unidade *filhoCen){
	Unidade *no;
	no = (Unidade*)malloc(sizeof(Unidade));
	if(!no){
		printf("Nao foi possivel criar no\n");
	}

	no->info1 = info;
	no->esq = filhoEsq;
	no->cen = filhoCen;

	no->n_infos = 1;

	return no;
}

void adicionaChave(Unidade *no,Data info,Unidade *filho){
	
	if(info.ini > no->info1.ini){
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

Unidade* quebraNo(Unidade **no,Data valor,Data *promove,Unidade **filho){
	Unidade *maior;

	if(valor.ini > (*no)->info2.ini){
		*promove = (*no)->info2;
		if(filho)
			maior = criaNo(valor, (*no)->dir, *filho);
		else
			maior = criaNo(valor, (*no)->dir, NULL);

	}else if(valor.ini > (*no)->info1.ini){
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

Unidade* inserirUnidade(Unidade **no, Data info, Data *promove, Unidade **pai){
	Unidade *maiorNo;
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
			if(info.ini < (*no)->info1.ini){
				maiorNo = inserirUnidade(&((*no)->esq), info, promove, no);
			}else{
				if(((*no)->n_infos == 1) || (info.ini < (*no)->info2.ini)){
					maiorNo = inserirUnidade(&((*no)->cen), info, promove,no);
				}else{
					maiorNo = inserirUnidade(&((*no)->dir), info, promove,no);
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

void exibeInfo(Data info){
	printf("|%d||%d| = %s\n",info.ini,info.fim,statusInfo(info.status));
}

void exibirPreordem(Unidade *arv23){
	if(arv23){
		exibeInfo(arv23->info1);
		if(arv23->n_infos == 2){
			exibeInfo(arv23->info2);
		}

		exibirPreordem(arv23->esq);
		exibirPreordem(arv23->cen);
		if(arv23->n_infos == 2)
			exibirPreordem(arv23->dir);
	}
}

void exibirEmOrdem(Unidade *arv23){
	if(arv23){
		exibirEmOrdem(arv23->esq);

		exibeInfo(arv23->info1);

		exibirEmOrdem(arv23->cen);
		if(arv23->n_infos == 2){
			exibeInfo(arv23->info2);
			exibirEmOrdem(arv23->dir);
		}
	}
}

void liberaArvore23(Unidade *raiz){
	if(raiz){

		liberaArvore23(raiz->esq);
		liberaArvore23(raiz->cen);
		if(raiz->n_infos == 2){
			liberaArvore23(raiz->dir);
		}
		free(raiz);
		raiz = NULL;
	}
}