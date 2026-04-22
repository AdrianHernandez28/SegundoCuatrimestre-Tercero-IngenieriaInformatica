#include "utils.h"

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

long long modularMultiplicativeInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;

    // Si el módulo es 1, no hay inverso
    if (m == 1) return 0;

    while (a > 1) {
        // Si a es 0, el MCD no es 1, por lo que no hay inverso
        if (m == 0) return -1; 

        // q es el cociente
        long long q = a / m;
        long long t = m;

        // m es el resto ahora, proceso estándar de Euclides
        m = a % m;
        a = t;
        t = y;

        // Actualizamos x e y (coeficientes de Bézout)
        y = x - q * y;
        x = t;
    }

    // Aseguramos que x sea positivo
    if (x < 0) x += m0;

    return x;
}

long long binaryExponentiation(long long alpha, long long exponent, long long module) {
  long long x = 1;
  alpha %= module;

  while (exponent != 0) {
    if (exponent % 2 == 0) {
      alpha = (alpha * alpha) % module; 
    } else {
      x = (x * alpha) % module;
      alpha = (alpha * alpha) % module; 
    }
    exponent /= 2;
  }
  return x;
}

int charToInt(char c) {
    if (c == ' ') return 26; 
    return toupper(c) - 'A';
}