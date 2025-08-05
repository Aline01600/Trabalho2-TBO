#include <iostream>
#include <string>
#include <vector>
#include "kmp.hpp"
#include "utilidades.hpp"

using namespace std;

// Cabeçalhos das funções que administram as tarefas
void administraKMP(const string& texto);


int main() {
    size_t escolhaMenu;

    // boas-vindas
    cout << "\n\tProjeto 2 - Busca e Ordenação." << endl;
    cout << "\tAline, João Vitor e Maria Fernanda" << endl << endl;

    // leitura do arquivo de texto
    string texto = lerArquivo("texto.txt");

    // Menu
    while(true){
        cout << "┌──────────────────────────────────────┐" << endl;
        cout << "│                 MENU                 │" << endl;
        cout << "├──────────────────────────────────────┤" << endl;
        cout << "│ 1 - Busca com KMP                    │" << endl;
        cout << "│ 2 - Opção 2                          │" << endl;
        cout << "│ 3 - Opção 3                          │" << endl;
        cout << "│ 0 - Sair                             │" << endl;
        cout << "└──────────────────────────────────────┘" << endl;
        cout << "Escolha uma opção: ";
        cin >> escolhaMenu;

        switch (escolhaMenu)
        {
        case 1:
            administraKMP(texto);
            break;

        case 0:
            return 0;

        default:
            cout << "Opção errada, escolha novamente!" << endl;
            break;
        }
    }
}


void administraKMP(const string& texto) {
    string palavra;

    cin.ignore(); // <- limpa o \n pendente no buffer

    cout << "\nTexto carregado!" << endl;

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
        cout << endl << endl;
    }


    // pausa para o usuário ler melhor os dados
    cout << "Pressione Enter para continuar...";
    cin.get();    // espera o Enter
}