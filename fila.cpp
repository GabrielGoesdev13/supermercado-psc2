#include "fila.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * Aloca um cliente com o carrinho vazio.
 * Parametros: nome (referencia constante). Retorno: ponteiro para o cliente criado.
 */
Cliente* criarCliente(const string& nome) {
    Cliente* cliente = new Cliente;
    cliente->nome = nome;
    inicializarPilha(cliente->carrinho);
    return cliente;
}

/*
 * Libera o carrinho e o cliente, e zera o ponteiro de quem chamou.
 * Parametros: cliente (referencia para ponteiro, para poder receber nullptr). Retorno: nenhum.
 */
void liberarCliente(Cliente*& cliente) {
    if (cliente == nullptr) return;
    liberarPilha(cliente->carrinho);
    delete cliente;
    cliente = nullptr;
}

/*
 * Deixa a fila vazia.
 * Parametros: fila (por referencia). Retorno: nenhum.
 */
void inicializarFila(Fila& fila) {
    fila.inicio = nullptr;
    fila.fim = nullptr;
    fila.tamanho = 0;
}

/*
 * Verifica se a fila esta vazia.
 * Parametros: fila (referencia constante). Retorno: true se vazia.
 */
bool filaVazia(const Fila& fila) {
    return fila.inicio == nullptr;
}

/*
 * Coloca o cliente no fim da fila em O(1).
 * Parametros: fila (por referencia) e cliente (ponteiro). Retorno: nenhum.
 */
void enfileirar(Fila& fila, Cliente* cliente) {
    NoFila* novo = new NoFila;
    novo->cliente = cliente;
    novo->proximo = nullptr;
    if (filaVazia(fila)) fila.inicio = novo;
    else fila.fim->proximo = novo;
    fila.fim = novo;
    fila.tamanho++;
}

/*
 * Retira o primeiro cliente da fila em O(1).
 * Parametros: fila (por referencia).
 * Retorno: ponteiro para o cliente (quem chama deve libera-lo) ou nullptr se vazia.
 */
Cliente* desenfileirar(Fila& fila) {
    if (filaVazia(fila)) return nullptr;
    NoFila* removido = fila.inicio;
    Cliente* cliente = removido->cliente;
    fila.inicio = removido->proximo;
    if (fila.inicio == nullptr) fila.fim = nullptr;
    delete removido;
    removido = nullptr;
    fila.tamanho--;
    return cliente;
}

/*
 * Mostra os clientes na ordem em que serao atendidos.
 * Parametros: fila (referencia constante). Retorno: nenhum.
 */
void imprimirFila(const Fila& fila) {
    if (filaVazia(fila)) {
        cout << "Nenhum cliente na fila do caixa.\n";
        return;
    }
    int posicao = 1;
    for (NoFila* no = fila.inicio; no != nullptr; no = no->proximo) {
        cout << posicao++ << ". " << left << setw(20) << no->cliente->nome
             << right << no->cliente->carrinho.tamanho << " item(ns)  R$ "
             << fixed << setprecision(2)
             << totalCarrinhoRecursivo(no->cliente->carrinho.topo) << "\n";
    }
}

/*
 * Libera todos os nos da fila e os clientes que ainda estavam nela.
 * Parametros: fila (por referencia). Retorno: nenhum.
 */
void liberarFila(Fila& fila) {
    while (!filaVazia(fila)) {
        Cliente* cliente = desenfileirar(fila);
        liberarCliente(cliente);
    }
}
