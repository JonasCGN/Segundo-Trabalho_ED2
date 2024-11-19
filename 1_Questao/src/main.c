#include "./utils/utils.h"

void insere(PortugesIngles **pi,Info info){
	Info promove;
	PortugesIngles *raiz;
	raiz = NULL;

	inserirPalavraPortugues(pi,info,&promove,&raiz);
}

int main(){

	Info info1;
	info1.palavraPortugues = "ola";
	info1.traducaoIngles = NULL;

	Info info2;
	info2.palavraPortugues = "zebra";
	info2.traducaoIngles = NULL;

	Info info3;
	info3.palavraPortugues = "cuscuz";
	info3.traducaoIngles = NULL;

	Info info4;
	info4.palavraPortugues = "abobora";
	info4.traducaoIngles = NULL;

	Info info5;
	info5.palavraPortugues = "pera";
	info5.traducaoIngles = NULL;

	Info info6;
	info6.palavraPortugues = "uva";
	info6.traducaoIngles = NULL;

	PortugesIngles *pI;
	pI = NULL;
	
	insere(&pI,info1);
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info2);
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info6);
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info3);
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info4);
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info5);	
	exibirPreordem(pI);
	printf("\n");

	printf("%s\n", pI->info1.palavraPortugues);

	return 0;
}