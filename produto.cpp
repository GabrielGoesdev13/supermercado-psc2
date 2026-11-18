#include "produto.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * Aloca dinamicamente um novo produto (new).
 * Parametros: codigo, nome (por referencia constante para evitar copia), preco e estoque.
 * Retorno: ponteiro para o produto criado. Quem libera e a lista do catalogo.
 */
Produto* criarProduto(int codigo, const string& nome, double preco, int estoque) {
    Produto* produto = new Produto;
    produto->codigo = codigo;
    produto->nome = nome;
    produto->preco = preco;
    produto->estoque = estoque;
    return produto;
}

/*
 * Imprime o cabecalho da tabela de produtos.
 * Parametros: nenhum. Retorno: nenhum.
 */
void imprimirCabecalhoProdutos() {
    cout << left << setw(8) << "Codigo" << setw(26) << "Produto"
         << right << setw(11) << "Preco" << setw(9) << "Estoque" << "\n";
    cout << string(54, '-') << "\n";
}

/*
 * Imprime uma linha com os dados de um produto.
 * Parametros: produto (ponteiro constante) e mostrarEstoque (parametro default = true).
 * Retorno: nenhum.
 */
void imprimirProduto(const Produto* produto, bool mostrarEstoque) {
    if (produto == nullptr) return;
    cout << left << setw(8) << produto->codigo << setw(26) << produto->nome
         << right << "R$ " << setw(8) << fixed << setprecision(2) << produto->preco;
    if (mostrarEstoque) cout << setw(9) << produto->estoque;
    cout << "\n";
}

/*
 * Comparador usado pelo Merge Sort para ordenar por preco.
 * Parametros: dois produtos. Retorno: true se a vem antes de b.
 */
bool menorPorPreco(const Produto* a, const Produto* b) {
    return a->preco < b->preco;
}

/*
 * Comparador usado pelo Merge Sort para ordenar por codigo (necessario para a busca binaria).
 * Parametros: dois produtos. Retorno: true se a vem antes de b.
 */
bool menorPorCodigo(const Produto* a, const Produto* b) {
    return a->codigo < b->codigo;
}
