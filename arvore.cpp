#include "arvore.h"

/*
 * Insere recursivamente um produto na BST usando o codigo como chave.
 * Parametros: raiz (referencia para ponteiro, para poder criar o no) e produto.
 * Retorno: true se inseriu, false se o codigo ja existe.
 */
bool inserirNaArvore(NoArvore*& raiz, Produto* produto) {
    if (raiz == nullptr) {
        raiz = new NoArvore;
        raiz->produto = produto;
        raiz->esquerda = nullptr;
        raiz->direita = nullptr;
        return true;
    }
    if (produto->codigo == raiz->produto->codigo) return false;
    if (produto->codigo < raiz->produto->codigo) {
        return inserirNaArvore(raiz->esquerda, produto);
    }
    return inserirNaArvore(raiz->direita, produto);
}

/*
 * Busca recursiva por codigo. A cada nivel descarta uma subarvore inteira.
 * Parametros: raiz, codigo procurado e comparacoes (contador por referencia).
 * Retorno: ponteiro para o produto ou nullptr se nao encontrado.
 */
Produto* buscarNaArvore(const NoArvore* raiz, int codigo, long long& comparacoes) {
    if (raiz == nullptr) return nullptr;
    comparacoes++;
    if (codigo == raiz->produto->codigo) return raiz->produto;
    if (codigo < raiz->produto->codigo) {
        return buscarNaArvore(raiz->esquerda, codigo, comparacoes);
    }
    return buscarNaArvore(raiz->direita, codigo, comparacoes);
}

/*
 * Travessia in-ordem recursiva (esquerda, raiz, direita): imprime em ordem crescente de codigo.
 * Parametros: raiz. Retorno: nenhum.
 */
void percorrerEmOrdem(const NoArvore* raiz) {
    if (raiz == nullptr) return;
    percorrerEmOrdem(raiz->esquerda);
    imprimirProduto(raiz->produto);
    percorrerEmOrdem(raiz->direita);
}

/*
 * Conta os nos da arvore recursivamente.
 * Parametros: raiz. Retorno: quantidade de nos.
 */
int contarNos(const NoArvore* raiz) {
    if (raiz == nullptr) return 0;
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita);
}

/*
 * Calcula a altura da arvore recursivamente (arvore vazia = 0).
 * Parametros: raiz. Retorno: altura.
 */
int alturaArvore(const NoArvore* raiz) {
    if (raiz == nullptr) return 0;
    int alturaEsquerda = alturaArvore(raiz->esquerda);
    int alturaDireita = alturaArvore(raiz->direita);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
}

/*
 * Libera os nos da arvore em pos-ordem (filhos antes do pai).
 * Nao apaga os produtos: quem e dono deles e a lista do catalogo.
 * Parametros: raiz (referencia para ponteiro, recebe nullptr no final). Retorno: nenhum.
 */
void liberarArvore(NoArvore*& raiz) {
    if (raiz == nullptr) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    delete raiz;
    raiz = nullptr;
}
