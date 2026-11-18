#include "ordenacao.h"

/*
 * MERGE SORT - analise de complexidade
 *   Tempo:  O(n log n) no melhor, medio e pior caso. O vetor e dividido ao meio
 *           log2(n) vezes e, em cada nivel, a intercalacao percorre os n elementos.
 *   Espaco: O(n) extra para o vetor auxiliar da intercalacao + O(log n) da pilha de recursao.
 *   Estavel: sim (em caso de empate mantem a ordem original).
 *   Escolhido porque o desempenho nao piora com a entrada (diferente do Bubble/Insertion,
 *   que chegam a O(n^2)), e porque recebe um comparador, servindo para preco e para codigo.
 */

/*
 * Intercala duas metades ja ordenadas: vetor[inicio..meio] e vetor[meio+1..fim].
 * Parametros: vetor de ponteiros, limites, comparador e contador de comparacoes.
 * Retorno: nenhum.
 */
static void intercalar(Produto** vetor, int inicio, int meio, int fim,
                       Comparador menor, long long& comparacoes) {
    int tamanho = fim - inicio + 1;
    Produto** auxiliar = new Produto*[tamanho];
    int i = inicio, j = meio + 1, k = 0;
    while (i <= meio && j <= fim) {
        comparacoes++;
        /* so pega da direita se for estritamente menor: garante estabilidade */
        if (menor(vetor[j], vetor[i])) auxiliar[k++] = vetor[j++];
        else auxiliar[k++] = vetor[i++];
    }
    while (i <= meio) auxiliar[k++] = vetor[i++];
    while (j <= fim) auxiliar[k++] = vetor[j++];
    for (k = 0; k < tamanho; k++) vetor[inicio + k] = auxiliar[k];
    delete[] auxiliar;
    auxiliar = nullptr;
}

/*
 * Ordena recursivamente o vetor de ponteiros de produtos.
 * Parametros: vetor, indice inicial e final, comparador (ponteiro para funcao)
 *             e comparacoes (contador por referencia).
 * Retorno: nenhum (ordena no proprio vetor).
 */
void mergeSort(Produto** vetor, int inicio, int fim, Comparador menor, long long& comparacoes) {
    if (inicio >= fim) return;
    int meio = inicio + (fim - inicio) / 2;
    mergeSort(vetor, inicio, meio, menor, comparacoes);
    mergeSort(vetor, meio + 1, fim, menor, comparacoes);
    intercalar(vetor, inicio, meio, fim, menor, comparacoes);
}
