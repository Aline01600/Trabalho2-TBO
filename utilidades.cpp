#include "utilidades.hpp"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

size_t utf8CharLen(unsigned char c) {
    if (c < 128) return 1;
    else if ((c >> 5) == 0x6) return 2;
    else if ((c >> 4) == 0xE) return 3;
    else if ((c >> 3) == 0x1E) return 4;
    return 1;
}

std::string removerAcentos(const std::string& texto) {
    std::unordered_map<std::string, char> mapa = {
        {"á",'a'}, {"à",'a'}, {"ã",'a'}, {"â",'a'}, {"ä",'a'},
        {"é",'e'}, {"è",'e'}, {"ê",'e'}, {"ë",'e'},
        {"í",'i'}, {"ì",'i'}, {"î",'i'}, {"ï",'i'},
        {"ó",'o'}, {"ò",'o'}, {"õ",'o'}, {"ô",'o'}, {"ö",'o'},
        {"ú",'u'}, {"ù",'u'}, {"û",'u'}, {"ü",'u'},
        {"ç",'c'},
        {"Á",'a'}, {"À",'a'}, {"Ã",'a'}, {"Â",'a'}, {"Ä",'a'},
        {"É",'e'}, {"È",'e'}, {"Ê",'e'}, {"Ë",'e'},
        {"Í",'i'}, {"Ì",'i'}, {"Î",'i'}, {"Ï",'i'},
        {"Ó",'o'}, {"Ò",'o'}, {"Õ",'o'}, {"Ô",'o'}, {"Ö",'o'},
        {"Ú",'u'}, {"Ù",'u'}, {"Û",'u'}, {"Ü",'u'},
        {"Ç",'c'}
    };

    std::string resultado;
    for (size_t i = 0; i < texto.size();) {
        size_t len = utf8CharLen((unsigned char)texto[i]);
        std::string c = texto.substr(i, len);

        auto it = mapa.find(c);
        if (it != mapa.end()) resultado += it->second;
        else resultado += c;

        i += len;
    }
    return resultado;
}

std::string paraMinusculo(const std::string& s) {
    std::string resultado;
    for (unsigned char c : s) {
        if (c >= 'A' && c <= 'Z') resultado += c + 32;
        else resultado += c;
    }
    return resultado;
}

std::string normalizarTexto(const std::string& s) {
    return paraMinusculo(removerAcentos(s));
}

std::string lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << arquivo.rdbuf();
    return buffer.str();
}

void imprimirPosicoes(const std::vector<size_t>& posicoes) {
    if (posicoes.empty()) {
        std::cout << "Palavra não encontrada no texto." << std::endl;
    } else {
        std::cout << "Palavra encontrada nas posições: ";
        for (size_t pos : posicoes) {
            std::cout << pos << " ";
        }
        std::cout << std::endl << std::endl;
    }
}
