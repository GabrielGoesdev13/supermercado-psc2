#include "supermercado.h"

/*
 * Inicializa todas as estruturas vazias.
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
void inicializarSupermercado(Supermercado& mercado) {
    inicializarLista(mercado.catalogo);
    mercado.indice = nullptr;
    inicializarFila(mercado.filaCaixa);
    mercado.faturamento = 0.0;
    mercado.clientesAtendidos = 0;
}

/*
 * Cadastra um produto: cria com new, insere no indice (arvore) e no catalogo (lista).
 * A arvore e consultada primeiro para impedir codigo duplicado.
 * Parametros: mercado (por referencia) e dados do produto.
 * Retorno: true se cadastrou, false se o codigo ja existia.
 */
bool cadastrarProduto(Supermercado& mercado, int codigo, const std::string& nome,
                      double preco, int estoque) {
    Produto* novo = criarProduto(codigo, nome, preco, estoque);
    if (!inserirNaArvore(mercado.indice, novo)) {
        delete novo;
        novo = nullptr;
        return false;
    }
    inserirNaLista(mercado.catalogo, novo);
    return true;
}

/*
 * Reconstroi a arvore a partir da lista (usado apos uma remocao,
 * para que o indice nunca aponte para um produto ja liberado).
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
static void reconstruirIndice(Supermercado& mercado) {
    liberarArvore(mercado.indice);
    for (NoLista* atual = mercado.catalogo.inicio; atual != nullptr; atual = atual->proximo) {
        inserirNaArvore(mercado.indice, atual->produto);
    }
}

/*
 * Remove um produto do catalogo e atualiza o indice.
 * Parametros: mercado (por referencia) e codigo. Retorno: true se removeu.
 */
bool removerProduto(Supermercado& mercado, int codigo) {
    if (!removerDaLista(mercado.catalogo, codigo)) return false;
    reconstruirIndice(mercado);
    return true;
}

/*
 * Busca um produto pelo codigo usando a arvore (O(log n) em media).
 * Parametros: mercado (referencia constante) e codigo. Retorno: ponteiro ou nullptr.
 */
Produto* buscarProduto(const Supermercado& mercado, int codigo) {
    long long comparacoes = 0;
    return buscarNaArvore(mercado.indice, codigo, comparacoes);
}

/*
 * Carrega um catalogo inicial para a demonstracao. Os codigos estao fora de ordem
 * de proposito, para a arvore ficar balanceada e a ordenacao ter trabalho a fazer.
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
void carregarProdutosIniciais(Supermercado& mercado) {
    cadastrarProduto(mercado, 150, "Arroz 5kg", 27.90, 30);
    cadastrarProduto(mercado, 75, "Feijao Carioca 1kg", 8.49, 40);
    cadastrarProduto(mercado, 230, "Cafe 500g", 18.75, 25);
    cadastrarProduto(mercado, 40, "Leite Integral 1L", 5.29, 60);
    cadastrarProduto(mercado, 110, "Macarrao 500g", 4.99, 50);
    cadastrarProduto(mercado, 190, "Oleo de Soja 900ml", 7.89, 35);
    cadastrarProduto(mercado, 300, "Sabao em Po 1kg", 15.40, 20);
    cadastrarProduto(mercado, 20, "Acucar 1kg", 4.59, 45);
    cadastrarProduto(mercado, 90, "Pao de Forma", 9.90, 15);
    cadastrarProduto(mercado, 130, "Manteiga 200g", 12.30, 18);
    cadastrarProduto(mercado, 210, "Refrigerante 2L", 9.49, 40);
    cadastrarProduto(mercado, 260, "Detergente 500ml", 2.79, 70);
}

/*
 * Libera toda a memoria do sistema. Ordem: fila (clientes e carrinhos),
 * arvore (so os nos) e por ultimo a lista (nos e produtos).
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
void encerrarSupermercado(Supermercado& mercado) {
    liberarFila(mercado.filaCaixa);
    liberarArvore(mercado.indice);
    liberarLista(mercado.catalogo);
}
