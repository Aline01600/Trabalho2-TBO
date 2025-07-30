# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Arquivos
SOURCES = main.cpp kmp.cpp
HEADERS = kmp.hpp
OBJECTS = $(SOURCES:.cpp=.o)

# Executável
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
