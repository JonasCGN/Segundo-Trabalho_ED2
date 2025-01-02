#include "unidade.h"

static int quantidadeEspaco(Data info){
	return info.fim - info.ini;
}

Data buscaBloco(Unidade *unidade,int quant,int status, Unidade **noEscolhido){
	Data aux;

	if(unidade){
		if(quant <= quantidadeEspaco(unidade->info1) && unidade->info1.status == status){
			aux = unidade->info1;
			*noEscolhido = unidade;
		}else if(unidade->n_infos == 2 && quant <= quantidadeEspaco(unidade->info2) && unidade->info2.status == status){
			aux = unidade->info2;
			*noEscolhido = unidade;
		}else{
			aux = buscaBloco(unidade->esq,quant,status,noEscolhido);
			aux = buscaBloco(unidade->cen,quant,status,noEscolhido);
			aux = buscaBloco(unidade->dir,quant,status,noEscolhido);
		}
	}

	return aux;
}

Unidade *atualizaInfoPos(Unidade **noEscolhido,Data info,int quant){
	Unidade *noAtualizado;
	noAtualizado = NULL;

	if(*noEscolhido){
		if(info.fim + quant  == (*noEscolhido)->info1.ini){
			if(info.fim == info.ini){
				(*noEscolhido)->info1.ini = info.fim;
			}else{
				(*noEscolhido)->info1.ini = info.fim + 1;
			}
			noAtualizado = (*noEscolhido);
		}else if((*noEscolhido)->n_infos == 2 && info.fim + quant == (*noEscolhido)->info2.ini){
			if(info.fim == info.ini){
				(*noEscolhido)->info2.ini = info.fim;
			}else{
				(*noEscolhido)->info2.ini = info.fim + 1;
			}
			noAtualizado = (*noEscolhido);
		}else{
			noAtualizado = atualizaInfoPos(&((*noEscolhido)->esq),info,quant);
			noAtualizado = atualizaInfoPos(&((*noEscolhido)->cen),info,quant);
			noAtualizado = atualizaInfoPos(&((*noEscolhido)->dir),info,quant);
		}
	}

	return noAtualizado;
}

Unidade *atualizarInfo(Unidade **noEscolhido,Data info,int quant){
	Unidade *noAtualizado;
	noAtualizado = NULL;

	if(*noEscolhido){
		if(info.ini == (*noEscolhido)->info1.ini){
			(*noEscolhido)->info1.fim -= quant;
			noAtualizado = atualizaInfoPos(noEscolhido,(*noEscolhido)->info1,quant+1);
		}else if((*noEscolhido)->n_infos == 2 && info.ini == (*noEscolhido)->info2.ini){
			(*noEscolhido)->info2.fim -= quant;
			noAtualizado = atualizaInfoPos(noEscolhido,(*noEscolhido)->info2,quant+1);
		}else{
			noAtualizado = atualizarInfo(&((*noEscolhido)->esq),info,quant);
			noAtualizado = atualizarInfo(&((*noEscolhido)->cen),info,quant);
			noAtualizado = atualizarInfo(&((*noEscolhido)->dir),info,quant);
		}
	}

	return noAtualizado;
}

void concatenar(Unidade **unidade,Data info,Data *infoAtualizada){
	if(*unidade){
		if(info.ini - 1 == (*unidade)->info1.fim){
			(*unidade)->info1.fim = infoAtualizada->fim;
			arvore23_remover(unidade,infoAtualizada->ini);
		}else if((*unidade)->n_infos == 2 && info.ini == (*unidade)->info2.fim){
			(*unidade)->info2.fim = infoAtualizada->fim;
			arvore23_remover(unidade,infoAtualizada->ini);
		}else{
			concatenar(&((*unidade)->esq),info,infoAtualizada);
			concatenar(&((*unidade)->cen),info,infoAtualizada);
			concatenar(&((*unidade)->dir),info,infoAtualizada);
		}
	}
}

void atualizarNo(Unidade **unidade,int tamanho,Unidade **noEscolhido,Data info){
	Unidade *atualizado;
	atualizado = NULL;

	if(tamanho < quantidadeEspaco(info)){
		atualizado = atualizarInfo(noEscolhido,info,tamanho);
	}else if(tamanho == quantidadeEspaco(info)){
		atualizado = atualizarInfo(noEscolhido,info,tamanho);
		arvore23_remover(unidade,info.ini);

		if(atualizado->info1.ini == info.ini){
			concatenar(unidade,info,&(atualizado->info1));
		}else if(atualizado->n_infos == 2 && atualizado->info2.ini == info.ini){
			concatenar(unidade,info,&(atualizado->info2));
		}
	}
}

void noOcupar(Unidade **unidade){
	Data aux;
	Unidade *noEscolhido;
	noEscolhido = NULL;

	int tamanho = 94;
	int status = 0;

	// printf("Voce quer usar qual bloco digite o inicio:");
	// scanf("%d",&tamanho);
	exibirEmOrdem(*unidade);

	aux = buscaBloco(*unidade,tamanho,status,&noEscolhido);

	if(noEscolhido){
		printf("Info Escolhido:\n");
		printf("%d - %d\n",aux.ini,aux.fim);
		atualizarNo(unidade,tamanho,&noEscolhido,aux);
		exibirEmOrdem(*unidade);
	}else{
		printf("Impossivel alocar espaço\n");
	}
}

void noLivre(Unidade **unidade){
	Data aux;
	Unidade *noEscolhido;
	noEscolhido = NULL;

	int tamanho = 10;
	int status = 1;

	// printf("Voce quer usar qual bloco digite o inicio:");
	// scanf("%d",&tamanho);
	exibirEmOrdem(*unidade);

	aux = buscaBloco(*unidade,tamanho,status,&noEscolhido);

	if(noEscolhido){
		printf("Info Escolhido:\n");
		printf("%d - %d\n",aux.ini,aux.fim);
		atualizarNo(unidade,tamanho,&noEscolhido,aux);
		exibirEmOrdem(*unidade);

	}
}