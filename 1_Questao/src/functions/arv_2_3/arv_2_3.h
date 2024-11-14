#pragma once

#include "../../utils/utils.h"

PortugesIngles* criaNo(Info info,PortugesIngles *filhoEsq,PortugesIngles *filhoCen);
PortugesIngles* quebraNo(PortugesIngles **no,Info valor,Info *promove,PortugesIngles **filho);
PortugesIngles* adicionaChave(PortugesIngles *no,Info info,PortugesIngles *filho);
int ehFolha(PortugesIngles *no);
PortugesIngles* inserirPalavraPortugues(PortugesIngles **no, Info info, Info *promove, PortugesIngles **Pai);