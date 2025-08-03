#include <vector>
#include <string>

using namespace std;

// Função que constroi vetor de prefixos
std::vector<size_t> construirPrefixo(const std::string& padrao) {
    int m = padrao.length(), j = 0;
    vector<size_t> prefixo(m);
    
    for (int i = 1; i < m; i++) {
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
            posicoes.push_back(i - j + 1);
            j = prefixo[j - 1];
        }
    }
    
    return posicoes;
}
