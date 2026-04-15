#include "diffie_hellman.h"

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

int main() {
  long long prime, alpha, secret_a, secret_b;
  std::cout << "--- PRÁCTICA 8. ALGORITMO DIFFIE-HELLMAN ---" << std::endl;
  std::cout << "Introduzca un número primo (p): ";
  std::cin >> prime;
  if (!isPrime(prime)) {
    std::cerr << "\nError: El numeró introducido no es primo." << std::endl;
    return -1;
  }
  std::cout << "\nIntroduzca el número α<p: ";
  std::cin >> alpha;
  if (alpha >= prime) {
    std::cerr << "\nError: El numeró introducido no es menor al número primo." << std::endl;
    return -1;    
  }
  std::cout << "\nIntroduzca el secreto A: ";
  std::cin >> secret_a;
  std::cout << "\nIntroduzca el secreto B: ";
  std::cin >> secret_b;

  DiffieHellman df(prime, alpha, secret_a, secret_b);

  std::cout << "xA = " << secret_a << std::endl;
  std::cout << "xB = " << secret_b << std::endl;
  std::cout << "p = " << prime << std::endl;
  df.generateKey();
  return 0;
}