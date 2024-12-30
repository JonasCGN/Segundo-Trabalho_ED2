#pragma once

#include "../../../utils/utils.h"

PalavraPortugues*no23_alocar();

PalavraPortugues *no23_juntar(PalavraPortugues *filho1, Data info, PalavraPortugues *maior, PalavraPortugues **raiz);

PalavraPortugues*arvore23_criar();

void arvore23_desalocar(PalavraPortugues**raiz);

int arvore23_remover1(PalavraPortugues**raiz, char* info, PalavraPortugues*pai, PalavraPortugues**origem, PalavraPortugues**maior);
int arvore23_remover2(PalavraPortugues**raiz, char* info, PalavraPortugues*pai, PalavraPortugues**origem, PalavraPortugues**maior);
int arvore23_remover(PalavraPortugues**raiz, char* info);

int arvore23_rebalancear(PalavraPortugues**raiz, char* info, PalavraPortugues**maior);