#pragma once

#include "../../utils/utils.h"

int inserirPalavraIngles(PalavraIngles **ingles, InfoArvBB info,int unidade);
int removerPalavraIngles(PalavraIngles**raiz, PalavraIngles *palavra);

int removePalavraInglesUnidade(PalavraIngles**raiz, int unidade);

void exibirENOrdem(PalavraIngles* raiz);
int verificaInglesUnidade(PalavraIngles* raiz,int unidade);
void exibeInglesUnidade(PalavraIngles* raiz,int unidade);

// void removeArvoreBB(PalavraIngles *raiz, int unidade);
void liberaArvoreBB(PalavraIngles *raiz);