#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Função que transforma a string em minúscula
string paraMinusculo(const string& s) {
    string resultado = s;

    for (size_t i = 0; i < resultado.size(); i++) {
        char c = resultado[i];
        
        /* Em ASCII:
            -  letras maiúsculas vão do 'A' (65) até 'Z' (90)
            -  letras minúsculas vão do 'a' (97) até 'z' (122)

            A diferença entre maiúscula e minúscula é 32, então somando 32 ao caractere, é encontrada sua versão minúsucla
        */
    
        if (c >= 'A' && c <= 'Z') {
            resultado[i] = c + 32;
        }
    }
    return resultado;    
}

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

    text = paraMinusculo(texto);
    pattern = paraMinusculo(padrao);
    
    vector<size_t> posicoes;
    vector<size_t> prefixo = construirPrefixo(pattern);
    size_t j = 0;

    for (size_t i = 0; i < text.length(); i++) {
        while (j > 0 && text[i] != pattern[j])
            j = prefixo[j - 1];

        if (text[i] == pattern[j])
            j++;

        if (j == pattern.length()) {
            size_t pos = i - j + 1;
            posicoes.push_back(pos);
            j = prefixo[j - 1];
        }
    }
 
    return posicoes;
}
