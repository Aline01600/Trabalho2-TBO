#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <vector>

using namespace std;

string paraMinusculo(const string& s);
string removerAcentos(const string& s);
string lerArquivo(const string& nomeArquivo);
string normalizarTexto(const string& s);
string normalizar(const string& palavra);
void imprimirPosicoes(const vector<size_t>& posicoes);

#endif
