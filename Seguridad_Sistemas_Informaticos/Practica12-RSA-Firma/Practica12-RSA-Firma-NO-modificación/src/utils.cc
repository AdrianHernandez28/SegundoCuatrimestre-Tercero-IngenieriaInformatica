#include "utils.h"

/**
 * @brief Método para elevar una base a una potencia módulo un número, utilizando el método de exponenciación rápida. 
 * @param base - La base que se desea elevar a una potencia.
 * @param exp - La potencia a la que se desea elevar la base.
 * @param mod - El número módulo el cual se desea calcular la potencia.
 * @return long long El resultado de (base^exp) % mod, calculado de manera eficiente utilizando la exponenciación rápida.
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
 * @return false Sin o es primo
 */
bool testLehmanPeralta(long long p) {
    if ( p == 2 || p == 3 || p == 5 || p == 7 || p == 11) return true;
    else if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0 || p % 11 == 0) return false;
    else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::cout << std::setw(3) << "i" << std::setw(15) << "a" << std::setw(15) << "r" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        for (int i = 1; i <= 10; i++) {
            std::uniform_int_distribution<long long> dis(2, p-2);
            long long a = dis(gen);
            long long r = modExp(a, (p-1)/2, p);
            
            std::cout << std::setw(3) << i << std::setw(15) << a << std::setw(15) << r << std::endl;
            if (r != 1 && r != p-1) {
                std::cout << std::endl;
                return false;
            }
        }   
    }
    std::cout << std::endl;
    return true;
}

/**
 * @brief Función para calcular el inverso multiplicativo de d módulo phi utilizando el algoritmo de Euclides extendido. Este valor se utiliza como la 
 * clave pública e en RSA.
 * 
 * @param d - El número del cual se quiere calcular el inverso multiplicativo módulo phi. En RSA, este valor es la clave privada.
 * @param phi - El módulo para el cual se quiere calcular el inverso multiplicativo. En RSA, este valor es phi(n) = (p-1)(q-1).
 * @return long long El valor del inverso multiplicativo de d módulo phi, que se utiliza como la clave pública e en RSA.
 */
long long euclidesExtend(long long d, long long phi) {
    int i = 0;
    std::vector<long long> xi = {phi};
    std::vector<long long> zi = {0, 1};
    
    std::cout << std::setw(3) << "i" << std::setw(8) << "xi" << std::setw(8) << "zi" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << std::setw(3) << i << std::setw(8) << xi[0] << std::setw(8) << zi[1] << std::endl;

    i++;
    xi.push_back(d);

    while (xi[xi.size() -1] > 1) {
        long long new_zi = -(xi[xi.size() -2] / xi[xi.size() -1])* zi[zi.size()-1] + zi[zi.size()-2];
        new_zi = (new_zi % phi + phi) % phi;
        zi.push_back(new_zi);

        long long new_xi = xi[xi.size()-1];

        std::cout << std::setw(3) << i << std::setw(8) << new_xi << std::setw(8) << new_zi << std::endl;

        new_xi = xi[xi.size()-2]% xi[xi.size()-1];
        xi.push_back(new_xi);
        i++;    
    }
    if (xi[zi.size() -1] != 1) {
        std::cout << "No existe el inverso multiplicativo, d no es coprimo con phi" << std::endl;
        return -1;
    }
    return zi[zi.size() -1];
}

/**
 * @brief Función para convertir un texto en bloques numéricos, asumiendo que cada letra del alfabeto inglés (a-z, A-Z) se representa como un número del 
 * 0 al 25 (0 = 'a', 1 = 'b', ..., 25 = 'z') y que cada bloque representa un número en base 26. El tamaño de cada bloque se determina por el parámetro "value", 
 * que indica cuántas letras representa cada bloque. Si el texto no es múltiplo del tamaño del bloque, se rellena con 'X' hasta completar el último bloque.
 * 
 * @param text - Cadena de texto a convertir en bloques numéricos. Se modificará si es necesario para rellenar con 'X'.
 * @param value - Tamaño de cada bloque, es decir, cuántas letras representa cada bloque.
 * @return std::vector<long long> Vector de bloques
 */
std::vector<long long> textToBlocks(std::string& text, int value) {
    std::vector<long long> blocks;

     while (text.size() % value != 0) {
        text += 'X';
    }

    for (size_t i = 0; i < text.length(); i+=value) {
        long long block = 0;
        for (size_t j = i; j < i + value; j++) {
            int letter_value = std::toupper(text[j]) - 'A';

            if (letter_value < 0 || letter_value > 25) {
                std::cerr << "Error: El texto solo puede contener letras del alfabeto inglés (a-z, A-Z)." << std::endl;
                return {};
            }
            long long power = 1;
            for (size_t k = 0; k < value - (j - i) - 1; k++) power *= 26;
            long long val = letter_value * power;
            block += val;
        } 
        blocks.push_back(block);
    }
    return blocks;
}

/**
 * @brief Función para convertir bloques de números en texto, asumiendo que cada bloque representa un número en base 26 donde cada dígito corresponde a una letra 
 * del alfabeto inglés (0 = 'a', 1 = 'b', ..., 25 = 'z').
 * 
 * @param blocks - Vector de bloques numéricos a convertir.
 * @param block_size - Tamaño de cada bloque, es decir, cuántas letras representa cada bloque.
 * @return std::string El texto resultante.
 */
std::string blocksToText(std::vector<long long>& blocks, int block_size) {
    std::string text;
    for (long long block : blocks) {
        std::string block_text;
        for (int i = 0; i < block_size; i++) {
            int letter_value = block % 26;
            char letter = 'A' + letter_value;
            block_text = letter + block_text;
            block /= 26;
        }
        text += block_text;
    }
    return text;
}