#include "./backend.h"

Data criaInfoVP(char *palavra){
	Data info;

	sprintf(info.palavraPortugues,"%s",palavra);
	info.traducaoIngles = NULL;

	return info;
}

InfoArvBB criaInfoBB(char *palavra){
	InfoArvBB info;

	sprintf(info.palavraIngles,"%s",palavra);
	info.unidades = NULL;
	
	return info;
}

char* alocarString(int tamanho){
	return (char*)calloc((unsigned int)tamanho,sizeof(char));
}

void recuperaDados(PalavraPortugues **raiz){
	FILE *arq;
	arq = fopen("./src/database/teste.txt","r");
	PalavraPortugues *noEncontrado;

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
							Data info = criaInfoVP(pt_br);
							noEncontrado = inserePalavraPortugues(raiz,criaNo(info));

							InfoArvBB infoBB;
							infoBB = criaInfoBB(p_en);
							
							inserirPalavraIngles(&(noEncontrado->info.traducaoIngles),infoBB,unidade);
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