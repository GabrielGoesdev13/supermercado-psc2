#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

/* Representa um produto do catalogo do supermercado. */
struct Produto {
    int codigo;
    std::string nome;
    double preco;
    int estoque;
};

/* Ponteiro para funcao que compara dois produtos (usado na ordenacao). */
typedef bool (*Comparador)(const Produto*, const Produto*);

Produto* criarProduto(int codigo, const std::string& nome, double preco, int estoque);
void imprimirCabecalhoProdutos();
void imprimirProduto(const Produto* produto, bool mostrarEstoque = true);
bool menorPorPreco(const Produto* a, const Produto* b);
bool menorPorCodigo(const Produto* a, const Produto* b);

#endif
