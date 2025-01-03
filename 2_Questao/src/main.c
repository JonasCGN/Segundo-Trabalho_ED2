#include "./utils/utils.h"

void teste(){
	PalavraPortugues *raiz;
	raiz = NULL;

	Data info[] = {
		{"abobora", NULL},
		{"cachorro", NULL},
		{"papagaio", NULL},
		{"ola", NULL},
		{"zebra", NULL},
		{"casa", NULL},
		{"pera", NULL},
		{"uva", NULL},
		{"gato", NULL}
	};
	int quant = sizeof(info) / sizeof(info[0]);
	printf("%d\n",quant);
	for(int i=0;i<quant;i++){
		inserePortuguesIngles(&raiz,info[i]);
	}

	char palavra1[] = "gato";
	char palavra2[] = "papagaio";

	removePortuguesIngles(&raiz,palavra1);
	removePortuguesIngles(&raiz,palavra2);

	exibeTodasPalavras(raiz);
}

int menuOpc(){
	int opc;

	printf("1 - Palavras da unidade em portugues e suas equivalentes em ingles\n");
	printf("2 - Palavras em portugues equivalentes em ingles\n");
	printf("3 - Remover palavra em ingles pela unidade\n");
	printf("4 - Remover palavra em portugues pela unidade\n");
	printf("5 - Exibe todas as palavras\n");
	printf("0 - Sair\n");

	scanf("%d", &opc);
	setbuf(stdin,NULL);

	return opc;
}

void menu(){
	PalavraPortugues *raiz;
	raiz = NULL;
	recuperaDados("./src/database/teste.txt",&raiz);

	exibeTodasPalavras(raiz);

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

				exibeArvoreVP(raiz, unidade);
			break;

			case 2:
				printf("Digite a palavra que deseja ver:\n");
				scanf("%[^\n]",palavra);

				exibePalavraPortuguesIngles(raiz, palavra);
			break;
			
			case 3:
				menuRemoverPalavraIngles(raiz);
			break;
			
			case 4:
				menuRemoverPalavraPortugues(&raiz);
			break;
			
			case 5:
				exibeTodasPalavras(raiz);
			break;

			case 0:
				printf("Saindo...\n");
			break;

			default:
				printf("Opcao Invalida!\n");
			break;
		}
	}while(opc != 0);

	liberarPalavraPortugues(raiz);
}

int main(){
	// teste();
	// menu();

	calcularTempoBusca();

	return 0;
}	