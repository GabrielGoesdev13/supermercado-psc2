**Centro Universitário Campo Real · Engenharia de Software · Programação e Sistemas Computacionais II**

- **Professor:** Giovane Galvão
- **Aluno:** Gabriel Goes 

---

## Descrição do sistema

Sistema de terminal em C++ que simula a operação de um supermercado:

- **Catálogo de produtos**: cadastrar, remover, listar, ordenar por preço e buscar por código ou por nome.
- **Carrinho de compras**: cada cliente monta seu carrinho e pode **desfazer o último item** (Ctrl+Z), devolvendo o produto ao estoque.
- **Fila do caixa**: o cliente que termina as compras entra na fila e é atendido por ordem de chegada; o atendimento gera o cupom com o total.
- **Comparativo de buscas**: gera um catálogo de 20.000 produtos e compara busca sequencial com busca binária (comparações e tempo).
- **Estatísticas**: tamanho do catálogo, nós e altura da árvore, clientes atendidos e faturamento.

Todas as estruturas de dados foram implementadas manualmente, com ponteiros e `new`/`delete`, sem usar containers da STL.

## Tema escolhido

**Simulador de Supermercado**: fila de atendimento nos caixas, carrinho de compras como pilha, catálogo de produtos com busca binária e ordenação por preço.

## Diagrama das estruturas de dados

```
                              struct Supermercado
   ┌────────────────────────────┬─────────────────────────────┬────────────────────────┐
   │ catalogo  (ListaProdutos)  │ indice  (NoArvore*)         │ filaCaixa  (Fila)      │
   │ é DONA dos Produtos        │ só APONTA para os Produtos  │ é DONA dos Clientes    │
   └────────────────────────────┴─────────────────────────────┴────────────────────────┘
```

**1. Lista encadeada — catálogo** (dona dos produtos; inserção no fim em O(1) graças ao ponteiro `fim`)

```
 inicio                                              fim
   │                                                  │
   ▼                                                  ▼
 [ • | •]──►[ • | •]──►[ • | •]──► ... ──►[ • | ø]
   │          │          │                  │
   ▼          ▼          ▼                  ▼
 Produto    Produto    Produto            Produto      (alocados com new)
  150         75         230                260
```

**2. Árvore binária de busca — índice por código** (cada nó aponta para o MESMO Produto da lista)

```
                  [150]
               /         \
           [75]           [230]
          /    \         /     \
       [40]   [110]   [190]    [300]
       /      /   \       \     /
    [20]   [90] [130]   [210] [260]

 in-ordem (esq → raiz → dir): 20, 40, 75, 90, 110, 130, 150, 190, 210, 230, 260, 300
```

**3. Pilha — carrinho de compras** (LIFO: o último item colocado é o primeiro a sair → "desfazer")

```
 topo
  │
  ▼
 [2x Cafe]──►[1x Arroz]──►[3x Leite]──► ø
```

**4. Fila — caixa** (FIFO: entra no fim, sai do início; cada cliente leva sua pilha)

```
 inicio                          fim
   │                              │
   ▼                              ▼
 [Maria]──►[Joao]──►[Ana]──► ø
    │         │        │
  Pilha     Pilha    Pilha
```

**5. Vetor dinâmico temporário** (`Produto**` criado com `new[]` a partir da lista)

```
 [ •  •  •  •  • ... ]  → Merge Sort por preço (opção 3)
                        → Merge Sort por código + busca binária (opção 6)
                        → liberado com delete[] logo em seguida
```

| Estrutura | Onde é usada | Operações | Complexidade |
|---|---|---|---|
| Lista encadeada (`lista.cpp`) | Catálogo de produtos | inserir no fim, remover por código, percorrer | O(1), O(n), O(n) |
| Pilha (`pilha.cpp`) | Carrinho de compras / desfazer | empilhar, desempilhar, total recursivo | O(1), O(1), O(n) |
| Fila (`fila.cpp`) | Fila do caixa | enfileirar, desenfileirar | O(1), O(1) |
| Árvore binária de busca (`arvore.cpp`) | Índice por código | inserir, buscar, in-ordem, contar, altura | O(log n) médio / O(n) |
| Merge Sort (`ordenacao.cpp`) | Ordenar por preço e por código | ordenação estável | O(n log n) |
| Busca sequencial / binária (`busca.cpp`) | Busca por código e por nome | — | O(n) / O(log n) |

## Requisitos atendidos

| # | Requisito | Onde está |
|---|---|---|
| R1 | Funções (valor, referência, default) | Todo o projeto. Valor: `paraMinusculas(string)`. Referência: `inserirNaLista(ListaProdutos&, ...)`, `liberarCliente(Cliente*&)`. Default: `imprimirProduto(..., bool mostrarEstoque = true)`, `lerInteiro(..., int minimo = 0, ...)`, `compararDesempenhoBuscas(int quantidade = 20000)` |
| R2 | Ponteiros | Nós de todas as estruturas, `Produto**` no vetor, ponteiro para função `Comparador` no Merge Sort |
| R3 | Recursividade | `inserirNaArvore`, `buscarNaArvore`, `percorrerEmOrdem`, `contarNos`, `alturaArvore`, `liberarArvore`, `totalCarrinhoRecursivo`, `mergeSort` |
| R4 | Memória dinâmica | `new` para cada nó, produto, cliente e vetor; `delete`/`delete[]` correspondente e ponteiro = `nullptr` |
| R5 | Lista encadeada | `lista.h` / `lista.cpp` |
| R6 | Pilha | `pilha.h` / `pilha.cpp` (carrinho + desfazer) |
| R7 | Fila | `fila.h` / `fila.cpp` (caixa) |
| R8 | Árvore binária de busca | `arvore.h` / `arvore.cpp` |
| R9 | Algoritmo de ordenação | Merge Sort em `ordenacao.cpp`, com análise de complexidade comentada |
| R10 | Busca sequencial e binária | `busca.cpp`, com contagem de comparações (opção 6) e medição de tempo (opção 11) |

## Estrutura do repositório

```
├── README.md
├── RELATORIO_TECNICO.txt
├── main.cpp            ponto de entrada e laço do menu
├── menu.h / .cpp       telas e opções do menu
├── supermercado.h/.cpp estado geral (catálogo + índice + fila)
├── produto.h / .cpp    struct Produto e comparadores
├── lista.h / .cpp      lista encadeada (catálogo)
├── pilha.h / .cpp      pilha (carrinho)
├── fila.h / .cpp       fila (caixa)
├── arvore.h / .cpp     árvore binária de busca (índice)
├── ordenacao.h / .cpp  Merge Sort
├── busca.h / .cpp      busca sequencial, binária e comparativo
└── entrada.h / .cpp    leitura validada do teclado
```

## Como compilar e executar

Precisa de um compilador C++ (g++ / MinGW no Windows).

```bash
g++ -std=c++17 -Wall -o supermercado src/*.cpp
./supermercado          # Linux / macOS
supermercado.exe        # Windows
```

Verificação de vazamento de memória (Linux):

```bash
valgrind --leak-check=full ./supermercado
# resultado obtido: "All heap blocks were freed -- no leaks are possible"
```

| Integrante | Responsabilidade |
|---|---|
| Gabriel Goes | Modelagem das structs, lista encadeada (catálogo), pilha (carrinho e desfazer), fila (caixa), árvore binária de busca (índice), Merge Sort, buscas sequencial e binária com comparativo, menu, gerenciamento de memória, testes com valgrind, README, relatório técnico e vídeo |
