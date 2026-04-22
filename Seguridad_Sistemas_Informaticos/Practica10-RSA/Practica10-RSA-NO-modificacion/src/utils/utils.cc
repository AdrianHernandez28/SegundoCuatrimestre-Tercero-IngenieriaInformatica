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
    long long original_module = module;
    
    long long auxiliary_inverse = 0;
    long long inverse = 1;

    if (module == 1) return 0;

    while (value > 1) {
        if (module == 0) return -1; 

        long long quotient = value / module;
        
        long long temp_module = module;
        module = value % module;
        value = temp_module;

        long long temp_inverse = auxiliary_inverse;
        auxiliary_inverse = inverse - quotient * auxiliary_inverse;
        inverse = temp_inverse;
    }

    if (inverse < 0) {
        inverse += original_module;
    }

    return inverse;
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