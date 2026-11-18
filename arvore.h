#ifndef ARVORE_H
#define ARVORE_H

#include "produto.h"

/* No da arvore binaria de busca, indexada pelo codigo do produto. */
struct NoArvore {
    Produto* produto;
    NoArvore* esquerda;
    NoArvore* direita;
};

bool inserirNaArvore(NoArvore*& raiz, Produto* produto);
Produto* buscarNaArvore(const NoArvore* raiz, int codigo, long long& comparacoes);
void percorrerEmOrdem(const NoArvore* raiz);
int contarNos(const NoArvore* raiz);
int alturaArvore(const NoArvore* raiz);
void liberarArvore(NoArvore*& raiz);

#endif
