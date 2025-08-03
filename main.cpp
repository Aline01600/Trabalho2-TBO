#include <iostream>
#include <string>
#include <vector>
#include "kmp.hpp"

using namespace std;

int main() {
    string texto, palavra;

    cout << "Digite um texto: " << endl;
    getline(cin, texto);

    cout << "Digite a palavra a ser buscada: ";
    getline(cin, palavra);

    vector<size_t> posicoes = buscarKMP(texto, palavra);

    if (posicoes.empty()) {
        cout << "Palavra não encontrada no texto." << endl;
    } else {
        cout << "Palavra encontrada nas posições: ";
        for (size_t pos : posicoes) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}
