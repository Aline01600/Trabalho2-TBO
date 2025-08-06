#ifndef VISUALIZACAO
#define VISUALIZACAO

#include <string>
#include <vector>
#include <unordered_set>
#include "utilidades.hpp"
const int TAM = 1009;

struct Entrada {
    std :: string palavra;
    int frequencia;

    Entrada(const std :: string& p) : palavra(p), frequencia(1) {}
};

struct TabelaHash {
    std :: vector<std :: vector<Entrada>> tabela;

    TabelaHash() {
        tabela.resize(TAM);  // inicializa com TAM buckets
    }

    int hash(const std :: string& chave) {
        int h = 0;
        for (char c : chave) {
            h = (31 * h + c) % TAM;
        }
        return h;
    }

    void inserir(const std :: string& chave) {
        int h = hash(chave);
        for (auto& entrada : tabela[h]) {
            if (entrada.palavra == chave) {
                entrada.frequencia++;
                return;
            }
        }
        tabela[h].emplace_back(chave);  // não achou, insere novo
    }

    std :: vector< std :: pair< std :: string, int>> obter_palavras() {
        std :: vector<std :: pair< std :: string, int>> palavras;
        for (auto& bucket : tabela) {
            for (auto& entrada : bucket) {
                palavras.push_back({entrada.palavra, entrada.frequencia});
            }
        }
        return palavras;
    }
};

void quickSort(std :: vector< std :: pair<std :: string, int>>& v, int esquerda, int direita);
std :: unordered_set<std :: string> carregarStopwords(const std :: string& nome_arquivo); 
void mapear_string_normalizada(const std::string& texto_normalizado, TabelaHash& tabela, const std::unordered_set<std::string>& stopwords);
#endif