#include "./utils/utils.h"

void insere(PalavraPortugues **pi,Data info){
	Data promove;
	PalavraPortugues *raiz;
	raiz = NULL;
	PalavraPortugues *inserido;

	inserirPalavraPortugues(pi,info,&promove,&raiz,&inserido);
}

void testeLista(){
	ListaUnidade *lista;
	lista = NULL;

	inserirUnidadeLista(&lista,1);
	inserirUnidadeLista(&lista,2);
	inserirUnidadeLista(&lista,3);
	inserirUnidadeLista(&lista,4);
	inserirUnidadeLista(&lista,5);

	removerUnidadeLista(&lista,1);
	removerUnidadeLista(&lista,2);
	removerUnidadeLista(&lista,3);
	removerUnidadeLista(&lista,4);
	removerUnidadeLista(&lista,5);

	exibirLista(lista);

	liberarLista(lista);
}

void teste3(){
	PalavraPortugues *raiz;
	raiz = NULL;
	recuperaDados("./src/database/teste.txt",(&raiz));

	exibirEmOrdem(raiz);

	printf("\n-------------------------Teste Item 1-------------------------\n");
	int unidade = 2;
	printf("Unidade %d\n",unidade);
	exibirEmOrdemUnidade(raiz, unidade);
	printf("\n---------------------------------------------------------------\n");

	printf("\n-------------------------Teste Item 2-------------------------\n");
	char palavra[] = "Bicleta";
	printf("%s\n",palavra);
	exibePalavraPortuguesIngles(raiz, "bicicleta");
	printf("\n---------------------------------------------------------------\n");

}

int menuOpc(){
	int opc;

	printf("1 - Palavras da unidade em portugues e suas equivalentes em ingles\n");
	printf("2 - Palavras em portugues equivalentes em ingles\n");
	printf("3 - Remover palavra em ingles pela unidade\n");
	printf("4 - Remover palavra em portugues pela unidade\n");
	// printf("5 - Exibe todas as palavras\n");
	printf("0 - Sair\n");

	scanf("%d", &opc);
	setbuf(stdin,NULL);

	return opc;
}

void menu(){
	PalavraPortugues *raiz;
	raiz = NULL;
	recuperaDados("./src/database/teste.txt",&raiz);

	exibirEmOrdem(raiz);

	// removendoPalavrasIngles(raiz,"Network",2);
	
	int opc;
	int unidade;
	char palavra[50];

	do{
		opc = menuOpc();

		switch (opc){
			case 1:
				printf("Digite a unidade que deseja ver:\n");
				scanf("%d", &unidade);
				setbuf(stdin,NULL);

				exibirEmOrdemUnidade(raiz, unidade);
			break;

			case 2:
				printf("Digite a palavra que deseja ver:\n");
				scanf("%[^\n]",palavra);

				exibePalavraPortuguesIngles(raiz, palavra);
				printf("\n");
			break;
			
			case 3:
				menuRemoverPalavraIngles(raiz);
			break;
			
			case 4:
				menuRemoverPalavraPortugues(&raiz);
			break;
			
			case 5:
				exibirEmOrdem(raiz);
			break;

			case 0:
				printf("Saindo...\n");
			break;

			default:
				printf("Opcao Invalida!\n");
			break;
		}
	}while(opc != 0);

	liberaArvore23(raiz);
}

int main() {
    // teste();
    
    menu();
	
	// teste3();

	// testeLista();
	// calcularTempoBusca();

	return 0;
}