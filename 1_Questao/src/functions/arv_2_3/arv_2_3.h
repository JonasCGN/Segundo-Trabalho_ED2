#pragma once

#include "../../utils/utils.h"

PalavraPortugues* criaNo(Data info,PalavraPortugues *filhoEsq,PalavraPortugues *filhoCen);
PalavraPortugues* quebraNo(PalavraPortugues **no,Data valor,Data *promove,PalavraPortugues **filho);
void adicionaChave(PalavraPortugues *no,Data info,PalavraPortugues *filho);

PalavraPortugues* inserirPalavraPortugues(PalavraPortugues **no, Data info, Data *promove, PalavraPortugues **pai,PalavraPortugues **noInserido);

void exibeInfo(Data info);

void exibirPreordem(PalavraPortugues *ptIn);
void exibirEmOrdem(PalavraPortugues *ptIn);


void exibirEmOrdemUnidade(PalavraPortugues *ptIn,int unidade);
void exibePalavraPortuguesIngles(PalavraPortugues *ptBR,char *palavra);

void liberaArvore23(PalavraPortugues *raiz);
