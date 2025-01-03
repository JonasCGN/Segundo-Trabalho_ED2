#include "./backend.h"

InfoArvBB criaInfoBB(char *palavra){
	InfoArvBB info;

	sprintf(info.palavraIngles,"%s",palavra);
	info.unidades = NULL;

	return info;
}

static void insere(PalavraPortugues **pi,Data info,char *p_en,int unidade){
	Data promove;
	PalavraPortugues *raiz;
	raiz = NULL;
	PalavraPortugues *inserido;
	inserido = NULL;
	
	inserirPalavraPortugues(pi,info,&promove,&raiz,&inserido);
	
	InfoArvBB infoBB;
	infoBB = criaInfoBB(p_en);

	if(strcmp(info.palavraPortugues,(inserido)->info1.palavraPortugues) == 0){
		inserirPalavraIngles(&(inserido->info1.traducaoIngles),infoBB,unidade); 
	}else if(strcmp(info.palavraPortugues,(inserido)->info2.palavraPortugues) == 0){
		inserirPalavraIngles(&(inserido->info2.traducaoIngles),infoBB,unidade);
	}
	
}

Data criaInfo23(char *palavra){
	Data info;

	strcpy(info.palavraPortugues,palavra);
	info.traducaoIngles = NULL;

	return info;
}


char* alocarString(int tamanho){
	return (char*)calloc((unsigned int)tamanho,sizeof(char));
}

void recuperaDados(char *caminho,PalavraPortugues **raiz){
	FILE *arq;
	arq = fopen(caminho,"r");
	
	if(!arq){
		printf("Arquivo nao encontrado!");
	}else{
		char linha[50];
		int unidade = 0;
		char *result,*pt;

		while((result = fgets(linha,50,arq))){
			char *p_en,*pt_br;
			p_en = alocarString(50);
			pt_br = alocarString(50);

			if(strstr(result,"Unidade")){
				pt = strtok(result, "%% Unidade ");
				unidade = atoi(pt);
			}else{
				pt = strtok(result, ":;,");
				strcpy(p_en, pt);

				while(pt){
					pt = strtok(NULL, ":;,");

					if(pt){
						strncpy(pt_br,pt + 1,strlen(pt)); 

						if(strlen(pt_br)){
							Data info = criaInfo23(pt_br);
							insere(raiz,info,p_en,unidade);
						}
					}
				}
			}
			
			free(p_en);
			p_en = NULL;
			free(pt_br);
			pt_br = NULL;
		}	
	}

}