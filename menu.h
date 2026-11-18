#ifndef MENU_H
#define MENU_H

#include "supermercado.h"

const int OPCAO_SAIR = 0;
const int ULTIMA_OPCAO = 12;

void exibirMenuPrincipal();
void executarOpcao(Supermercado& mercado, int opcao);

#endif
