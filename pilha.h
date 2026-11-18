#ifndef PILHA_H
#define PILHA_H

#include <string>

/* Item do carrinho: guarda uma copia dos dados do produto no momento da compra. */
struct ItemCarrinho {
    int codigo;
    std::string nome;
    double precoUnitario;
    int quantidade;
};

/* No da pilha encadeada. */
struct NoPilha {
    ItemCarrinho item;
    NoPilha* abaixo;
};

/* Carrinho de compras implementado como pilha (LIFO). */
struct Pilha {
    NoPilha* topo;
    int tamanho;
};

void inicializarPilha(Pilha& pilha);
bool pilhaVazia(const Pilha& pilha);
void empilhar(Pilha& pilha, const ItemCarrinho& item);
bool desempilhar(Pilha& pilha, ItemCarrinho& removido);
double totalCarrinhoRecursivo(const NoPilha* no);
void imprimirCarrinho(const Pilha& pilha);
void liberarPilha(Pilha& pilha);

#endif
