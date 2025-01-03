#include "unidade.h"

static int quantidadeEspaco(Data info){
	return (info.fim - info.ini) + 1;
}

static void exibeInfo(Data *unidade){
	if(unidade){
		printf("%d | %d\n",unidade->ini,unidade->fim);
	}
}

static Data *infoRequerida(Data *info1){
	return info1;
}

static Data *infoCorretaIni(Unidade *unidade,int info){
	Data *aux;
	aux = NULL;
	
	if(unidade){
		if(info == unidade->info1.ini){
			aux = infoRequerida(&(unidade->info1));
		}else{
			aux = infoRequerida(&(unidade->info2));
		}
	}

	return aux;
}

static Data *infoCorretaFim(Unidade *unidade,int info){
	Data *aux;
	aux = NULL;
	
	if(unidade){
		if(info == unidade->info1.fim){
			aux = infoRequerida(&(unidade->info1));
		}else{
			aux = infoRequerida(&(unidade->info2));
		}
	}

	return aux;
}

static int antecessorInfo(Data info){
	return info.ini - 1;
}

static int sucessorInfo(Data info){
	return info.fim + 1;
}

Data buscaBlocoTamanho(Unidade *unidade,int quant,int status, Unidade **noEscolhido){
	Data aux;

	if(unidade){
		if(quant <= quantidadeEspaco(unidade->info1) && unidade->info1.status == status){
			aux = unidade->info1;
			*noEscolhido = unidade;
		}else if(unidade->n_infos == 2 && quant <= quantidadeEspaco(unidade->info2) && unidade->info2.status == status){
			aux = unidade->info2;
			*noEscolhido = unidade;
		}else{
			aux = buscaBlocoTamanho(unidade->esq,quant,status,noEscolhido);
			if(!(*noEscolhido)){
				aux = buscaBlocoTamanho(unidade->cen,quant,status,noEscolhido);
			}
			if(!(*noEscolhido)){
				aux = buscaBlocoTamanho(unidade->dir,quant,status,noEscolhido);
			}
		}
	}

	return aux;
}

Unidade *buscaFim(Unidade *unidade,int info){
	Unidade *aux;
	aux = NULL;

	if(unidade){
		if(info == unidade->info1.fim){
			aux = unidade;
		}else if(unidade->n_infos == 2 && info == unidade->info2.fim){
			aux = unidade;
		}else{
			if(info < unidade->info1.fim){
				aux = buscaFim(unidade->esq,info);
			}else if(unidade->n_infos == 1 || info < unidade->info2.fim){
				aux = buscaFim(unidade->cen,info);
			}else{
				aux = buscaFim(unidade->dir,info);
			}
		}
	}

	return aux;
}

Unidade *buscaInicio(Unidade *unidade,int info){
	Unidade *aux;
	aux = NULL;

	if(unidade){
		if(info == unidade->info1.ini){
			aux = unidade;
		}else if(unidade->n_infos == 2 && info == unidade->info1.ini){
			aux = unidade;
		}else{
			if(info < unidade->info1.ini){
				aux = buscaInicio(unidade->esq,info);
			}else if(unidade->n_infos == 1 || info < unidade->info2.ini){
				aux = buscaInicio(unidade->cen,info);
			}else{
				aux = buscaInicio(unidade->dir,info);
			}
		}
	}

	return aux;
}

void exibeInfoUnidade(Unidade *unidade){
	if(unidade){
		printf("%d | %d\n",unidade->info1.ini,unidade->info1.fim);
		if(unidade->n_infos == 2){
			printf("%d | %d\n",unidade->info2.ini,unidade->info2.fim);
		}
	}
}

void atualizarNoTamanhoMax(Unidade **unidade,Data **atual,Data **antecessor,Data **sucessor){
	if(!(*antecessor)){
		(*atual)->fim = (**sucessor).fim;
		(*atual)->status = !((*atual)->status);
		printf("\n\n %d \n\n",arvore23_remover_ini(unidade,(**sucessor).ini));
	}else if(!(*sucessor)){
		(*antecessor)->fim = (**atual).fim;
		printf("\n\n %d \n\n",arvore23_remover_ini(unidade,(**atual).ini));
	}else{
		(*antecessor)->fim = (**sucessor).fim;
		printf("\n\n %d \n\n",arvore23_remover_ini(unidade,(**sucessor).ini));
		printf("\n\n %d \n\n",arvore23_remover_ini(unidade,(**atual).ini));
	}
}

void atualizarNoTamanhoMin(int tam,Data **atual,Data **antecessor,Data **sucessor){
	if(!(*antecessor)){
		(*atual)->fim -= tam;
		(*sucessor)->ini -= tam;
	}else if(!(*sucessor)){
		(*atual)->ini += tam;
		(*antecessor)->fim += tam;
	}else{
		(*atual)->fim -= tam;
		(*sucessor)->ini -= tam;
	}
}

void modificaNo(Unidade **unidade,int tamanho,int status){
	Unidade *antecessor,*sucessor,*noAtual;
	noAtual = NULL;
	Data aux;
	Data *infoAux,*infoAntecessor,*infoSucessor;

	aux = buscaBlocoTamanho(*unidade,tamanho,status,&noAtual);
	if(noAtual){
		antecessor = buscaFim(*unidade, antecessorInfo(aux));
		sucessor = buscaInicio(*unidade, sucessorInfo(aux));

		infoAntecessor = infoCorretaFim(antecessor, antecessorInfo(aux));
		infoSucessor = infoCorretaIni(sucessor, sucessorInfo(aux));

		printf("ATUAL\n");
		infoAux = infoCorretaIni(noAtual,aux.ini);
		exibeInfo(infoAux);

		printf("ANTECESSOR\n");
		exibeInfo(infoAntecessor);

		printf("SUCESSOR\n");
		exibeInfo(infoSucessor);

		if(tamanho == quantidadeEspaco(aux)){
			atualizarNoTamanhoMax(unidade,&infoAux,&infoAntecessor,&infoSucessor);
		}else if(tamanho < quantidadeEspaco(aux)){
			atualizarNoTamanhoMin(tamanho,&infoAux,&infoAntecessor,&infoSucessor);
		}

		exibirEmOrdem(*unidade);
	}else{
		printf("Nao a espaço disponivel!\n");
	}
}

void noOcupar(Unidade **unidade){
	int tamanho;
	
	exibirEmOrdem(*unidade);

	printf("Voce quer usar qual bloco digite o inicio:");
	scanf("%d",&tamanho);

	modificaNo(unidade,tamanho,LIVRE);
}

void noLivre(Unidade **unidade){
	int tamanho;

	exibirEmOrdem(*unidade);
	
	printf("Voce quer usar qual bloco digite o inicio:");
	scanf("%d",&tamanho);

	modificaNo(unidade,tamanho,OCUPADO);
}