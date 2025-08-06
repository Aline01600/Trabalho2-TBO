/*por enquanto se quiserem testar rode 
g++ -std=c++17 -Wall -O2 -o visualizacao visualizacao.cpp utilitarios.cpp 

./visualizacao
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "utilitarios.hpp"

using namespace std;

const int TAM = 1009;

// Estrutura de entrada
struct Entrada {
    string palavra;
    int frequencia;

    Entrada(const string& p) : palavra(p), frequencia(1) {}
};

struct TabelaHash {
    vector<vector<Entrada>> tabela;

    TabelaHash() {
        tabela.resize(TAM);  // inicializa com TAM buckets
    }

    int hash(const string& chave) {
        int h = 0;
        for (char c : chave) {
            h = (31 * h + c) % TAM;
        }
        return h;
    }

    void inserir(const string& chave) {
        int h = hash(chave);
        for (auto& entrada : tabela[h]) {
            if (entrada.palavra == chave) {
                entrada.frequencia++;
                return;
            }
        }
        tabela[h].emplace_back(chave);  // não achou, insere novo
    }

    vector<pair<string, int>> obter_palavras() {
        vector<pair<string, int>> palavras;
        for (auto& bucket : tabela) {
            for (auto& entrada : bucket) {
                palavras.push_back({entrada.palavra, entrada.frequencia});
            }
        }
        return palavras;
    }
};

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

int main() {
    TabelaHash tabela;

    unordered_set<string> stopwords = carregarStopwords("stopwords.txt");

    string nome_arquivo = "texto.txt";

    processar_arquivo(nome_arquivo, tabela, stopwords);

    auto palavras = tabela.obter_palavras();

    // Ordenar com quicksort por frequência decrescente
    quickSort(palavras, 0, palavras.size() - 1);

    cout << "\nPalavras mais frequentes (ignorando stopwords):\n";
    for (auto& par : palavras) {
        cout << par.first << "  " << par.second << endl;
    }

    return 0;
}
