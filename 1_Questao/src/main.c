#include "./utils/utils.h"

void insere(PalavraPortugues **pi,Data info){
	Data promove;
	PalavraPortugues *raiz;
	raiz = NULL;

	inserirPalavraPortugues(pi,info,&promove,&raiz);
}

int main() {
    PalavraPortugues *raiz = NULL;
    Data infos[26];
    char *palavrasPT[] = {
        "abacaxi", "banana", "cachorro", "dado", "elefante", "foca", "gato", "hipopotamo", "iguana", "jacare",
        "kiwi", "leao", "macaco", "navio", "ovelha", "pato", "quati", "rato", "sapo", "tigre",
        "urso", "vaca", "wolverine", "xaxim", "yak", "zebra"
    };
    
	for(int i=0;i<26;i++){
		infos[i].palavraPortugues = palavrasPT[i];
	}

    for (int i = 0; i < 26; i++) {
		insere(&raiz,infos[i]);
    }

	exibirPreordem(raiz);
    // exibirEmOrdem(raiz);

    printf("\n\n");

    for (int i = 0; i < 26; i++) {
        printf("Removendo %s\n", palavrasPT[i]);
		
		exibirPreordem(raiz);
		printf("\n\n");

        arvore23_remover(&raiz, palavrasPT[i]);
    }

    liberar23(raiz);
	return 0;
}