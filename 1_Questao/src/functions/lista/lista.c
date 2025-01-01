#include "lista.h"

void inserirUnidadeLista(ListaUnidade **lista, int unidade){
	ListaUnidade *novo = (ListaUnidade *)malloc(sizeof(ListaUnidade));	

	novo->unidade = unidade;
	novo->prox = NULL;

	if(!(*lista)){
		*lista = novo;	
	}else{
		ListaUnidade *aux = *lista;
		
		*lista = novo;
		novo->prox = aux;
	}

}

int removerUnidadeLista(ListaUnidade **lista, int unidade){
	int verifica = 0;
	ListaUnidade *aux = *lista;

	if(*lista){
		ListaUnidade *remove;
		remove = NULL;

		if((*lista)->unidade == unidade){
			remove = (*lista);
			(*lista) = aux->prox;
		}else{
			while(aux->prox && aux->prox->unidade != unidade){
				aux = aux->prox;
			}

			if(aux->prox){
				remove = aux->prox;
				aux->prox = aux->prox->prox;
			}
		}

		if(remove){
			free(remove);
			remove = NULL;

			verifica = 1;
		}
	}

	return verifica;
}

ListaUnidade * buscarUnidadeLista(ListaUnidade *lista, int unidade){
	ListaUnidade *aux;
	aux = NULL;

	if(lista){
		if(lista->unidade == unidade){
			aux = lista;
		}else{
			aux = buscarUnidadeLista(lista->prox,unidade);
		}
	}
	
	return aux;
}

void exibirLista(ListaUnidade *lista){
	if(lista){
		printf("%d -> ", lista->unidade);
		exibirLista(lista->prox);
	}
}

void liberarLista(ListaUnidade *lista){
	if(lista){
		liberarLista(lista->prox);
		free(lista);
		lista = NULL;
	}
}