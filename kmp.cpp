#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Função que constroi vetor de prefixos
std::vector<size_t> construirPrefixo(const std::string& padrao) {
    vector<size_t> prefixo(padrao.length(), 0);
    size_t j = 0;
    
    for (size_t i = 1; i < padrao.length(); i++) {
        while (j > 0 && padrao[i] != padrao[j])
            j = prefixo[j - 1];
        if (padrao[i] == padrao[j])
            j++;
        prefixo[i] = j;
    }

    return prefixo;
}

// Função KMP
std::vector<size_t> buscarKMP(const std::string& texto, const std::string& padrao) {
    vector<size_t> posicoes;
    vector<size_t> prefixo = construirPrefixo(padrao);
    size_t j = 0;

    for (size_t i = 0; i < texto.length(); i++) {
        while (j > 0 && texto[i] != padrao[j])
            j = prefixo[j - 1];

        if (texto[i] == padrao[j])
            j++;

        if (j == padrao.length()) {
            size_t pos = i - j + 1;
            posicoes.push_back(pos);
            j = prefixo[j - 1];
        }
    }
 
    return posicoes;
}
