#include "busca.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

/*
 * Busca sequencial por codigo percorrendo a lista do inicio ao fim.
 * Complexidade: O(n). Nao exige dados ordenados.
 * Parametros: lista, codigo e comparacoes (contador por referencia).
 * Retorno: ponteiro para o produto ou nullptr.
 */
Produto* buscaSequencial(const ListaProdutos& lista, int codigo, long long& comparacoes) {
    comparacoes = 0;
    for (NoLista* atual = lista.inicio; atual != nullptr; atual = atual->proximo) {
        comparacoes++;
        if (atual->produto->codigo == codigo) return atual->produto;
    }
    return nullptr;
}

/*
 * Busca binaria iterativa por codigo. Complexidade: O(log n).
 * Pre-condicao: o vetor precisa estar ordenado por codigo.
 * Parametros: vetor de ponteiros, tamanho, codigo e comparacoes (por referencia).
 * Retorno: indice do produto no vetor ou -1 se nao existe.
 */
int buscaBinaria(Produto** vetor, int tamanho, int codigo, long long& comparacoes) {
    comparacoes = 0;
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;   /* evita overflow de (inicio + fim) */
        comparacoes++;
        if (vetor[meio]->codigo == codigo) return meio;
        if (vetor[meio]->codigo < codigo) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/*
 * Converte um texto para minusculas.
 * Parametros: texto (por VALOR, pois a copia e alterada sem mexer no original).
 * Retorno: o texto em minusculas.
 */
static string paraMinusculas(string texto) {
    for (char& c : texto) {
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
    }
    return texto;
}

/*
 * Busca sequencial por parte do nome (sem diferenciar maiusculas). O(n).
 * Nome nao e a chave da arvore, por isso aqui so a busca sequencial serve.
 * Parametros: lista e trecho procurado. Retorno: quantidade de produtos encontrados.
 */
int buscarPorNome(const ListaProdutos& lista, const string& trecho) {
    string alvo = paraMinusculas(trecho);
    int encontrados = 0;
    for (NoLista* atual = lista.inicio; atual != nullptr; atual = atual->proximo) {
        if (paraMinusculas(atual->produto->nome).find(alvo) != string::npos) {
            if (encontrados == 0) imprimirCabecalhoProdutos();
            imprimirProduto(atual->produto);
            encontrados++;
        }
    }
    return encontrados;
}

/*
 * Mede uma busca sequencial e uma binaria para o mesmo alvo e imprime a linha da tabela.
 * Cada busca e repetida REPETICOES vezes e o tempo mostrado e a media (mais estavel).
 * Parametros: lista, vetor ordenado, tamanho, codigo alvo e descricao do caso.
 * Retorno: nenhum.
 */
static void medirBusca(const ListaProdutos& lista, Produto** vetor, int tamanho,
                       int alvo, const string& descricao) {
    const int REPETICOES = 200;
    long long compSequencial = 0, compBinaria = 0;
    volatile bool resultado = false;   /* impede o compilador de descartar as buscas */
    auto t0 = chrono::steady_clock::now();
    for (int r = 0; r < REPETICOES; r++)
        resultado = buscaSequencial(lista, alvo, compSequencial) != nullptr;
    auto t1 = chrono::steady_clock::now();
    for (int r = 0; r < REPETICOES; r++)
        resultado = buscaBinaria(vetor, tamanho, alvo, compBinaria) != -1;
    auto t2 = chrono::steady_clock::now();
    long long nsSeq = chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count() / REPETICOES;
    long long nsBin = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() / REPETICOES;
    cout << left << setw(13) << descricao << right << setw(8) << alvo
         << setw(12) << compSequencial << setw(12) << nsSeq
         << setw(12) << compBinaria << setw(12) << nsBin
         << (resultado ? "   sim" : "   nao") << "\n";
}

/*
 * Gera um catalogo temporario grande e compara busca sequencial x binaria
 * em quatro casos: primeiro, meio, ultimo e inexistente.
 * Parametros: quantidade de produtos (parametro default = 20000). Retorno: nenhum.
 */
void compararDesempenhoBuscas(int quantidade) {
    ListaProdutos teste;
    inicializarLista(teste);
    for (int i = 1; i <= quantidade; i++) {
        inserirNaLista(teste, criarProduto(i * 2, "Produto teste", 1.0, 1));
    }
    Produto** vetor = listaParaVetor(teste);   /* codigos gerados ja em ordem crescente */

    cout << "\nComparativo com " << quantidade << " produtos\n";
    cout << left << setw(13) << "Caso" << right << setw(8) << "Codigo"
         << setw(12) << "Seq. comp" << setw(12) << "Seq. ns"
         << setw(12) << "Bin. comp" << setw(12) << "Bin. ns" << "  Achou\n";
    cout << string(75, '-') << "\n";
    medirBusca(teste, vetor, quantidade, 2, "Primeiro");
    medirBusca(teste, vetor, quantidade, quantidade, "Meio");
    medirBusca(teste, vetor, quantidade, quantidade * 2, "Ultimo");
    medirBusca(teste, vetor, quantidade, quantidade * 2 + 1, "Inexistente");

    delete[] vetor;
    vetor = nullptr;
    liberarLista(teste);
}
