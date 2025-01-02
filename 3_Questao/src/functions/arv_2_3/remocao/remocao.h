#pragma once

#include "../../../utils/utils.h"

Unidade *no23_alocar();

void no23_desalocar(Unidade **no);

Unidade *no23_criar(Data info, Unidade *filho_esquerdo, Unidade *filho_centro);

Data no23_maior_info(Unidade *raiz);


Unidade *arvore23_criar();

Unidade *arvore23_buscar(Unidade *raiz, int info);

Unidade *arvore23_buscar_menor_filho(Unidade *raiz, Unidade **pai);

Unidade *arvore23_buscar_maior_filho(Unidade *raiz, Unidade **pai, Data *maior_valor);

Unidade *arvore23_buscar_pai(Unidade *raiz, int info);

Unidade *arvore23_buscar_maior_pai(Unidade *raiz, int info);

Unidade *arvore23_buscar_menor_pai(Unidade *raiz, int info);

void arvore23_desalocar(Unidade **raiz);

Unidade *arvore23_inserir(Unidade **raiz, Data info, Unidade *pai, Data *promove);

int arvore23_remover1(Unidade **raiz, int info, Unidade *pai, Unidade **origem, Unidade **maior);

int arvore23_remover2(Unidade **raiz, int info, Unidade *pai, Unidade **origem, Unidade **maior);

int arvore23_remover(Unidade **raiz, int info);

int arvore23_rebalancear(Unidade **raiz, int info, Unidade **maior);

void arvore23_exibir_pre(Unidade *raiz);

void arvore23_exibir_ordem(Unidade *raiz);

void arvore23_exibir_pos(Unidade *raiz);