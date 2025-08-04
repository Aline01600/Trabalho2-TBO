#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

const int TAM = 1009; // Tamanho da tabela hash (primo para melhor distribuição)

// Lista de stopwords comuns em português
const string STOPWORDS[] = {
    "a", "o", "e", "de", "do", "da", "em", "um", "uma", "os", "as", "no", "na",
    "por", "com", "que", "para", "como", "se", "não", "mas", "ou", "já", "foi",
    "são", "é", "dos", "das", "ao", "aos", "às", "há", "à", "isso", "esta", "este",
    "esses", "essas", "também", "tão", "só", "quando", "quanto", "pelo", "pela", "porque"
};
const int QTD_STOPWORDS = sizeof(STOPWORDS) / sizeof(string);

// Função para verificar se a palavra é uma stopword
bool eh_stopword(const string& palavra) {
    for (int i = 0; i < QTD_STOPWORDS; ++i) {
        if (palavra == STOPWORDS[i]) return true;
    }
    return false;
}

// Função para normalizar a palavra (remover pontuação e colocar em minúsculas)
string normalizar(string palavra) {
    string resultado;
    for (char c : palavra) {
        if (isalpha(c)) {
            resultado += tolower(c);
        }
    }
    return resultado;
}

// Estrutura de entrada na tabela hash
struct Entrada {
    string chave;
    int frequencia;
    bool ocupado;

    Entrada() {
        chave = "";
        frequencia = 0;
        ocupado = false;
    }
};

// Tabela Hash com endereçamento aberto linear
struct TabelaHash {
    Entrada tabela[TAM];

    int hash(string chave) {
        int h = 0;
        for (char c : chave) {
            h = (31 * h + c) % TAM;
        }
        return h;
    }

    void inserir(string chave) {
        int h = hash(chave);
        int original = h;
        while (tabela[h].ocupado && tabela[h].chave != chave) {
            h = (h + 1) % TAM;
            if (h == original) return; // tabela cheia
        }

        if (!tabela[h].ocupado) {
            tabela[h].chave = chave;
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
                palavras.push_back({tabela[i].chave, tabela[i].frequencia});
            }
        }
        return palavras;
    }
};

// Lê todas as palavras do arquivo e insere na tabela
void processar_arquivo(const string& nome_arquivo, TabelaHash& tabela) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string palavra;
    while (arquivo >> palavra) {
        string limpa = normalizar(palavra);
        if (!limpa.empty() && !eh_stopword(limpa)) {
            tabela.inserir(limpa);
        }
    }

    arquivo.close();
}

int main() {
    TabelaHash tabela;
    string nome_arquivo;

    nome_arquivo = "texto.txt";
   
    processar_arquivo(nome_arquivo, tabela);

    auto palavras = tabela.obter_palavras();

    cout << "\nPalavras mais frequentes:\n";
    for (auto& par : palavras) {
        cout << par.first << ": " << par.second << endl;
    }

    return 0;
}
