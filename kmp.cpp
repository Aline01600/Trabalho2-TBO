#include <vector>
#include <string>
#include <iostream>
#include "utilidades.hpp"

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

    // VERIFICAÇÕES INICIAIS DE SEGURANÇA
    // Se não tiver palavra a ser procurada:
    if (padrao.empty()) {
        cout << "\nNão há palavra a ser procurada!" << endl;
        return {};
    }

    // Se não tiver texto para procurar a palavra:
    if (texto.empty()) {
        cout << "\nNão há texto a ser percorrido!" << endl;
        return {}; 
    }

    // Se a palavra a ser procurada for maior que o texto:
    if (padrao.size() > texto.size()) {
        cout << "\nA palavra a ser encontrada é maior que o texto!" << endl;
        return {}; 
    }


    string text, pattern;

    text = normalizarTexto(texto);
    pattern = normalizarTexto(padrao);
    
    vector<size_t> posicoes;
    vector<size_t> prefixo = construirPrefixo(pattern);
    size_t j = 0, n = text.length(), total_ocorrencias = 0;

    posicoes.reserve(20);   // reserva 20 espaços de memória para guardar as posições encontradas. Isso evita de ficar dobrando o vector a cada nova palavra encontrada. O(n) -> O(1) para as 20 primeiras posições

    for (size_t i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j])
            j = prefixo[j - 1];

        if (text[i] == pattern[j])
            j++;

        if (j == pattern.length()) {
            size_t pos = i - j + 1;
            posicoes.push_back(pos);
            j = prefixo[j - 1];
            total_ocorrencias++;
        }
    }

    cout << "\nNúmero total de ocorrências desta palavra: " << total_ocorrencias << endl;

    return posicoes;
}
