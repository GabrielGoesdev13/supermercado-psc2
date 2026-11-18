#include "menu.h"
#include "busca.h"
#include "ordenacao.h"
#include "entrada.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * Mostra as opcoes do menu principal.
 * Parametros: nenhum. Retorno: nenhum.
 */
void exibirMenuPrincipal() {
    cout << "\n========== SUPERMERCADO CAMPO REAL ==========\n"
         << " 1. Listar catalogo (lista encadeada)\n"
         << " 2. Listar por codigo (arvore - in-ordem)\n"
         << " 3. Ordenar por preco (Merge Sort)\n"
         << " 4. Cadastrar produto\n"
         << " 5. Remover produto\n"
         << " 6. Buscar por codigo (sequencial x binaria x arvore)\n"
         << " 7. Buscar por nome\n"
         << " 8. Novo cliente (montar carrinho)\n"
         << " 9. Ver fila do caixa\n"
         << "10. Atender proximo cliente\n"
         << "11. Comparativo de desempenho das buscas\n"
         << "12. Estatisticas\n"
         << " 0. Sair\n";
}

/*
 * Opcao 3: copia o catalogo para um vetor, ordena por preco com Merge Sort e mostra.
 * Parametros: mercado (referencia constante: o catalogo original nao e alterado).
 * Retorno: nenhum.
 */
static void opcaoOrdenarPorPreco(const Supermercado& mercado) {
    int tamanho = mercado.catalogo.tamanho;
    Produto** vetor = listaParaVetor(mercado.catalogo);
    if (vetor == nullptr) {
        cout << "Catalogo vazio.\n";
        return;
    }
    long long comparacoes = 0;
    mergeSort(vetor, 0, tamanho - 1, menorPorPreco, comparacoes);
    imprimirCabecalhoProdutos();
    for (int i = 0; i < tamanho; i++) imprimirProduto(vetor[i]);
    cout << "Merge Sort: " << comparacoes << " comparacoes para " << tamanho << " produtos.\n";
    delete[] vetor;
    vetor = nullptr;
}

/*
 * Opcao 4: le os dados e cadastra um novo produto.
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
static void opcaoCadastrar(Supermercado& mercado) {
    int codigo = lerInteiro("Codigo: ", 1, 999999);
    if (buscarProduto(mercado, codigo) != nullptr) {
        cout << "Ja existe um produto com esse codigo.\n";
        return;
    }
    string nome = lerTexto("Nome: ");
    double preco = lerDecimal("Preco: R$ ", 0.01, 100000.0);
    int estoque = lerInteiro("Estoque: ", 0, 100000);
    cadastrarProduto(mercado, codigo, nome, preco, estoque);
    cout << "Produto cadastrado.\n";
}

/*
 * Opcao 5: remove um produto pelo codigo.
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
static void opcaoRemover(Supermercado& mercado) {
    int codigo = lerInteiro("Codigo do produto a remover: ", 1, 999999);
    if (removerProduto(mercado, codigo)) cout << "Produto removido.\n";
    else cout << "Produto nao encontrado.\n";
}

/*
 * Opcao 6: busca o mesmo codigo de tres formas e compara o numero de comparacoes.
 * Parametros: mercado (referencia constante). Retorno: nenhum.
 */
static void opcaoBuscarPorCodigo(const Supermercado& mercado) {
    int codigo = lerInteiro("Codigo: ", 1, 999999);
    long long compSeq = 0, compBin = 0, compArv = 0, compOrdenacao = 0;
    int tamanho = mercado.catalogo.tamanho;
    Produto* encontrado = buscaSequencial(mercado.catalogo, codigo, compSeq);
    Produto** vetor = listaParaVetor(mercado.catalogo);
    if (vetor != nullptr) {
        mergeSort(vetor, 0, tamanho - 1, menorPorCodigo, compOrdenacao);
        buscaBinaria(vetor, tamanho, codigo, compBin);
    }
    buscarNaArvore(mercado.indice, codigo, compArv);
    delete[] vetor;
    vetor = nullptr;

    if (encontrado != nullptr) {
        imprimirCabecalhoProdutos();
        imprimirProduto(encontrado);
    } else {
        cout << "Produto nao encontrado.\n";
    }
    cout << "Comparacoes -> sequencial (lista): " << compSeq
         << " | binaria (vetor ordenado): " << compBin
         << " | arvore (BST): " << compArv << "\n";
}

/*
 * Opcao 7: busca produtos que contenham o texto digitado no nome.
 * Parametros: mercado (referencia constante). Retorno: nenhum.
 */
static void opcaoBuscarPorNome(const Supermercado& mercado) {
    string trecho = lerTexto("Parte do nome: ");
    int encontrados = buscarPorNome(mercado.catalogo, trecho);
    cout << encontrados << " produto(s) encontrado(s).\n";
}

/*
 * Coloca um produto no carrinho (empilha) e reserva o estoque.
 * Parametros: mercado (por referencia) e cliente (ponteiro). Retorno: nenhum.
 */
static void adicionarAoCarrinho(Supermercado& mercado, Cliente* cliente) {
    Produto* produto = buscarProduto(mercado, lerInteiro("Codigo do produto: ", 1, 999999));
    if (produto == nullptr) {
        cout << "Produto nao encontrado.\n";
        return;
    }
    if (produto->estoque == 0) {
        cout << "Produto sem estoque.\n";
        return;
    }
    int quantidade = lerInteiro("Quantidade: ", 1, produto->estoque);
    produto->estoque -= quantidade;
    ItemCarrinho item = {produto->codigo, produto->nome, produto->preco, quantidade};
    empilhar(cliente->carrinho, item);
    cout << quantidade << "x " << produto->nome << " adicionado ao carrinho.\n";
}

