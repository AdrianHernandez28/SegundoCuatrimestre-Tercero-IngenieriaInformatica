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

long long modularMultiplicativeInverse(long long value, long long module) {
  long long x, y;
  long long mcd = extendedEuclides(value, module, x, y);
  if (mcd != 1) return -1;
  return (x % module + module) % module;
}

long long modularExponentiation(long long alpha, long long exponent, long long module) {
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

long long extendedEuclides(long long a, long long b, long long &x, long long &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  long long x1, y1;
  long long mcd = extendedEuclides(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return mcd;
}

long long calculateLambda(long long p, long long q) {
  long long product = (p - 1) * (q - 1);
  long long x, y;
  long long mcd = extendedEuclides(p-1, q-1, x, y);
  if (mcd == 0) return -1;
  return product / mcd;
}