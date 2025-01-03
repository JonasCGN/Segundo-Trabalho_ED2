#include "tempo.h"

void caminhoPercorrido(PalavraPortugues *dicionario,char *palavra){
	if(dicionario){
		if(strcmp(palavra,dicionario->info1.palavraPortugues) == 0){
			printf("%s\n", dicionario->info1.palavraPortugues);
		}else if(dicionario->n_infos == 2 && strcmp(palavra,dicionario->info2.palavraPortugues) == 0){
			printf("%s\n", dicionario->info2.palavraPortugues);
		}else{
			if(dicionario->n_infos == 1){
				printf("%s -> ", dicionario->info1.palavraPortugues);
			}else if(dicionario->n_infos == 2){
				printf("%s -> ", dicionario->info2.palavraPortugues);
			}

			if(strcmp(palavra,dicionario->info1.palavraPortugues) < 0){
				caminhoPercorrido(dicionario->esq,palavra);
			}else if(dicionario->n_infos == 1|| strcmp(palavra,dicionario->info2.palavraPortugues) < 0){
				caminhoPercorrido(dicionario->cen,palavra);
			}else{
				caminhoPercorrido(dicionario->dir,palavra);
			}
		}
	}
}

double tempoPercorre(PalavraPortugues *dicionario,char *palavra){
    clock_t inicio, fim;
    double tempo_gasto;

	inicio = clock();

	if(dicionario){
		if(strcmp(palavra,dicionario->info1.palavraPortugues) == 0){
			
		}else if(dicionario->n_infos == 2 && strcmp(palavra,dicionario->info2.palavraPortugues) == 0){

		}else{
			if(strcmp(palavra,dicionario->info1.palavraPortugues) < 0){
				tempoPercorre(dicionario->esq,palavra);
			}else if(dicionario->n_infos == 1|| strcmp(palavra,dicionario->info2.palavraPortugues) < 0){
				tempoPercorre(dicionario->cen,palavra);
			}else{
				tempoPercorre(dicionario->dir,palavra);
			}
		}
	}
	fim = clock();

	tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;


	return tempo_gasto;
} 

void calcularTempoBusca(){
	PalavraPortugues *dicionario;
	dicionario = NULL;
	recuperaDados("./src/database/teste.txt",&dicionario);

	char *listaPalavra[] = {
		"inseto","onibus","barramento","problema",
		"rede de computadores","ventilador","bicicleta","sistema",
		"rede de relacionamento","barramento","barramento","barramento",
		"barramento","barramento","barramento","barramento",
	};

	for(int i=0;i<9;i++){
		printf("----------------------------------------\n");
		printf("Tempo para buscar %s:",listaPalavra[i]);
		printf("%lf\n", tempoPercorre(dicionario,listaPalavra[i]));
		printf("Caminho percorrido para buscar %s:",listaPalavra[i]);
		caminhoPercorrido(dicionario,listaPalavra[i]);
		printf("----------------------------------------\n");
	}

	// exibirEmOrdem(dicionario);

	liberaArvore23(dicionario);
}