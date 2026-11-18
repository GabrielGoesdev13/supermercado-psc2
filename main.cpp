#include "menu.h"
#include "entrada.h"
#include <iostream>

using namespace std;

/*
 * Ponto de entrada: monta o supermercado, roda o menu e libera tudo ao sair.
 * Retorno: 0 (sucesso).
 */
int main() {
    Supermercado mercado;
    inicializarSupermercado(mercado);
    carregarProdutosIniciais(mercado);

    int opcao;
    do {
        exibirMenuPrincipal();
        opcao = lerInteiro("Escolha uma opcao: ", OPCAO_SAIR, ULTIMA_OPCAO);
        executarOpcao(mercado, opcao);
    } while (opcao != OPCAO_SAIR);

    encerrarSupermercado(mercado);
    cout << "Memoria liberada. Ate logo!\n";
    return 0;
}
