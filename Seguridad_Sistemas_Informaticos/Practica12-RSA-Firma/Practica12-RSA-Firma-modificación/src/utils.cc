#include "utils.h"
#include "utils.h"

/**
 * @brief Método para elevar una base a una potencia módulo un número, utilizando el método de exponenciación rápida. 
 * @param base - La base que se desea elevar a una potencia.
 * @param exp - La potencia a la que se desea elevar la base.
 * @param mod - El número módulo el cual se desea calcular la potencia.
 * @return long long El resultado de (base^exp) % mod.
 */
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    long long b = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) result = (result * b) % mod;
        b = (b * b) % mod;
        exp /= 2;
    }
    return result;
}

/**
 * @brief Funcion para determinar si un numero p es primo usando el test de Lehman-Peralta.
 * 
 * @param p - El numero a evaluar si es primo.
 * @return true Si es primo
 * @return false Si no es primo
 */
bool testLehmanPeralta(long long p) {
    if ( p == 2 || p == 3 || p == 5 || p == 7 || p == 11) return true;
    if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0 || p % 11 == 0) return false;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 1; i <= 10; i++) {
        std::uniform_int_distribution<long long> dis(2, p-2);
        long long a = dis(gen);
        long long r = modExp(a, (p-1)/2, p);
        
        if (r != 1 && r != p-1) {
            return false;
        }
    }   
    return true;
}

/**
 * @brief Función para calcular el inverso multiplicativo de d módulo phi utilizando el algoritmo de Euclides extendido.
 * 
 * @param d - El número del cual se quiere calcular el inverso multiplicativo módulo phi.
 * @param phi - El módulo para el cual se quiere calcular el inverso multiplicativo.
 * @return long long El valor del inverso multiplicativo de d módulo phi, o -1 si no existe.
 */
long long euclidesExtend(long long d, long long phi) {
    std::vector<long long> xi = {phi, d};
    std::vector<long long> zi = {0, 1};
    
    while (xi.back() > 1) {
        size_t last = xi.size() - 1;
        long long quotient = xi[last - 1] / xi[last];
        
        long long new_zi = (zi[zi.size() - 2] - quotient * zi.back()) % phi;
        if (new_zi < 0) new_zi += phi;
        zi.push_back(new_zi);

        long long new_xi = xi[last - 1] % xi[last];
        xi.push_back(new_xi);
    }

    if (xi.back() != 1) {
        return -1;
    }
    return zi.back();
}

/**
 * @brief Función para convertir un texto en bloques numéricos.
 * 
 * @param text - Cadena de texto a convertir. Se rellena con 'X' si es necesario.
 * @param value - Tamaño de cada bloque.
 * @return std::vector<long long> Vector de bloques.
 */
std::vector<long long> textToBlocks(std::string& text, int value) {
    std::vector<long long> blocks;

    while (text.size() % value != 0) {
        text += 'X';
    }

    for (size_t i = 0; i < text.length(); i += value) {
        long long block = 0;
        for (size_t j = i; j < i + value; j++) {
            int letter_value = std::toupper(text[j]) - 'A';

            if (letter_value < 0 || letter_value > 25) {
                return {};
            }
            
            long long power = 1;
            for (size_t k = 0; k < (size_t)(value - (j - i) - 1); k++) power *= 26;
            block += (long long)letter_value * power;
        } 
        blocks.push_back(block);
    }
    return blocks;
}

/**
 * @brief Función para convertir bloques de números en texto.
 * 
 * @param blocks - Vector de bloques numéricos.
 * @param block_size - Tamaño de cada bloque.
 * @return std::string El texto resultante en mayúsculas.
 */
std::string blocksToText(std::vector<long long>& blocks, int block_size) {
    std::string text;
    for (long long block : blocks) {
        std::string block_text = "";
        long long temp_block = block;
        for (int i = 0; i < block_size; i++) {
            int letter_value = temp_block % 26;
            char letter = 'A' + letter_value;
            block_text = letter + block_text;
            temp_block /= 26;
        }
        text += block_text;
    }
    return text;
}