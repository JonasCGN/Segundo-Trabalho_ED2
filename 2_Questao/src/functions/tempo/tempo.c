#include "tempo.h"

void caminhoPercorrido(PalavraPortugues *dicionario,char *palavra){
	if(dicionario){
		if(strcmp(palavra,dicionario->info.palavraPortugues) == 0){
			printf("%s\n", dicionario->info.palavraPortugues);
		}else{
			printf("%s -> ", dicionario->info.palavraPortugues);

			if(strcmp(palavra,dicionario->info.palavraPortugues) < 0){
				caminhoPercorrido(dicionario->esq,palavra);
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
		if(strcmp(palavra,dicionario->info.palavraPortugues) == 0){
			
		}else{
			if(strcmp(palavra,dicionario->info.palavraPortugues) < 0){
				tempoPercorre(dicionario->esq,palavra);
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
	recuperaDados("./src/database/teste2.txt",&dicionario);
	double tempo = 0,media= 0;
	int n = 30;
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
		printf("Caminho percorrido para buscar %s:",listaPalavra[i]);
		caminhoPercorrido(dicionario,listaPalavra[i]);
		printf("----------------------------------------\n");

		media += tempo;
	}
	printf("A media foi: %lf\n", media/n);

	// exibirEmOrdem(dicionario);

	liberarPalavraPortugues(dicionario);
}