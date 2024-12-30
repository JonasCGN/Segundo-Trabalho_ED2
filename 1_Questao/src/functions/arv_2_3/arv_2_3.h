#pragma once

#include "../../utils/utils.h"

PalavraPortugues* criaNo(Data info,PalavraPortugues *filhoEsq,PalavraPortugues *filhoCen);
PalavraPortugues* quebraNo(PalavraPortugues **no,Data valor,Data *promove,PalavraPortugues **filho);
void adicionaChave(PalavraPortugues *no,Data info,PalavraPortugues *filho);
int ehFolha(PalavraPortugues *no);
PalavraPortugues* inserirPalavraPortugues(PalavraPortugues **no, Data info, Data *promove, PalavraPortugues **Pai);

void exibirPreordem(PalavraPortugues *ptIn);
void exibirEmOrdem(PalavraPortugues *ptIn);

void liberaArvore23(PalavraPortugues *raiz);
