#include "./generator.h"

int main() {
  int size;

  std::cout << "--------------GENERADOR C/A DE GPS MODIFICACIÓN--------------" << std::endl;
  std::cout << std::endl;
  std::cout << "Ingrese la longitud de la secuencia de salida: ";
  std::cin >> size;
  std::cout << std::endl;

  CA generator;

  std::cout << "LFSR1         retroalimentación | LFSR2         retroalimentación | Secuencia C/A PRN1" << std::endl;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl;
  generator.generate(size);
  return 0;
}