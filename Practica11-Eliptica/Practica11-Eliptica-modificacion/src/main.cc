#include <iostream>
#include "utils.h"

int main() {
    int p, a, b, dA, dB, m, M;
    Punto G;
    std::cout << "=== Cifrado Elíptico ===\n";
    std::cout << "\nIngrese los parámetros de la curva y los datos necesarios:\n";

    std::cout << "\np = "; std::cin >> p;
    std::cout << "a = "; std::cin >> a;
    std::cout << "b = "; std::cin >> b;
    std::cout << "G (x y) = "; std::cin >> G.x >> G.y;
    std::cout << "dA = "; std::cin >> dA;
    std::cout << "dB = "; std::cin >> dB;
    std::cout << "Mensaje m = "; std::cin >> m;
    std::cout << "M = "; std::cin >> M;

    std::cout << "\n--- Resultados ---\n";
    std::cout << "\nCurva: y^2 = x^3 + " << a << "x + " << b << " mod " << p << "\n";
    
    // 1. Puntos de la curva
    std::cout << "\nPuntos de la curva: ";
    for (int x = 0; x < p; x++) {
        int function_value = pow(x, 3) + a*x + b;
        int target = modulo(function_value, p);
        for (int y = 0; y < p; y++) {
            if (modulo(pow(y, 2), p) == target) std::cout << "(" << x << "," << y << ") ";
        }
    }

    // 2. Claves Públicas
    Punto dBG = multiplicarPunto(G, dB, a, p);
    Punto dAG = multiplicarPunto(G, dA, a, p);

    // 3. Secreto Compartido
    Punto S = multiplicarPunto(dBG, dA, a, p);

    // 4. Codificación del Mensaje (Paso de M y h)
    int h = p / M; 
    Punto Qm = {0, 0, true};
    for (int j = 0; j < h; j++) {
        int x_candidato = m * h + j;
        int value = pow(x_candidato, 3) + a * x_candidato + b;
        value = modulo(value, p);

        for (int y = 0; y < p; y++) {
            if (modulo(pow(y, 2), p) == value) {
                Qm = {x_candidato, y, false};
                break;
            }
        }
        if (!Qm.infinito) break;
    }

    // 5. Cifrado
    Punto C1 = sumarPuntos(Qm, S, a, p);

    // Salidas exactamente como el ejemplo
    std::cout << "\n\nClave publica de B: (" << dBG.x << "," << dBG.y << ")";
    std::cout << "\nClave publica de A: (" << dAG.x << "," << dAG.y << ")";
    std::cout << "\nClave secreta compartida: (" << S.x << "," << S.y << ")";
    std::cout << "\nMensaje codificado Qm: (" << Qm.x << "," << Qm.y << ")";
    std::cout << "\nCifrado {Qm+dA*dBG, dAG}: {(" << C1.x << "," << C1.y << "), (" << dAG.x << "," << dAG.y << ")}\n";

    std::cout << "\n¿Quieres descifrar el mensaje? (s/n): ";
    char respuesta;
    std::cin >> respuesta;
    if (respuesta == 's' || respuesta == 'S') {
        Punto Qm = descifrado(C1, dAG, dB, a, p);
        std::cout << "\nParte entera del mensaje m: " << Qm.x / h << "\n";
        std::cout << "Mensaje descifrado Qm: (" << Qm.x << "," << Qm.y << ")\n";
    }

    return 0;
}