#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

int main() {
    std::cout << "-------- PROTOCOLO DE FIRMA RSA --------" << std::endl;
    std::cout << "\n1. Firmar (Generar firma)\n2. Verificar (Validar firma)" << std::endl;
    std::cout << "\nSeleccione una opcion: ";
    int opcion;
    std::cin >> opcion;
    std::cin.ignore(); // Limpiar el buffer

    if (opcion == 1) {
        std::string text;
        long long p, q, e_public;

        std::cout << "Inserte el texto original a firmar: ";
        std::getline(std::cin >> std::ws, text); 

        std::cout << "Inserte p: "; std::cin >> p;
        std::cout << "Inserte q: "; std::cin >> q;
        std::cout << "Inserte e (exponente publico de A): "; std::cin >> e_public;

        std::cout << "\n === verificacion de p ===" << std::endl;
        if (!testLehmanPeralta(p)) { std::cerr << "Error: p no es primo." << std::endl; return -1; }
        
        std::cout << "\n === verificacion de q ===" << std::endl;
        if (!testLehmanPeralta(q)) { std::cerr << "Error: q no es primo." << std::endl; return -1; }

        long long n = p * q;
        long long phi = (p - 1) * (q - 1);
        
        std::cout << "\n === verificacion de que e es coprimo con phi(n) ===" << std::endl;
        long long d_private = euclidesExtend(e_public, phi);
        if (d_private == -1) { std::cerr << "Error: e no es coprimo con phi(n)." << std::endl; return -1; }

        int block_size = 0;
        while (std::pow(26, block_size + 1) < n) block_size++;

        text.erase(std::remove(text.begin(), text.end(), ' '), text.end());

        std::vector<long long> msg_blocks = textToBlocks(text, block_size);

        if (msg_blocks.empty()) return -1;

        // 6. Cálculo de la firma S = M^d mod n para cada bloque M

        std::cout << "Clave privada calculada (d): " << d_private << std::endl;
        std::cout << "n = " << n << std::endl;
        std::cout << "Tamaño de bloque: " << block_size << std::endl;
        std::cout << "\nBloques del mensaje (decimal): ";

        for (long long m : msg_blocks) std::cout << m << " ";

        std::cout << "\n\nTEXTO FIRMADO (S = M^d mod n):";

        for (size_t i = 0; i < msg_blocks.size(); i++) {
            std::cout << modExp(msg_blocks[i], d_private, n) << " ";
        }

        std::cout << std::endl; 

    } else if (opcion == 2) {
        std::string firma_str;
        long long n, e_public;

        std::cout << "Inserte los bloques de la firma (separados por espacios): ";
        std::getline(std::cin >> std::ws, firma_str);

        std::cout << "Inserte n: "; std::cin >> n;
        std::cout << "Inserte e (exponente publico del emisor): "; std::cin >> e_public;

        std::vector<long long> signature_blocks;
        std::stringstream ss(firma_str);
        long long temp;
        while (ss >> temp) signature_blocks.push_back(temp);

        int block_size = 0;
        while (std::pow(26, block_size + 1) < n) block_size++;

        std::cout << "\n=== Verificando Firma (M = S^e mod n) ===" << std::endl;
        std::vector<long long> recovered_decimal_blocks;
        for (long long s : signature_blocks) {
            recovered_decimal_blocks.push_back(modExp(s, e_public, n));
        }

        std::cout << "Bloques recuperados (decimal): ";
        for (long long m : recovered_decimal_blocks) std::cout << m << " ";

        std::string original_text = blocksToText(recovered_decimal_blocks, block_size);
        std::cout << "\n\nTEXTO ORIGINAL RECUPERADO: " << original_text << std::endl;

    } else {
        std::cout << "Opción no reconocida." << std::endl;
    }

    return 0;
}