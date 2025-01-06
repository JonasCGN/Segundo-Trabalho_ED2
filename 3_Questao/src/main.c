#include "./utils/utils.h"

void insere(Unidade **pi,Data info){
	Data promove;
	Unidade *raiz;
	raiz = NULL;

	inserirUnidade(pi,info,&promove,&raiz);
}

void menuOpc(){
    printf("1 - Ocupar Nós Livres\n");
    printf("2 - Desocupar Nós\n");
    printf("3 - Exibir Alocação de Memória\n");
    printf("0 - Sair\n");
}

void menu(){
	int opc,maximo;
	Unidade *unidadeAlocao;
	unidadeAlocao = NULL;

	do{
        leia_int("Quantidade máxima de Blocos de memória: ", &maximo);
        if(maximo <= 0)
            printf("\nDigite uma quantidade positiva!\n\n");
    } while(maximo <= 0);

	iniciarPrograma(&unidadeAlocao,maximo);	

	exibirEmOrdem(unidadeAlocao);

	do{
		menuOpc();
		scanf("%d", &opc);
		
		switch (opc){
			case 1:
				noOcupar(&unidadeAlocao);
			break;
			
			case 2:
				noLivre(&unidadeAlocao);
			break;

			case 3:
				exibirEmOrdem(unidadeAlocao);
			break;

			case 0:
				printf("Saindo...\n");
			break;

			default:
				printf("Opcao Invalida!");
			break;
		}
	}while(opc != 0);

	liberaArvore23(unidadeAlocao);
}

int main(){

	menu();
	
	return 0;
}