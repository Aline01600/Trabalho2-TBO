#include <iostream>
#include <fstream>
#include "visualizacao.hpp"


using namespace std;

// QuickSort (ordena por frequência decrescente)
void quickSort(vector<pair<string, int>>& v, int esquerda, int direita) {
    if (esquerda >= direita) return;

    int meio = esquerda + (direita - esquerda) / 2;
    int pivo = v[meio].second;

    int i = esquerda;
    int j = direita;

    while (i <= j) {
        while (v[i].second > pivo) i++;  // Maior frequência primeiro
        while (v[j].second < pivo) j--;

        if (i <= j) {
            pair<string, int> temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            j--;
        }
    }

    if (esquerda < j)
        quickSort(v, esquerda, j);
    if (i < direita)
        quickSort(v, i, direita);
}

// Carregar stopwords
unordered_set<string> carregarStopwords(const string& nome_arquivo) {
    unordered_set<string> stopwords;
    ifstream arquivo(nome_arquivo);
    if (!arquivo) {
        cerr << "Aviso: não foi possível abrir o arquivo de stopwords: " << nome_arquivo << endl;
        return stopwords;
    }
    string palavra;
    while (arquivo >> palavra) {
        palavra = normalizar(palavra);
        if (!palavra.empty()) {
            stopwords.insert(palavra);
        }
    }
    return stopwords;
}

// Processar arquivo de texto
void processar_arquivo(const string& nome_arquivo, TabelaHash& tabela, const unordered_set<string>& stopwords) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return;
    }

    string palavra;
    while (arquivo >> palavra) {
        string limpa = normalizar(palavra);
        if (!limpa.empty() && stopwords.count(limpa) == 0) {
            tabela.inserir(limpa);
        }
    }

    arquivo.close();
}
