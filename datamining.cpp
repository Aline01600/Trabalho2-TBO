#include <string>
#include <vector>
#include <iostream>
#include <cctype>

using namespace std;

// verifica se o caractere é um dígito
inline bool ehDigito(char c) {
    return c >= '0' && c <= '9';
}

// BUSCAS POR DATAS

// verifica se uma string é uma data
bool ehData(const string& texto, size_t pos) {

    if (pos + 9 >= texto.size()) return false;

    return (
        ehDigito(texto[pos]) &&     // primeiro campo do dia
        ehDigito(texto[pos+1]) &&   // segundo campo do dia
        texto[pos+2] == '/' &&      // primeiro separador
        ehDigito(texto[pos+3]) &&   // primeiro campo do mês
        ehDigito(texto[pos+4]) &&   // segundo campo do mês
        texto[pos+5] == '/' &&      // segundo separador
        ehDigito(texto[pos+6]) &&   // primeiro campo do ano
        ehDigito(texto[pos+7]) &&   // segundo campo do ano
        ehDigito(texto[pos+8]) &&   // terceiro campo do ano
        ehDigito(texto[pos+9])      // quarto campo do ano
    );
}

bool ehDataCurta(const std::string& texto, size_t pos) {
    if (pos + 4 >= texto.size()) return false;

    return (
        (texto[pos] >= '0' && texto[pos] <= '9') &&
        (texto[pos+1] >= '0' && texto[pos+1] <= '9') &&
        texto[pos+2] == '/' &&
        (texto[pos+3] >= '0' && texto[pos+3] <= '9') &&
        (texto[pos+4] >= '0' && texto[pos+4] <= '9')
    );
}

// impressão das datas no formato adequado
void imprimeDatas(const vector<size_t>& posicoes, const string& texto) {
    cout << endl;
    if (posicoes.empty()) {
        cout << "Nenhuma data encontrada no texto." << endl;
        return;
    }

    cout << "Datas encontradas:" << endl;
    for (size_t pos : posicoes) {
        // Decide se é data curta ou longa
        if (pos + 9 < texto.size() && ehData(texto, pos)) {
            cout << texto.substr(pos, 10) << " (posição " << pos << ")" << endl;
        }
        else if (pos + 4 < texto.size() && ehDataCurta(texto, pos)) {
            cout << texto.substr(pos, 5) << " (posição " << pos << ")" << endl;
        }
    }
    cout << endl;
}

// procura por datas no texto
void encontrarDatas(const string& texto) {
    vector<size_t> posicoes_datas;
    posicoes_datas.reserve(20);

    size_t i = 0;
    while (i + 9 < texto.size()) {

        // verifica se é um dígito numérico
        if (texto[i] < '0' || texto[i] > '9') {
            ++i; // pula caractere não numérico
            continue;
        }

        // se for um dígito, verifica se é data
        if (ehData(texto, i)) {
            posicoes_datas.push_back(i);
            i += 10; // pula a data inteira
        } else if (i + 4 < texto.size() && ehDataCurta(texto, i)) {
            posicoes_datas.push_back(i);
            i += 5;  // pula data curta (dd/mm)
        } else {
            ++i;
        }
    }
    imprimeDatas(posicoes_datas, texto);
}


// BUSCA POR TELEFONES

// Função para imprimir os telefones encontrados no formato adequado
void imprimeTelefones(const vector<pair<size_t, size_t>>& posicoes, const string& texto) {
    cout << endl;
    if (posicoes.empty()) {
        cout << "Nenhum telefone encontrado." << endl;
        return;
    }

    cout << "Telefones encontrados:" << endl;
    for (const auto& p : posicoes) {
        cout << texto.substr(p.first, p.second) << " (posição " << p.first << ")" << endl;
    }
    cout << endl;
}

// Verifica se substring a partir de pos é telefone fixo: (DD) ####-####
bool ehTelefoneFixo(const string& texto, size_t pos) {
    if (pos + 13 >= texto.size()) return false;

    return texto[pos] == '(' &&
           ehDigito(texto[pos+1]) && ehDigito(texto[pos+2]) &&
           texto[pos+3] == ')' && texto[pos+4] == ' ' &&
           ehDigito(texto[pos+5]) && ehDigito(texto[pos+6]) &&
           ehDigito(texto[pos+7]) && ehDigito(texto[pos+8]) &&
           texto[pos+9] == '-' &&
           ehDigito(texto[pos+10]) && ehDigito(texto[pos+11]) &&
           ehDigito(texto[pos+12]) && ehDigito(texto[pos+13]);
}

