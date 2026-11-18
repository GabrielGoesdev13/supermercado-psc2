#include "pilha.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * Deixa a pilha vazia.
 * Parametros: pilha (por referencia). Retorno: nenhum.
 */
void inicializarPilha(Pilha& pilha) {
    pilha.topo = nullptr;
    pilha.tamanho = 0;
}

/*
 * Verifica se a pilha esta vazia.
 * Parametros: pilha (referencia constante). Retorno: true se vazia.
 */
bool pilhaVazia(const Pilha& pilha) {
    return pilha.topo == nullptr;
}

/*
 * Coloca um item no topo do carrinho em O(1).
 * Parametros: pilha (por referencia) e item (referencia constante, e copiado para o no).
 * Retorno: nenhum.
 */
void empilhar(Pilha& pilha, const ItemCarrinho& item) {
    NoPilha* novo = new NoPilha;
    novo->item = item;
    novo->abaixo = pilha.topo;
    pilha.topo = novo;
    pilha.tamanho++;
}

/*
 * Retira o item do topo (o ultimo colocado) em O(1). E o "desfazer" do carrinho.
 * Parametros: pilha (por referencia) e removido (saida por referencia com o item retirado).
 * Retorno: true se retirou, false se a pilha estava vazia.
 */
bool desempilhar(Pilha& pilha, ItemCarrinho& removido) {
    if (pilhaVazia(pilha)) return false;
    NoPilha* antigoTopo = pilha.topo;
    removido = antigoTopo->item;
    pilha.topo = antigoTopo->abaixo;
    delete antigoTopo;
    antigoTopo = nullptr;
    pilha.tamanho--;
    return true;
}

/*
 * Soma o valor do carrinho de forma recursiva, descendo do topo ate a base.
 * Caso base: no nulo vale 0. Passo: subtotal do no + total do restante.
 * Parametros: no atual (comeca pelo topo). Retorno: valor total em reais.
 */
double totalCarrinhoRecursivo(const NoPilha* no) {
    if (no == nullptr) return 0.0;
    double subtotal = no->item.precoUnitario * no->item.quantidade;
    return subtotal + totalCarrinhoRecursivo(no->abaixo);
}

/*
 * Mostra os itens do carrinho do topo para a base e o total.
 * Parametros: pilha (referencia constante). Retorno: nenhum.
 */
void imprimirCarrinho(const Pilha& pilha) {
    if (pilhaVazia(pilha)) {
        cout << "Carrinho vazio.\n";
        return;
    }
    cout << "Carrinho (topo primeiro):\n";
    for (NoPilha* no = pilha.topo; no != nullptr; no = no->abaixo) {
        cout << "  " << no->item.quantidade << "x " << left << setw(24) << no->item.nome
             << right << " R$ " << fixed << setprecision(2)
             << no->item.precoUnitario * no->item.quantidade << "\n";
    }
    cout << "Total: R$ " << fixed << setprecision(2)
         << totalCarrinhoRecursivo(pilha.topo) << "\n";
}

/*
 * Libera todos os nos da pilha.
 * Parametros: pilha (por referencia). Retorno: nenhum. A pilha termina vazia.
 */
void liberarPilha(Pilha& pilha) {
    ItemCarrinho descartado;
    while (desempilhar(pilha, descartado)) {
    }
}
