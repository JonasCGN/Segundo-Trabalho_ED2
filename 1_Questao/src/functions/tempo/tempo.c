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
	
	double media = 0,tempo = 0;
	int n = 30;
	recuperaDados("./src/database/teste2.txt",&dicionario);

	char *listaPalavra[] = {
		"onibus", "barramento", "inseto", "problema", 
		"bicicleta", "bolsa", "mochila", "bola", 
		"esfera", "livro", "barco", "caixa", 
		"sino", "passaro", "ponte", "garrafa", 
		"escova", "pao", "tijolo", "galho", 
		"banco", "gato", "xicara", "copo", 
		"carro", "automovel", "cadeira", "vaca", 
		"relogio", "nuvem"
	};

	for(int i=0;i<n;i++){
		tempo = tempoPercorre(dicionario,listaPalavra[i]);
		
		printf("----------------------------------------\n");
		printf("Tempo para buscar %s:",listaPalavra[i]);
		printf("%lf\n", tempo);
		media += tempo;
		printf("Caminho percorrido para buscar %s:",listaPalavra[i]);
		caminhoPercorrido(dicionario,listaPalavra[i]);
		printf("----------------------------------------\n");
	}
	printf("A media foi: %lf\n", media / n);
	// exibirEmOrdem(dicionario);

	liberaArvore23(dicionario);
}