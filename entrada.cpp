#include "entrada.h"
#include <iostream>
#include <limits>

using namespace std;

/*
 * Le um numero decimal do teclado, repetindo ate o valor ser valido.
 * Parametros: mensagem, minimo e maximo (parametros default).
 * Retorno: valor digitado (ou o minimo, se a entrada acabar).
 */
double lerDecimal(const string& mensagem, double minimo, double maximo) {
    double valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor && valor >= minimo && valor <= maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        if (cin.eof()) return minimo;
        cout << "Valor invalido. Digite entre " << minimo << " e " << maximo << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/*
 * Le um numero inteiro reaproveitando lerDecimal (evita repetir a validacao).
 * Parametros: mensagem, minimo e maximo (parametros default).
 * Retorno: inteiro digitado.
 */
int lerInteiro(const string& mensagem, int minimo, int maximo) {
    while (true) {
        double valor = lerDecimal(mensagem, minimo, maximo);
        if (valor == static_cast<int>(valor)) return static_cast<int>(valor);
        cout << "Digite um numero inteiro.\n";
    }
}

/*
 * Le uma linha de texto nao vazia.
 * Parametros: mensagem. Retorno: texto digitado.
 */
string lerTexto(const string& mensagem) {
    string texto;
    while (texto.empty()) {
        cout << mensagem;
        if (!getline(cin, texto)) return "Sem nome";
    }
    return texto;
}

/*
 * Espera o usuario apertar ENTER para continuar.
 * Parametros: nenhum. Retorno: nenhum.
 */
void pausar() {
    cout << "\nPressione ENTER para continuar...";
    string descarte;
    getline(cin, descarte);
}
