#pragma once

#include "../../utils/utils.h"

int inserirPalavraIngles(InglesPortugues **ingles, InfoArvBB info);
int removerPalavraIngles(InglesPortugues **raiz, char *palavra, int unidade);

void removeArvoreBB(InglesPortugues *raiz, int unidade);
void liberaArvoreBB(InglesPortugues *raiz);