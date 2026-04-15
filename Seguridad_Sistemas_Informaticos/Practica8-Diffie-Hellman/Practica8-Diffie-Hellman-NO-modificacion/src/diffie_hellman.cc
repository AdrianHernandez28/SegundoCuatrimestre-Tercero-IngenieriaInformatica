#include "diffie_hellman.h"

DiffieHellman::DiffieHellman(long long prime, long long alpha, long long secret_a, long long secret_b) {
  prime_ = prime;
  alpha_ = alpha;
  secret_a_ = secret_a;
  secret_b_ = secret_b;
}

void DiffieHellman::generateKey() {
  long long y_a = binaryExponentiation(alpha_, secret_a_);
  long long y_b = binaryExponentiation(alpha_, secret_b_);
  std::cout << "yA = " << y_a << std::endl;
  std::cout << "yB = " << y_b << std::endl;
  key_ = binaryExponentiation(y_a, secret_b_);
  std::cout << "key = " << key_ << std::endl;

}

long long DiffieHellman::binaryExponentiation(long long alpha, long long exponent) {
  long long x = 1;
  alpha %= prime_;

  while (exponent != 0) {
    if (exponent % 2 == 0) {
      alpha = (alpha * alpha) % prime_; 
    } else {
      x = (x * alpha) % prime_;
      alpha = (alpha * alpha) % prime_; 
    }
    exponent /= 2;
  }
  return x;
}