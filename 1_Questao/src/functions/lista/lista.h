#pragma once

#include "../../utils/utils.h"

void inserirUnidadeLista(ListaUnidade **lista, int unidade);
int removerUnidadeLista(ListaUnidade **lista, int unidade);

ListaUnidade * buscarUnidadeLista(ListaUnidade *lista, int unidade);

void exibirLista(ListaUnidade *lista);
void liberarLista(ListaUnidade *lista);