# Nombre del ejecutable
TARGET = vernam

# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Archivos fuente y objetos
SRCS = src/vernam.cc src/vernam_main.cc
OBJS = $(SRCS:.cc=.o)

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar archivos .cc a .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean