#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "kmp.hpp"
#include "datamining.hpp"
#include "utilidades.hpp"
#include "cifra.hpp"
#include "visualizacao.hpp"

using namespace std;

// Cabeçalhos das funções que administram as tarefas
void administraKMP(const string& texto);
void administraCifra(const string& texto);
void administraVisualizacao();
void administraDataMining(const string& texto);

void mostrarResumoEGerarArquivoOpcional(const string& texto, const string& nomeArquivo, int linhasParaMostrar = 10) {
    // Mostra as primeiras linhas no terminal
    int linhasMostradas = 0;
    for (size_t i = 0; i < texto.size() && linhasMostradas < linhasParaMostrar; ++i) {
        cout << texto[i];
        if (texto[i] == '\n') linhasMostradas++;
    }
    cout << "\n[... texto truncado ...]\n";

    // Pergunta se usuário quer salvar o texto completo em arquivo
    cout << "Deseja salvar o texto completo no arquivo '" << nomeArquivo << "'? (s/n): ";
    char opcao;
    cin >> opcao;
    cin.ignore(); // limpa o \n pendente

    if (opcao == 's' || opcao == 'S') {
        ofstream arq(nomeArquivo);
        if (!arq) {
            cerr << "Erro ao abrir arquivo para salvar o texto: " << nomeArquivo << endl;
            return;
        }
        arq << texto;
        arq.close();
        cout << "Texto completo salvo em '" << nomeArquivo << "'." << endl;
    } else {
        cout << "Arquivo não salvo." << endl;
    }
}


int main() {
    size_t escolhaMenu;

    // boas-vindas
    cout << "\n\tProjeto 2 - Busca e Ordenação." << endl;
    cout << "\tAline, João Vitor e Maria Fernanda" << endl << endl;

    // leitura do arquivo de texto
    string texto = lerArquivo("texto.txt");

    // Menu
    while(true){
       /* cout << "┌──────────────────────────────────────┐" << endl;
        cout << "│                 MENU                 │" << endl;
        cout << "├──────────────────────────────────────┤" << endl;
        cout << "│ 1 - Busca com KMP                    │" << endl;
        cout << "│ 2 - Opção 2                          │" << endl;
        cout << "│ 3 - Opção 3                          │" << endl;
        cout << "│ 0 - Sair                             │" << endl;
        cout << "└──────────────────────────────────────┘" << endl;
        cout << "Escolha uma opção: ";
        cin >> escolhaMenu;
*/
        cout << "===============================" << endl;
cout << "           MENU                " << endl;
cout << "===============================" << endl;
cout << "1 - Busca com KMP" << endl;
cout << "2 - Visualizar" << endl;
cout << "3 - Cifrar / Decifrar Texto" << endl;
cout << "4 - Data Mining" << endl;
cout << "0 - Sair" << endl;
cout << "===============================" << endl;
cout << "Escolha uma opcao: ";
        cin >> escolhaMenu;
        switch (escolhaMenu)
        {
        case 1:
            administraKMP(texto);
            break;
        case 2:
            administraVisualizacao();
            break;
        case 3:
            administraCifra(texto);
            break;
        case 4:
            administraDataMining(texto);
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
    imprimirPosicoes(posicoes);

    // pausa para o usuário ler melhor os dados
    cout << "Pressione Enter para continuar...";
    cin.get();    // espera o Enter
}

void administraCifra(const string& texto) {
    char chave[26];
    gerarChaveAleatoria(chave);

    string criptografado = criptografarTexto(texto, chave);
    string decifrado = descriptografarTexto(criptografado, chave);

    cout << "\nTexto original normalizado e cifrado:" << endl;
    mostrarResumoEGerarArquivoOpcional(criptografado, "cifrado.txt");

    cout << "\nTexto decifrado:" << endl;
    mostrarResumoEGerarArquivoOpcional(decifrado, "decifrado.txt");

    cout << "\nPressione Enter para continuar...";
    cin.get(); // espera o Enter para continuar
}

void administraVisualizacao(){
    TabelaHash tabela;

    unordered_set<string> stopwords = carregarStopwords("stopwords.txt");

    string nome_arquivo = "texto.txt";

    processar_arquivo(nome_arquivo, tabela, stopwords);

    auto palavras = tabela.obter_palavras();

    // Ordenar com quicksort por frequência decrescente
    quickSort(palavras, 0, palavras.size() - 1);

    cout << "\nPalavras mais frequentes do Texto:\n";
    for (auto& par : palavras) {
        cout << par.first << "  " << par.second << endl;
    }
}

void administraDataMining(const string& texto) {
    size_t escolhaMenu;

    // Menu
    while(true){
        cout << "┌──────────────────────────────────────┐" << endl;
        cout << "│                 MENU                 │" << endl;
        cout << "├──────────────────────────────────────┤" << endl;
        cout << "│ 1 - Buscar datas                     │" << endl;
        cout << "│ 2 - Buscar telefones                 │" << endl;
        cout << "│ 3 - Buscar emails                    │" << endl;
        cout << "│ 0 - Sair                             │" << endl;
        cout << "└──────────────────────────────────────┘" << endl;
        cout << "Escolha uma opção: ";
        cin >> escolhaMenu;

        switch (escolhaMenu)
        {
        case 1:
            encontrarDatas(texto);
            break;

        case 2:
            encontrarTelefones(texto);
            break;

        case 3:
            encontrarEmails(texto);
            break;

        case 0:
            return;

        default:
            cout << "Opção errada, escolha novamente!" << endl;
            break;
        }
    }
}