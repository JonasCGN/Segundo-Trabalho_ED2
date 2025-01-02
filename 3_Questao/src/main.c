#include "./utils/utils.h"

void insere(Unidade **pi,Data info){
	Data promove;
	Unidade *raiz;
	raiz = NULL;

	inserirPalavraPortugues(pi,info,&promove,&raiz);
}

void teste(){
	Unidade *pI;
	pI = NULL;
	
	int qtd_info = 100;

	for(int i=0;i<qtd_info;i++){
		insere(&pI,(Data){i * 10,((i+1)*10)-1,rand() % 2});
	}

	arvore23_remover(&pI,500);

	exibirEmOrdem(pI);

	liberaArvore23(pI);
}

void menuOpc(){
    printf("1 - Ocupar Nós Livres\n");
    printf("2 - Desocupar Nós\n");
    printf("3 - Exibir Alocação de Memória\n");
    printf("0 - Sair\n");
}

void menu(){
	int opc;
	Unidade *unidadeAlocao;
	unidadeAlocao = NULL;

	// iniciarPrograma();	
	int qtd_info = 100;

	int ini = 0,fim = 0,status = 0;

	for(int i=0;i<qtd_info;i++){
		fim = ini + rand() % 100;

		insere(&unidadeAlocao,(Data){ini,fim,status});
		
		status = !status;
		ini = fim + 1;	
	}

	exibirEmOrdem(unidadeAlocao);

	do{
		menuOpc();
		scanf("%d", &opc);
		
		switch (opc){
			case 1:
				// noLivre(&unidadeAlocao);
			break;
			
			case 2:
				noOcupar(&unidadeAlocao);
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

void teste1(){
	Unidade *unidadeAlocao;
	unidadeAlocao = NULL;

	// iniciarPrograma();	
	int qtd_info = 100;

	int ini = 0,fim = 0,status = 0;

	for(int i=0;i<qtd_info;i++){
		fim = ini + rand() % 100;

		insere(&unidadeAlocao,(Data){ini,fim,status});
		
		status = !status;
		ini = fim + 1;	
	}

	noOcupar(&unidadeAlocao);
	// noLivre(&unidadeAlocao);

	liberaArvore23(unidadeAlocao);
}

int main(){
	// teste();

	// menu();

	teste1();
	return 0;
}