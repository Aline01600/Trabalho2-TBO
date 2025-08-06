/* ARQUIVO COM FUNÇÕES ÚTEIS. SE HÁ UMA FUNÇÃO ÚTIL AO PROJETO COMO UM TODO, COLOQUE AQUI*/

#include "utilidades.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>


// Função que remove os acentos da string
string removerAcentos(const string& texto) {
    unordered_map<string, char> mapa = {
        {"á",'a'}, {"à",'a'}, {"ã",'a'}, {"â",'a'}, {"ä",'a'},
        {"é",'e'}, {"è",'e'}, {"ê",'e'}, {"ë",'e'},
        {"í",'i'}, {"ì",'i'}, {"î",'i'}, {"ï",'i'},
        {"ó",'o'}, {"ò",'o'}, {"õ",'o'}, {"ô",'o'}, {"ö",'o'},
        {"ú",'u'}, {"ù",'u'}, {"û",'u'}, {"ü",'u'},
        {"ç",'c'},
        {"Á",'a'}, {"À",'a'}, {"Ã",'a'}, {"Â",'a'}, {"Ä",'a'},
        {"É",'e'}, {"È",'e'}, {"Ê",'e'}, {"Ë",'e'},
        {"Í",'i'}, {"Ì",'i'}, {"Î",'i'}, {"Ï",'i'},
        {"Ó",'o'}, {"Ò",'o'}, {"Õ",'o'}, {"Ô",'o'}, {"Ö",'o'},
        {"Ú",'u'}, {"Ù",'u'}, {"Û",'u'}, {"Ü",'u'},
        {"Ç",'c'}
    };

    string resultado;
    for (size_t i = 0; i < texto.size();) {
        // Se for o início de um caractere UTF-8 multibyte
        if ((unsigned char)texto[i] >= 192) {
            string caractere_utf8 = texto.substr(i, 2);
            auto it = mapa.find(caractere_utf8);
            if (it != mapa.end()) {
                resultado += it->second;
            } else {
                resultado += caractere_utf8;
            }
            i += 2;
        } else {
            resultado += texto[i];
            i++;
        }
    }

    return resultado;
}

// Função que transforma a string em minúscula
string paraMinusculo(const string& s) {
    string resultado = s;

    for (size_t i = 0; i < resultado.size(); i++) {
        char c = resultado[i];      
        /* Em ASCII:
            -  letras maiúsculas vão do 'A' (65) até 'Z' (90)
            -  letras minúsculas vão do 'a' (97) até 'z' (122)

            A diferença entre maiúscula e minúscula é 32, então somando 32 ao caractere, é encontrada sua versão minúsucla
        */
        if (c >= 'A' && c <= 'Z') {
            resultado[i] = c + 32;
        }
    }
    return resultado;    
}

// Converte a string para facilitar a manipulação
string normalizarTexto(const string& s) {
    string resultado;

    // remove acento
    resultado = removerAcentos(s);
    // deixa minúsculo
    resultado = paraMinusculo(resultado);

    return resultado;
}


// Lê um arquivo .txt e retorna uma string
string lerArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    // tratamento de erro
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return "";
    }

    stringstream buffer;
    buffer << arquivo.rdbuf(); // copia a leitura do arquivo para o buffer

    return buffer.str(); // converte o buffer em string e retorna
}

string normalizar(const string& palavra) {
    string limpa;
    for (unsigned char c : palavra) {
        if (isalpha(c) || (c >= 128)) {
            limpa += tolower(c);
        }
    }
    return limpa;
}