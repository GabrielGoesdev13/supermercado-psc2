#include "lista.h"
#include <iostream>

using namespace std;

/*
 * Deixa a lista vazia e pronta para uso.
 * Parametros: lista (por referencia, pois sera alterada). Retorno: nenhum.
 */
void inicializarLista(ListaProdutos& lista) {
    lista.inicio = nullptr;
    lista.fim = nullptr;
    lista.tamanho = 0;
}

/*
 * Insere um produto no final da lista em O(1), usando o ponteiro fim.
 * Parametros: lista (por referencia) e produto (ponteiro ja alocado com new).
 * Retorno: nenhum. A lista passa a ser dona do produto.
 */
void inserirNaLista(ListaProdutos& lista, Produto* produto) {
    NoLista* novo = new NoLista;
    novo->produto = produto;
    novo->proximo = nullptr;
    if (lista.inicio == nullptr) {
        lista.inicio = novo;
    } else {
        lista.fim->proximo = novo;
    }
    lista.fim = novo;
    lista.tamanho++;
}

/*
 * Remove da lista o produto com o codigo informado e libera a memoria (delete).
 * Parametros: lista (por referencia) e codigo do produto.
 * Retorno: true se removeu, false se o codigo nao existe.
 */
bool removerDaLista(ListaProdutos& lista, int codigo) {
    NoLista* anterior = nullptr;
    NoLista* atual = lista.inicio;
    while (atual != nullptr && atual->produto->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == nullptr) return false;

    /* religa os ponteiros pulando o no removido */
    if (anterior == nullptr) lista.inicio = atual->proximo;
    else anterior->proximo = atual->proximo;
    if (atual == lista.fim) lista.fim = anterior;

    delete atual->produto;
    atual->produto = nullptr;
    delete atual;
    atual = nullptr;
    lista.tamanho--;
    return true;
}

/*
 * Percorre a lista do inicio ao fim imprimindo cada produto (travessia).
 * Parametros: lista (referencia constante, so leitura). Retorno: nenhum.
 */
void imprimirLista(const ListaProdutos& lista) {
    if (lista.inicio == nullptr) {
        cout << "Catalogo vazio.\n";
        return;
    }
    imprimirCabecalhoProdutos();
    for (NoLista* atual = lista.inicio; atual != nullptr; atual = atual->proximo) {
        imprimirProduto(atual->produto);
    }
}

/*
 * Copia os ponteiros dos produtos para um vetor dinamico (usado na ordenacao e busca binaria).
 * Parametros: lista (referencia constante).
 * Retorno: vetor alocado com new[] (quem chama deve dar delete[]) ou nullptr se vazia.
 */
Produto** listaParaVetor(const ListaProdutos& lista) {
    if (lista.tamanho == 0) return nullptr;
    Produto** vetor = new Produto*[lista.tamanho];
    int i = 0;
    for (NoLista* atual = lista.inicio; atual != nullptr; atual = atual->proximo) {
        vetor[i++] = atual->produto;
    }
    return vetor;
}

/*
 * Libera todos os nos e todos os produtos da lista.
 * Parametros: lista (por referencia). Retorno: nenhum. A lista termina vazia.
 */
void liberarLista(ListaProdutos& lista) {
    NoLista* atual = lista.inicio;
    while (atual != nullptr) {
        NoLista* proximo = atual->proximo;
        delete atual->produto;
        atual->produto = nullptr;
        delete atual;
        atual = proximo;
    }
    inicializarLista(lista);
}
