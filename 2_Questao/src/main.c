#include "./utils/utils.h"

int menuOpc(){
	int opc;

	printf("1 - Palavras da unidade em portugues e suas equivalentes em ingles\n");
	printf("2 - Palavras em portugues equivalentes em ingles\n");
	printf("3 - Remover palavra em ingles pela unidade\n");
	printf("4 - Remover palavra em portugues pela unidade\n");
	printf("0 - Sair\n");

	scanf("%d", &opc);
	setbuf(stdin,NULL);

	return opc;
}

void menu(){
	ArvVP *raiz;
	raiz = NULL;
	recuperaDados(&raiz);

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
				
			break;
			
			case 4:
				
			break;
			
			case 0:
				printf("Saindo...\n");
			break;

			default:
				printf("Opcao Invalida!\n");
			break;
		}
	}while(opc != 0);
}

int main(){
	
	menu();

	return 0;
}	