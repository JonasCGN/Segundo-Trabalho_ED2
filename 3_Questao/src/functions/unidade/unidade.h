#pragma once

#include "../../utils/utils.h"

void noOcupar(Unidade **unidade);
void noLivre(Unidade **unidade);
void modificaNo(Unidade **unidade,int tamanho,int status);
char *statusInfo(int status);