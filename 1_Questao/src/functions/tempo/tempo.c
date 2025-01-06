#include "tempo.h"

static Data criaInfo23(char *palavra){
	Data info;

	strcpy(info.palavraPortugues,palavra);
	info.traducaoIngles = NULL;

	return info;
}

static void insere(PalavraPortugues **pi,Data info){
	Data promove;
	PalavraPortugues *raiz;
	raiz = NULL;
	PalavraPortugues *inserido;

	inserirPalavraPortugues(pi,info,&promove,&raiz,&inserido);
}


int caminhoPercorrido(PalavraPortugues *dicionario,char *palavra){
	int caminho = 0;
	if(dicionario){
		if(strcmp(palavra,dicionario->info1.palavraPortugues) == 0){
			printf("%s\n", dicionario->info1.palavraPortugues);
			caminho ++;
		}else if(dicionario->n_infos == 2 && strcmp(palavra,dicionario->info2.palavraPortugues) == 0){
			printf("%s\n", dicionario->info2.palavraPortugues);
			caminho ++;

		}else{
			if(dicionario->n_infos == 1){
				printf("%s -> ", dicionario->info1.palavraPortugues);
				caminho ++;
			}else if(dicionario->n_infos == 2){
				printf("%s -> ", dicionario->info2.palavraPortugues);
				caminho ++;
			}

			if(strcmp(palavra,dicionario->info1.palavraPortugues) < 0){
				caminho += caminhoPercorrido(dicionario->esq,palavra);
			}else if(dicionario->n_infos == 1|| strcmp(palavra,dicionario->info2.palavraPortugues) < 0){
				caminho += caminhoPercorrido(dicionario->cen,palavra);
			}else{
				caminho += caminhoPercorrido(dicionario->dir,palavra);
			}
		}
	}

	return caminho;
}

void tempoPercorre(PalavraPortugues *dicionario,char *palavra){
	if(dicionario){
		if(strcmp(palavra,dicionario->info1.palavraPortugues) == 0){
			
		}else if(dicionario->n_infos == 2 && strcmp(palavra,dicionario->info2.palavraPortugues) == 0){

		}else{
			if(strcmp(palavra,dicionario->info1.palavraPortugues) < 0){
				tempoPercorre(dicionario->esq,palavra);
			}else if(dicionario->n_infos == 1 || strcmp(palavra,dicionario->info2.palavraPortugues) < 0){
				tempoPercorre(dicionario->cen,palavra);
			}else if(dicionario->n_infos == 2){
				tempoPercorre(dicionario->dir,palavra);
			}
		}
	}
} 

void calcularTempoBusca(){
	PalavraPortugues *dicionario;
	dicionario = NULL;
	clock_t inicio, fim;
	double media = 0,tempo = 0;
	int n = 30,quant=100000,tempo_total=0;
	// recuperaDados("./src/database/teste2.txt",&dicionario);
	// char *listaPalavra[] = {
	// 	"onibus", "barramento", "inseto", "problema", 
	// 	"bicicleta", "bolsa", "mochila", "bola", 
	// 	"esfera", "livro", "barco", "caixa", 
	// 	"sino", "passaro", "ponte", "garrafa", 
	// 	"escova", "pao", "tijolo", "galho", 
	// 	"banco", "gato", "xicara", "copo", 
	// 	"carro", "automovel", "cadeira", "vaca", 
	// 	"relogio", "nuvem"
	// };

	char palavra[10];

	for(int i=0;i < quant;i++){
		sprintf(palavra,"%d",i);
		insere(&dicionario,criaInfo23(palavra));
	}

	for(int i=0;i<n;i++){
		sprintf(palavra,"%d",(quant/2) - 1 - i);
		inicio = clock();
		tempoPercorre(dicionario,palavra);
		fim = clock();
		tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
		
		// printf("----------------------------------------\n");
		// printf("Tempo para buscar %s:",palavra);
		printf("%lf\n", tempo);
		media += tempo;
		// printf("Caminho percorrido para buscar %s:",palavra);
		// printf("Tamanho do camina: %d\n",tempo_total += caminhoPercorrido(dicionario,palavra));
		// printf("----------------------------------------\n");
	}

	// for(int i=0;i<n;i++){
	// 	inicio = clock();
	// 	tempoPercorre(dicionario,listaPalavra[i]);
	// 	fim = clock();
	// 	tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
		
	// 	printf("----------------------------------------\n");
	// 	printf("Tempo para buscar %s:",listaPalavra[i]);
	// 	printf("%lf\n", tempo);
	// 	media += tempo;
	// 	printf("Caminho percorrido para buscar %s:",listaPalavra[i]);
	// 	printf("Tamanho do camina: %d\n",caminhoPercorrido(dicionario,listaPalavra[i]));
	// 	printf("----------------------------------------\n");
	// }
	
	printf("%lf\n", media);
	printf("O total de caminho percorrido foi: %d\n", tempo_total);

	liberaArvore23(dicionario);
}