/*
 * Desfaz a ultima insercao no carrinho (desempilha) e devolve o estoque.
 * Parametros: mercado (por referencia) e cliente (ponteiro). Retorno: nenhum.
 */
static void desfazerUltimoItem(Supermercado& mercado, Cliente* cliente) {
    ItemCarrinho removido;
    if (!desempilhar(cliente->carrinho, removido)) {
        cout << "Nada para desfazer: carrinho vazio.\n";
        return;
    }
    Produto* produto = buscarProduto(mercado, removido.codigo);
    if (produto != nullptr) produto->estoque += removido.quantidade;
    cout << "Desfeito: " << removido.quantidade << "x " << removido.nome << "\n";
}

/*
 * Mostra o submenu de compras de um cliente.
 * Parametros: cliente (ponteiro constante). Retorno: nenhum.
 */
static void exibirMenuCompras(const Cliente* cliente) {
    cout << "\n--- Compras de " << cliente->nome << " ("
         << cliente->carrinho.tamanho << " item(ns)) ---\n"
         << "1. Adicionar produto\n"
         << "2. Desfazer ultimo item (Ctrl+Z)\n"
         << "3. Ver carrinho\n"
         << "4. Ver catalogo\n"
         << "0. Finalizar e ir para a fila do caixa\n";
}

/*
 * Opcao 8: cria um cliente, monta o carrinho e coloca o cliente na fila.
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
static void opcaoNovoCliente(Supermercado& mercado) {
    Cliente* cliente = criarCliente(lerTexto("Nome do cliente: "));
    int opcao;
    do {
        exibirMenuCompras(cliente);
        opcao = lerInteiro("Escolha: ", 0, 4);
        if (opcao == 1) adicionarAoCarrinho(mercado, cliente);
        else if (opcao == 2) desfazerUltimoItem(mercado, cliente);
        else if (opcao == 3) imprimirCarrinho(cliente->carrinho);
        else if (opcao == 4) imprimirLista(mercado.catalogo);
    } while (opcao != 0);

    if (pilhaVazia(cliente->carrinho)) {
        cout << "Carrinho vazio: cliente saiu sem comprar.\n";
        liberarCliente(cliente);
        return;
    }
    enfileirar(mercado.filaCaixa, cliente);
    cout << cliente->nome << " entrou na fila. Posicao: " << mercado.filaCaixa.tamanho << "\n";
}

/*
 * Opcao 10: atende o primeiro da fila, mostra o cupom e libera o cliente.
 * Parametros: mercado (por referencia). Retorno: nenhum.
 */
static void opcaoAtenderCliente(Supermercado& mercado) {
    Cliente* cliente = desenfileirar(mercado.filaCaixa);
    if (cliente == nullptr) {
        cout << "Nenhum cliente na fila.\n";
        return;
    }
    cout << "\n===== CUPOM - " << cliente->nome << " =====\n";
    imprimirCarrinho(cliente->carrinho);
    mercado.faturamento += totalCarrinhoRecursivo(cliente->carrinho.topo);
    mercado.clientesAtendidos++;
    liberarCliente(cliente);
    cout << "Restam " << mercado.filaCaixa.tamanho << " cliente(s) na fila.\n";
}

/*
 * Opcao 12: mostra numeros gerais, varios calculados por recursao.
 * Parametros: mercado (referencia constante). Retorno: nenhum.
 */
static void opcaoEstatisticas(const Supermercado& mercado) {
    cout << "Produtos no catalogo (lista): " << mercado.catalogo.tamanho << "\n"
         << "Nos na arvore (recursivo):    " << contarNos(mercado.indice) << "\n"
         << "Altura da arvore (recursivo): " << alturaArvore(mercado.indice) << "\n"
         << "Clientes na fila:             " << mercado.filaCaixa.tamanho << "\n"
         << "Clientes atendidos:           " << mercado.clientesAtendidos << "\n"
         << "Faturamento: R$ " << fixed << setprecision(2) << mercado.faturamento << "\n";
}

/*
 * Opcao 2: lista os produtos em ordem de codigo usando a travessia in-ordem.
 * Parametros: mercado (referencia constante). Retorno: nenhum.
 */
static void opcaoListarPorCodigo(const Supermercado& mercado) {
    if (mercado.indice == nullptr) {
        cout << "Catalogo vazio.\n";
        return;
    }
    imprimirCabecalhoProdutos();
    percorrerEmOrdem(mercado.indice);
}

/*
 * Direciona a opcao escolhida para a funcao responsavel.
 * Parametros: mercado (por referencia) e opcao. Retorno: nenhum.
 */
void executarOpcao(Supermercado& mercado, int opcao) {
    switch (opcao) {
        case 1: imprimirLista(mercado.catalogo); break;
        case 2: opcaoListarPorCodigo(mercado); break;
        case 3: opcaoOrdenarPorPreco(mercado); break;
        case 4: opcaoCadastrar(mercado); break;
        case 5: opcaoRemover(mercado); break;
        case 6: opcaoBuscarPorCodigo(mercado); break;
        case 7: opcaoBuscarPorNome(mercado); break;
        case 8: opcaoNovoCliente(mercado); break;
        case 9: imprimirFila(mercado.filaCaixa); break;
        case 10: opcaoAtenderCliente(mercado); break;
        case 11: compararDesempenhoBuscas(); break;
        case 12: opcaoEstatisticas(mercado); break;
        default: return;
    }
    pausar();
}
