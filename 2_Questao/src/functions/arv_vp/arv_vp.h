
#pragma once

#include "../../utils/utils.h"

int cor(ArvVP *no);

void rotacaoEsq(ArvVP **no);
void rotacaoDir(ArvVP **no);
void inverteCor(ArvVP **no);

void trocaCor(ArvVP **no);
ArvVP* criaNo(Info valor);
ArvVP* insereArvVP(ArvVP **raiz, ArvVP* no);
void exibirArvore(ArvVP *raiz);
void liberar(ArvVP *raiz);

void moveEsqVermelha(ArvVP **raiz);
void moveDirVermelha(ArvVP **raiz);
void removeMenor(ArvVP **raiz);
ArvVP *procuraMenor(ArvVP *raiz);
int removerNoArvVP(ArvVP **raiz, char *valor);