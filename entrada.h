#ifndef ENTRADA_H
#define ENTRADA_H

#include <string>

double lerDecimal(const std::string& mensagem, double minimo = 0.0, double maximo = 1000000.0);
int lerInteiro(const std::string& mensagem, int minimo = 0, int maximo = 1000000);
std::string lerTexto(const std::string& mensagem);
void pausar();

#endif
