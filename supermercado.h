#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H

#include "lista.h"
#include "arvore.h"
#include "fila.h"

/* Estado geral do sistema: catalogo (lista), indice (arvore) e fila do caixa. */
struct Supermercado {
    ListaProdutos catalogo;
    NoArvore* indice;
    Fila filaCaixa;
    double faturamento;
    int clientesAtendidos;
};

void inicializarSupermercado(Supermercado& mercado);
bool cadastrarProduto(Supermercado& mercado, int codigo, const std::string& nome,
                      double preco, int estoque);
bool removerProduto(Supermercado& mercado, int codigo);
Produto* buscarProduto(const Supermercado& mercado, int codigo);
void carregarProdutosIniciais(Supermercado& mercado);
void encerrarSupermercado(Supermercado& mercado);

#endif
