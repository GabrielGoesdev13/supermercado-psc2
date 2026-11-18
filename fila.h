#ifndef FILA_H
#define FILA_H

#include <string>
#include "pilha.h"

/* Cliente que entra na fila do caixa levando seu carrinho. */
struct Cliente {
    std::string nome;
    Pilha carrinho;
};

/* No da fila encadeada. */
struct NoFila {
    Cliente* cliente;
    NoFila* proximo;
};

/* Fila do caixa (FIFO): entra no fim, sai do inicio. */
struct Fila {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
};

Cliente* criarCliente(const std::string& nome);
void liberarCliente(Cliente*& cliente);
void inicializarFila(Fila& fila);
bool filaVazia(const Fila& fila);
void enfileirar(Fila& fila, Cliente* cliente);
Cliente* desenfileirar(Fila& fila);
void imprimirFila(const Fila& fila);
void liberarFila(Fila& fila);

#endif
