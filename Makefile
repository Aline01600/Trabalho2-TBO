# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Arquivos
SOURCES = main.cpp kmp.cpp utilidades.cpp cifra.cpp visualizacao.cpp datamining.cpp
HEADERS = kmp.hpp utilidades.hpp cifra.hpp visualizacao.hpp datamining.hpp
OBJECTS = $(SOURCES:.cpp=.o)

# Executável
TARGET = programa

# Regra padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação de .cpp para .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

# Limpeza
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean run
