#include "./generator.h"

int main() {
  int id;
  int size;

  std::cout << "--------------GENERADOR C/A DE GPS--------------" << std::endl;
  std::cout << "Ingrese el ID del satélite para generar su secuencia C/A: ";
  std::cin >> id;
  std::cout << std::endl;
  std::cout << "Ingrese la longitud de la secuencia de salida: ";
  std::cin >> size;
  std::cout << std::endl;

  CA generator;

  std::cout << "LFSR1         retroalimentación | LFSR2         retroalimentación | Secuencia C/A PRN1" << std::endl;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl;
  generator.generate(id, size);
  return 0;
}