// Verifica se substring a partir de pos é celular: (DD) 9 ####-####
bool ehCelular(const string& texto, size_t pos) {
    if (pos + 15 >= texto.size()) return false;

    return texto[pos] == '(' &&
           ehDigito(texto[pos+1]) && ehDigito(texto[pos+2]) &&
           texto[pos+3] == ')' && texto[pos+4] == ' ' &&
           texto[pos+5] == '9' && texto[pos+6] == ' ' &&
           ehDigito(texto[pos+7]) && ehDigito(texto[pos+8]) &&
           ehDigito(texto[pos+9]) && ehDigito(texto[pos+10]) &&
           texto[pos+11] == '-' &&
           ehDigito(texto[pos+12]) && ehDigito(texto[pos+13]) &&
           ehDigito(texto[pos+14]) && ehDigito(texto[pos+15]);
}

// Verifica se é telefone curto: 3 dígitos só
bool ehTelefoneCurto(const string& texto, size_t pos) {
    if (pos + 2 >= texto.size()) return false;

    return texto[pos] == '1' && ehDigito(texto[pos+1]) && ehDigito(texto[pos+2]) &&
        (pos == 0 || !ehDigito(texto[pos-1])) &&  // não faz parte de número maior
        (pos + 3 >= texto.size() || !ehDigito(texto[pos+3]));
}

// Função que encontra todas as posições dos telefones no texto
void encontrarTelefones(const string& texto) {
    vector<pair<size_t, size_t>> posicoes; // par: (posição, tamanho)
    posicoes.reserve(20);

    size_t i = 0;
    while (i < texto.size()) {
        if (ehCelular(texto, i)) {
            posicoes.push_back({i, 16}); // celular tem 16 chars
            i += 16;
        } else if (ehTelefoneFixo(texto, i)) {
            posicoes.push_back({i, 14}); // fixo tem 14 chars
            i += 14;
        } else if (ehTelefoneCurto(texto, i)) {
            posicoes.push_back({i, 3});  // curto tem 3 chars
            i += 3;
        } else {
            ++i;
        }
    }
    imprimeTelefones(posicoes, texto);
}


// EMAILS

// Verifica se um caractere pode estar em um nome de usuário de e-mail
inline bool caractereEmailValido(char c) {
    return isalnum(c) || c == '.' || c == '-' || c == '_';
}

// Verifica se um caractere pode estar no domínio
inline bool caractereDominioValido(char c) {
    return isalnum(c) || c == '.' || c == '-';
}

// impressão dos emails em formato válido
void imprimeEmails(const vector<pair<size_t, string>>& emails) {
    if (emails.empty()) {
        cout << "Nenhum e-mail encontrado." << endl;
        return;
    }

    cout << "E-mails encontrados:\n";
    for (const auto& [pos, email] : emails) {
        cout << "- " << email << " (posição: " << pos << ")\n";
    }
    cout << endl;
}


// Busca e-mails no texto// Busca e-mails no texto e retorna pares: <posição inicial, email>
void encontrarEmails(const string& texto) {
    vector<pair<size_t, string>> emails;
    emails.reserve(20);

    for (size_t i = 0; i < texto.size(); ++i) {
        if (texto[i] == '@') {
            // parte anterior ao @
            size_t inicio = i;
            while (inicio > 0 && caractereEmailValido(texto[inicio - 1]))
                --inicio;

            // parte posterior ao @
            size_t fim = i + 1;
            while (fim < texto.size() && (caractereEmailValido(texto[fim]) || texto[fim] == '.'))
                ++fim;

            // extrai o email completo
            if (fim - inicio >= 5) { // mínimo: a@b.c
                string email = texto.substr(inicio, fim - inicio);
                emails.push_back({inicio, email});
                i = fim - 1;
            }
        }
    }

    imprimeEmails(emails);
}