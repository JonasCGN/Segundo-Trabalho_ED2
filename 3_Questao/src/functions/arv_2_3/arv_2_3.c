#include "arv_2_3.h"

int ehFolha(PortugesIngles *no){
	return no->esq == NULL;
}

PortugesIngles* criaNo(Info info, PortugesIngles *filhoEsq, PortugesIngles *filhoCen){
	PortugesIngles *no;
	no = (PortugesIngles*)malloc(sizeof(PortugesIngles));
	if(!no){
		printf("Nao foi possivel criar no\n");
	}

	no->info1 = info;
	no->esq = filhoEsq;
	no->cen = filhoCen;

	no->qtdInfo = 1;

	return no;
}

void adicionaChave(PortugesIngles *no,Info info,PortugesIngles *filho){
	
	if(strcmp(info.palavraPortugues, no->info1.palavraPortugues) > 0){
		no->info2 = info;
		no->dir = filho;
	}else{
		no->info2 = no->info1;
		no->dir = no->cen;
		no->info1 = info;
		no->cen = filho;
	}

	no->qtdInfo = 2;
}

PortugesIngles* quebraNo(PortugesIngles **no,Info valor,Info *promove,PortugesIngles **filho){
	PortugesIngles *maior;

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

	(*no)->qtdInfo = 1;
	return maior;
}

PortugesIngles* inserirPalavraPortugues(PortugesIngles **no, Info info, Info *promove, PortugesIngles **pai){
	PortugesIngles *maiorNo;
	Info promove1;
	maiorNo = NULL;

	if(*no == NULL){
		*no = criaNo(info,NULL,NULL);
	}else{
		if(ehFolha(*no)){
			if((*no)->qtdInfo == 1){
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
				if(((*no)->qtdInfo == 1) || (strcmp(info.palavraPortugues, (*no)->info2.palavraPortugues)< 0)){
					maiorNo = inserirPalavraPortugues(&((*no)->cen), info, promove,no);
				}else{
					maiorNo = inserirPalavraPortugues(&((*no)->dir), info, promove,no);
				}
			}

			if(maiorNo){
				if((*no)->qtdInfo == 1){
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

void exibirPreordem(PortugesIngles *ptIn){
	if(ptIn){
		printf("%s\n", ptIn->info1.palavraPortugues);
		if(ptIn->qtdInfo == 2){
			printf("%s\n", ptIn->info2.palavraPortugues);
		}

		exibirPreordem(ptIn->esq);
		exibirPreordem(ptIn->cen);
		if(ptIn->qtdInfo == 2)
			exibirPreordem(ptIn->dir);
	}
}

void exibirEmOrdem(PortugesIngles *ptIn){
	if(ptIn){
		exibirEmOrdem(ptIn->esq);

		printf("%s\n", ptIn->info1.palavraPortugues);

		exibirEmOrdem(ptIn->cen);
		if(ptIn->qtdInfo == 2){
			printf("%s\n", ptIn->info2.palavraPortugues);
			exibirEmOrdem(ptIn->dir);
		}
	}
}