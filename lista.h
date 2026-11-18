#ifndef LISTA_H
#define LISTA_H

#include "produto.h"

/* No da lista encadeada simples do catalogo. */
struct NoLista {
    Produto* produto;
    NoLista* proximo;
};

/* Catalogo de produtos: lista encadeada com ponteiro para inicio e fim. */
struct ListaProdutos {
    NoLista* inicio;
    NoLista* fim;
    int tamanho;
};

void inicializarLista(ListaProdutos& lista);
void inserirNaLista(ListaProdutos& lista, Produto* produto);
bool removerDaLista(ListaProdutos& lista, int codigo);
void imprimirLista(const ListaProdutos& lista);
Produto** listaParaVetor(const ListaProdutos& lista);
void liberarLista(ListaProdutos& lista);

#endif
