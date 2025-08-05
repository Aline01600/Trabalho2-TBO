#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int TAM = 1009; // Tamanho da tabela hash (primo para melhor distribuição)

// Função para normalizar a palavra (remover pontuação e colocar em minúsculas)
string normalizar(string palavra) {
    // Remove pontuação no início
    while (!palavra.empty() && ispunct((unsigned char)palavra.front())) {
        palavra.erase(palavra.begin());
    }
    // Remove pontuação no fim
    while (!palavra.empty() && ispunct((unsigned char)palavra.back())) {
        palavra.pop_back();
    }
    
    // Se a palavra não estiver vazia, transforma a primeira letra em minúscula
    if (!palavra.empty()) {
        //Só funciona para ASCII
        palavra[0] = tolower((unsigned char)palavra[0]);
    }
    return palavra;
}

// Estrutura de entrada na tabela hash
struct Entrada {
    string palavra;
    int frequencia;
    bool ocupado;

    Entrada() {
        palavra = "";
        frequencia = 0;
        ocupado = false;
    }
};

// Tabela Hash com endereçamento aberto linear
struct TabelaHash {
    Entrada tabela[TAM];

    int hash(const string& chave) {
        int h = 0;
        for (char c : chave) {
            h = (31 * h + c) % TAM;
        }
        return h;
    }

    void inserir(const string& chave) {
        int h = hash(chave);
        int original = h;
        while (tabela[h].ocupado && tabela[h].palavra != chave) {
            h = (h + 1) % TAM;
            if (h == original) return; // tabela cheia
        }

        if (!tabela[h].ocupado) {
            tabela[h].palavra = chave;
            tabela[h].frequencia = 1;
            tabela[h].ocupado = true;
        } else {
            tabela[h].frequencia++;
        }
    }

    vector<pair<string, int>> obter_palavras() {
        vector<pair<string, int>> palavras;
        for (int i = 0; i < TAM; ++i) {
            if (tabela[i].ocupado) {
                palavras.push_back({tabela[i].palavra, tabela[i].frequencia});
            }
        }
        return palavras;
    }
};

// Função para carregar stopwords de um arquivo em um unordered_set
unordered_set<string> carregarStopwords(const string& nome_arquivo) {
    unordered_set<string> stopwords;
    ifstream arquivo(nome_arquivo);
    if (!arquivo) {
        cerr << "Aviso: não foi possível abrir o arquivo de stopwords: " << nome_arquivo << endl;
        return stopwords; // vazio
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

// Lê todas as palavras do arquivo e insere na tabela (ignorando stopwords)
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

    // Carregue as stopwords de arquivo
    unordered_set<string> stopwords = carregarStopwords("stopwords.txt");

    string nome_arquivo;
   
    nome_arquivo = "texto.txt";

    processar_arquivo(nome_arquivo, tabela, stopwords);

    auto palavras = tabela.obter_palavras();

    // Ordenar por frequência (decrescente)
    sort(palavras.begin(), palavras.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "\nPalavras mais frequentes (ignorando stopwords):\n";
    for (auto& par : palavras) {
        cout << par.first << ": " << par.second << endl;
    }

    return 0;
}
