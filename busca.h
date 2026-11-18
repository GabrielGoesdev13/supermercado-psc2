#ifndef BUSCA_H
#define BUSCA_H

#include <string>
#include "lista.h"

Produto* buscaSequencial(const ListaProdutos& lista, int codigo, long long& comparacoes);
int buscaBinaria(Produto** vetor, int tamanho, int codigo, long long& comparacoes);
int buscarPorNome(const ListaProdutos& lista, const std::string& trecho);
void compararDesempenhoBuscas(int quantidade = 20000);

#endif
