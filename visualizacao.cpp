#include "visualizacao.hpp"
#include "utilidades.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

// QuickSort
void quickSort(std::vector<std::pair<std::string,int>>& v, int esquerda, int direita) {
    if (esquerda >= direita) return;

    int meio = esquerda + (direita-esquerda)/2;
    int pivo = v[meio].second;
    int i=esquerda, j=direita;

    while(i <= j){
        while(v[i].second > pivo) i++;
        while(v[j].second < pivo) j--;
        if(i <= j){
            std::swap(v[i], v[j]);
            i++; j--;
        }
    }

    if(esquerda<j) quickSort(v, esquerda, j);
    if(i<direita) quickSort(v, i, direita);
}

// Carregar stopwords
std::unordered_set<std::string> carregarStopwords(const std::string& nome_arquivo){
    std::unordered_set<std::string> stopwords;
    std::ifstream arquivo(nome_arquivo);
    if(!arquivo){
        std::cerr << "Aviso: não foi possível abrir o arquivo de stopwords: " << nome_arquivo << std::endl;
        return stopwords;
    }
    std::string palavra;
    while(arquivo >> palavra){
        palavra = normalizarTexto(palavra);
        if(!palavra.empty()) stopwords.insert(palavra);
    }
    return stopwords;
}

// Mapear texto normalizado para tabela hash
void mapear_string_normalizada(const std::string& texto, TabelaHash& tabela, const std::unordered_set<std::string>& stopwords){
    std::istringstream stream(texto);
    std::string palavra;

    while(stream >> palavra){
        palavra = normalizarTexto(palavra);

        std::string limpa;
        for(char c : palavra){
            if((c>='a' && c<='z') || (c>='A' && c<='Z')) limpa += c;
        }

        if(!limpa.empty() && stopwords.find(limpa)==stopwords.end()){
            tabela.inserir(limpa);
        }
    }
}
