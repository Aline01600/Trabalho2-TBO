#ifndef CIFRA_HPP
#define CIFRA_HPP

#include <string>
using std::string;

// Gera uma chave de permutação aleatória para a cifra
void gerarChaveAleatoria(char chave[26]);

// Criptografa um texto normalizado com a chave fornecida
string criptografarTexto(const string& entrada, char chave[26]);

// Descriptografa um texto cifrado com a mesma chave original
string descriptografarTexto(const string& entrada, char chave[26]);

#endif
