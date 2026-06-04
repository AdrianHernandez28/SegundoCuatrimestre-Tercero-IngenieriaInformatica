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

std::vector<int> randomIndexGenerator(long long p, int num) {
  std::vector<int> posibilities = {};
  for (int i = 1; i < p; i++) {
    posibilities.push_back(i);
  }
  std::vector<int> results = {};
  std::random_device rd;
  std::mt19937 gen(rd());
  std::sample(posibilities.begin(), posibilities.end(),
              std::back_inserter(results), num, gen);

  std::cout << "Indices generados: ";
  for (int i = 0; i < num; i++) {
    int aux = results[i];
    if (i == num - 1) {
     std::cout << aux << ", ";
    } else {
      std::cout << aux << ", ";
    }
  }
  std::cout << std::endl;
  return results;
}

long long binaryExponentiation(long long alpha, long long exponent, long long prime) {
  long long x = 1;
  alpha %= prime;
  while (exponent != 0) {
    if (exponent % 2 == 0) {
      alpha = (alpha * alpha) % prime; 
    } else {
      x = (x * alpha) % prime;
      alpha = (alpha * alpha) % prime; 
    }
    exponent /= 2;
  }
  return x;
}

bool isNotValid(long long alpha, long long prime, std::vector<int>& index_collection) {
  std::vector<int> results = {};
  std::set<int> unique_elements;
  std::cout << "Resultados generados: ";

  for (int i = 0; i < index_collection.size(); i++) {
    long long aux = binaryExponentiation(alpha, index_collection[i], prime);
    results.push_back(aux);
    unique_elements.insert(aux);
    if (i == index_collection.size() - 1) {
      std::cout << aux << ", ";
    } else {
      std::cout << aux << ", ";
    }
  }
  std::cout << std::endl;
  return results.size() == unique_elements.size() ? false : true;
}

int main() {
  long long prime, alpha, secret_a, secret_b, rand_numbers;
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

  std::cout << "\nIntroduzca el numero de numeros aleatorios para comprobar si el generador es valido (debe ser menor que " << prime << "): ";
  std::cin >> rand_numbers;
  if (rand_numbers > prime) {
    std::cerr << "\nError: El numeró introducido no es menor al número primo." << std::endl;
    return -1;    
  }
  std::vector<int> index_collection = randomIndexGenerator(prime, rand_numbers);
  if (isNotValid(alpha, prime, index_collection)) {
    std::cout << "\nEl generador no es valido" << std::endl; 
  }

  std::cout << "\nIntroduzca el secreto A: ";
  std::cin >> secret_a;
  std::cout << "\nIntroduzca el secreto B: ";
  std::cin >> secret_b;

  DiffieHellman df(prime, alpha, secret_a, secret_b);

  std::cout << "\nxA = " << secret_a << std::endl;
  std::cout << "xB = " << secret_b << std::endl;
  std::cout << "p = " << prime << std::endl;
  df.generateKey();
  return 0;
}