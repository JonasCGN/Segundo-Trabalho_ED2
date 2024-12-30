#include "./utils/utils.h"

void insere(PortugesIngles **pi,Info info){
	Info promove;
	PortugesIngles *raiz;
	raiz = NULL;

	inserirPalavraPortugues(pi,info,&promove,&raiz);
}

int main(){

	Info info1;
	info1.palavraPortugues = "a";
	info1.traducaoIngles = NULL;

	Info info2;
	info2.palavraPortugues = "b";
	info2.traducaoIngles = NULL;

	Info info3;
	info3.palavraPortugues = "c";
	info3.traducaoIngles = NULL;

	Info info4;
	info4.palavraPortugues = "d";
	info4.traducaoIngles = NULL;

	Info info5;
	info5.palavraPortugues = "e";
	info5.traducaoIngles = NULL;

	Info info6;
	info6.palavraPortugues = "f";
	info6.traducaoIngles = NULL;

	Info info7;
	info7.palavraPortugues = "g";
	info7.traducaoIngles = NULL;

	PortugesIngles *pI;
	pI = NULL;
	
	insere(&pI,info1);
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info2);
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

	insere(&pI,info6);	
	exibirPreordem(pI);
	printf("\n");

	insere(&pI,info7);	
	exibirPreordem(pI);
	printf("\n");

	exibirEmOrdem(pI);

	liberaArvore23(pI);

	return 0;
}