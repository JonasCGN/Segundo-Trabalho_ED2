#pragma once

#include "../../utils/utils.h"

Unidade* criaNo(Data info,Unidade *filhoEsq,Unidade *filhoCen);
Unidade* quebraNo(Unidade **no,Data valor,Data *promove,Unidade **filho);
void adicionaChave(Unidade *no,Data info,Unidade *filho);
int ehFolha(Unidade *no);
Unidade* inserirUnidade(Unidade **no, Data info, Data *promove, Unidade **Pai);

void exibirPreordem(Unidade *ptIn);
void exibirEmOrdem(Unidade *ptIn);

void liberaArvore23(Unidade *raiz);
