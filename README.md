# Projeto 2 - Busca e Ordenação

Autores: Aline, João Vitor e Maria Fernanda

## 📄 Descrição
Este projeto implementa três funcionalidades principais sobre textos:

1. **Busca com o algoritmo KMP (Knuth-Morris-Pratt)**
2. **Visualização de trechos com destaque para palavras buscadas**
3. **Cifra por permutação com substituição de caracteres aleatória (criptografia/descriptografia)**

Todas as funcionalidades utilizam **funções auxiliares em `utilidades.cpp`**, como leitura de arquivos, normalização de texto (remoção de acentos e conversão para minúsculas).

## 🧪 Como executar

### Pré-requisitos
- Compilador C++ (g++)
- Terminal com suporte a comandos `make`

### Passos
1. Clone o repositório ou baixe os arquivos
2. No terminal, dentro da pasta do projeto, execute:
   ```bash
   make
   ```
3. Execute o programa:
   ```bash
   ./main
   ```

Se `make` não funcionar, compile manualmente:
```bash
g++ main.cpp kmp.cpp cifra.cpp visualizacao.cpp utilidades.cpp -o main
./main
```

##  Estrutura dos arquivos

| Arquivo             | Descrição                                                             |
|---------------------|-----------------------------------------------------------------------|
| `main.cpp`          | Menu principal e chamadas para os módulos                             |
| `kmp.cpp/hpp`       | Algoritmo KMP de busca de padrões em texto                            |
| `cifra.cpp/hpp`     | Algoritmo de cifra por permutação                                     |
| `visualizacao.cpp`  | Exibe o texto com palavras buscadas destacadas                        |
| `utilidades.cpp/hpp`| Funções de apoio: leitura de arquivo, normalização, remoção de acento.|
| `texto.txt`         | Arquivo de entrada com o conteúdo a ser processado                    |

##  Funcionalidades

###  1. Busca com KMP
- Permite buscar uma palavra no texto carregado
- Mostra as posições em que a palavra aparece

###  2. Visualização com destaque
- Solicita uma palavra
- Exibe o texto com a palavra destacada visualmente

###  3. Cifra por Permutação
- Gera uma chave aleatória usando Fisher-Yates
- Criptografa e em seguida descriptografa o texto
- Aplica normalização antes da cifragem

---

**Observação:** Todos os módulos compartilham a mesma leitura de texto (`texto.txt`) e reutilizam funções auxiliares padronizadas no projeto.

---

## Exemplo de execução
```
Projeto 2 - Busca e Ordenação.
Aline, João Vitor e Maria Fernanda

┌──────────────────────────────────────┐
│                 MENU                 │
├──────────────────────────────────────┤
│ 1 - Busca com KMP                    │
│ 2 - Visualizar Texto Destacado       │
│ 3 - Cifrar / Decifrar Texto          │
│ 0 - Sair                             │
└──────────────────────────────────────┘
Escolha uma opção: 
```

---


