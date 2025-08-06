#include "cifra.hpp"
#include "utilidades.hpp"
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include <string>
using namespace std;

// Gera uma chave aleatória de substituição (permuta as 26 letras do alfabeto)
void gerarChaveAleatoria(char chave[26]) {
    for (int i = 0; i < 26; ++i) {
        chave[i] = 'a' + i;
    }

    // Embaralha as letras usando Fisher-Yates 
    //Começa do último elemento (índice 25), para cada posição i de 25 até 1.
    //Gera um índice aleatório j tal que 0 ≤ j ≤ i
    //Os elementos são trocados chave[i] e chave[j]

    for (int i = 25; i > 0; --i) {
        int j = rand() % (i + 1);
        char tmp = chave[i];
        chave[i] = chave[j];
        chave[j] = tmp;
    }
}

// Criptografa o texto com base na chave de substituição
string criptografarTexto(const string& entrada, char chave[26]) {
    string texto = normalizarTexto(entrada);  // remove acentos e converte para minúsculo

    for (size_t i = 0; i < texto.size(); ++i) {
        char c = texto[i];
        if (c >= 'a' && c <= 'z') {
            int idx = c - 'a';
            texto[i] = chave[idx];
        }
    }

    return texto;
}

// Descriptografa o texto com base na chave original
string descriptografarTexto(const string& entrada, char chave[26]) {
    char chaveInversa[26];

    // Cria a chave inversa: chaveInversa[chave[i] - 'a'] = 'a' + i
    for (int i = 0; i < 26; ++i) {
        int idx = chave[i] - 'a';
        chaveInversa[idx] = 'a' + i;
    }

    return criptografarTexto(entrada, chaveInversa);
}
