#pragma once

#include "../../utils/utils.h"

int cor(PalavraPortugues *no);

void rotacaoEsq(PalavraPortugues **no);
void rotacaoDir(PalavraPortugues **no);
void inverteCor(PalavraPortugues **no);

void trocaCor(PalavraPortugues **no);
PalavraPortugues* criaNo(Data valor);
PalavraPortugues* inserePalavraPortugues(PalavraPortugues **raiz, PalavraPortugues* no);
void inserePortuguesIngles(PalavraPortugues **raiz, Data info);

void exibirArvore(PalavraPortugues *raiz);
void liberarPalavraPortugues(PalavraPortugues *raiz);

void moveEsqVermelha(PalavraPortugues **raiz);
void moveDirVermelha(PalavraPortugues **raiz);
void removeMenor(PalavraPortugues **raiz);
PalavraPortugues *procuraMenor(PalavraPortugues *raiz);
int removerNoPalavraPortugues(PalavraPortugues **raiz, char *valor);
void removePortuguesIngles(PalavraPortugues **raiz, char *valor);