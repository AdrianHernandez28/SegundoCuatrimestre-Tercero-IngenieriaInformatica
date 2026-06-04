#include "utils.h"

/**
 * @brief Función para calcular el módulo de a con respecto a p, asegurando que el resultado sea siempre positivo. Si el resultado de a % p es negativo, 
 * se le suma p para obtener un resultado positivo.
 * 
 * @param a - El número del cual se quiere calcular el módulo.
 * @param p -  El módulo.
 * @return int El resultado del módulo de a con respecto a p, siempre positivo.
 */
int modulo(int a, int p) {
    int r = a % p;
    return r < 0 ? r + p : r;
}

/**
 * @brief Función para calcular el inverso multiplicativo de a módulo m. Hace un bucle desde 1 hasta m-1 para encontrar un número x tal que (a * x) % m == 1. 
 * Si no se encuentra tal número, devuelve -1.
 * 
 * @param a - El número del cual se quiere encontrar el inverso multiplicativo.
 * @param m - El módulo.
 * @return int EL inverso multiplicativo de a módulo m, o -1 si no existe.
 */
int modInverse(int a, int m) {
    a = modulo(a, m);
    for (int x = 1; x < m; x++) {
        if (modulo(a * x, m) == 1) return x;
    }
    return -1;
}

// Suma y Doblado de puntos en la curva y^2 = x^3 + ax + b
Punto sumarPuntos(Punto P, Punto Q, int a, int p) {

    //Casos especiales
    if (P.infinito) return Q;
    if (Q.infinito) return P;

    int lambda;

    //CASO 1: P == Q
    if (P.x == Q.x && P.y == Q.y) {

        int numerador = modulo(3 * P.x * P.x + a, p);
        int denominador = modulo(2 * P.y, p);
        int inverso = modInverse(denominador, p);

        if (inverso == -1) return {0, 0, true}; // No hay inverso, punto en el infinito
        
        lambda = modulo(numerador * inverso, p);

    } 
    
    //CASO 2: P != Q
    else {
        if (P.x == Q.x) return {0, 0, true}; // P + (-P) = Infinito

        int numerador = modulo(Q.y - P.y, p);
        int denominador = modulo(Q.x - P.x, p);
        int inverso = modInverse(denominador, p);

        if (inverso == -1) return {0, 0, true}; // No hay inverso, punto en el infinito

        lambda = modulo(numerador * inverso, p);
    }

    //CALCULO DEL PUNTO RESULTANTE R = P + Q

    int x3 = modulo(lambda * lambda - P.x - Q.x, p);
    int y3 = modulo(lambda * (P.x - x3) - P.y, p);
    
    return {x3, y3, false};
}

// Multiplicación escalar
Punto multiplicarPunto(Punto G, int d, int a, int p) {
    Punto resultado = {0, 0, true};
    Punto potenciaActual = G;

    while (d > 0) {
        // Si el bit actual de d es 1, sumamos potenciaActual al resultado
        if (d % 2 == 1) resultado = sumarPuntos(resultado, potenciaActual, a, p);

        // Doblamos potenciaActual para el siguiente bit
        potenciaActual = sumarPuntos(potenciaActual, potenciaActual, a, p);
        
        // Avanzamos al siguiente bit de d
        d /= 2;
    }
    return resultado;
}

Punto negarPunto(Punto P, int p) {
    if (P.infinito) return P; 
    return {P.x, modulo(-P.y, p), false}; 
}

Punto descifrado(Punto C1, Punto C2, int dB, int a, int p) {
    Punto secreto_compartido = multiplicarPunto(C2, dB, a, p);
    Punto secreto_negativo = negarPunto(secreto_compartido, p);
    Punto Qm_descifrado = sumarPuntos(secreto_negativo, C1, a, p);
    return Qm_descifrado;
}
