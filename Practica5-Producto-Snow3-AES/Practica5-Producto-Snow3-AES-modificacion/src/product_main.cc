#include "./product.h"

int main() {
  std::string selection;
  bool is_aes = false;
  unsigned char first_byte;
  unsigned char second_byte;

  std::cout << "-----------------MULTIPLICACIÓN EN SNOW 3G Y AES-----------------" << std::endl;
  std::cout << "¿Qué algoritmo selecciona?" << std::endl;
  std::cout << "-(AES/Snow3): ";
  std::cin >> selection;
  std::cout << std::endl;

  if (selection == "AES") {
    is_aes = true;
  } else if (selection == "Snow3") {
    is_aes = false;
  } else {
    std::cout << "Opcion introducida incorrecta" << std::endl;
    return 0;
  }

  Product p(is_aes);

  unsigned int temp;
  std::cout << "Introduzca el primer byte (2 digitos): ";
  std::cin >> std::hex >> temp;
  std::cout << std::endl;
  first_byte = static_cast<unsigned int>(temp);

  std::cout << "Introduzca el segundo byte (2 digitos): ";
  std::cin >> std::hex >> temp;
  std::cout << std::endl;
  second_byte = static_cast<unsigned int>(temp);

  p.operation(first_byte, second_byte);
  std::cout << "Primer byte: " << p.getFirstByte() << ", en hexadecimal: " << std::hex << p.getFirstByte().to_ulong() << std::endl;
  std::cout << "Segundo byte: " << p.getSecondByte() << ", en hexadecimal: " << std::hex << p.getSecondByte().to_ulong() << std::endl;
  std::cout << "Byte del algoritmo: " << p.getConstByte() << ", en hexadecimal: " << std::hex << p.getConstByte().to_ulong() << std::endl;
  std::cout << "Resultado de la multiplicación: " << p.getResult() << ", en hexadecimal: " << std::hex << p.getResult().to_ulong() << std::endl;

  return 0;
}