#include "./backend.h"

Info criaInfoVP(char *palavra,int unidade){
	Info info;

	sprintf(info.palavra,"%s",palavra);
	info.unidade = unidade;
	info.palavrasIngles = NULL;

	return info;
}

InfoArvBB criaInfoBB(char *palavra,int unidade){
	InfoArvBB info;

	sprintf(info.palavra,"%s",palavra);
	info.unidade = unidade;

	return info;
}

char* alocarString(int tamanho){
	return (char*)calloc((unsigned int)tamanho,sizeof(char));
}

void recuperaDados(ArvVP **raiz){
	FILE *arq;
	arq = fopen("./src/database/teste.txt","r");
	ArvVP *noEncontrado;

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
							Info info = criaInfoVP(pt_br,unidade);
							noEncontrado = insereArvVP(raiz,criaNo(info));

							InfoArvBB infoBB;
							infoBB = criaInfoBB(p_en,unidade);
							
							inserirPalavraIngles(&(noEncontrado->info.palavrasIngles),infoBB);
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