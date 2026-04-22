#include "./utils/utils.h"
#include <string>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <algorithm>

int main() {
  std::string text;
  long long p, q, d;

  std::cout << "----- PRÁCTICA 10. RSA -----" << std::endl;
  std::cout << "Introduzca el texto original: ";
  std::getline(std::cin, text);
  std::cout << std::endl;
  std::cout << "Introduzca el número primo p: ";
  std::cin >> p;
  std::cout << "Introduzca el número primo q: ";
  std::cin >> q;
  std::cout << "Introduzca el valor de d: ";
  std::cin >> d;
  std::cout << std::endl;

  const long long n = p * q;
  const long long phi = (p - 1) * (q - 1);

  if (isPrime(p) && isPrime(q)) {
    std::cout << "PASO 1: Se comprueba que p y q son primos..." << std::endl;
  } else {
    std::cerr << "Error: p o q no son primos." << std::endl;
    return -1;
  }

  if (std::gcd(d, phi) == 1) {
    std::cout << "PASO 2: Se comprueba que d es primo con phi(n)=" << phi << "..." << std::endl; 
  } else {
    std::cerr << "Error: d no es primo con phi(n)." << std::endl;
    return -1;
  }

  const long long e = modularMultiplicativeInverse(d, phi);
  std::cout << "PASO 3: Se calculca el valor de e=" << e << "..." << std::endl;

  //Eliminamos los expacios del mensaje
  text.erase(std::remove(text.begin(), text.end(), ' '), text.end());

  int block_sz = 0;
  long long capacity = 1;

  while (capacity * 26 < n) {
      capacity *= 26;
      block_sz++;
  }

  if (block_sz == 0) block_sz = 1;

  std::cout << "PASO 4: Como n=" << n << ", se divide el texto en bloques de " << block_sz << " caracteres..." << std::endl;

  while (text.length() % block_sz != 0) {
        text += 'X'; 
  }

  std::vector<long long> m_values;
  std::vector<long long> c_values;

  for (size_t i = 0; i < text.length(); i += block_sz) {
    long long m_value = 0;
    for (int j = 0; j < block_sz; j++) {
      m_value = (m_value * 26) + charToInt(text[i + j]);
    }
    m_values.push_back(m_value);
    long long c_value = binaryExponentiation(m_value, e, n);
    c_values.push_back(c_value);
  }

  std::cout << "\nPASO 5: Se pasa cada bloque a decimal para poder cifrar, obteniendo ";
  for (size_t i = 0; i < m_values.size(); ++i) {
    std::cout << m_values[i] << (i == m_values.size() - 1 ? "" : ", ");
  }
  std::cout << std::endl;

  std::cout << "PASO 6: Se calcula en decimal el texto cifrado: ";
  for (size_t i = 0; i < c_values.size(); ++i) {
    int digits = std::to_string(n).length();
    std::cout << std::setfill('0') << std::setw(digits) << c_values[i] 
              << (i == c_values.size() - 1 ? "" : ", ");
  }
  std::cout << std::endl;
}