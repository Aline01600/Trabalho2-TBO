#include "utilitarios.hpp"
#include <cctype>

std::string normalizar(const std::string& palavra) {
    std::string limpa;
    for (unsigned char c : palavra) {
        if (std::isalpha(c) || (c >= 128)) {
            limpa += std::tolower(c);
        }
    }
    return limpa;
}
