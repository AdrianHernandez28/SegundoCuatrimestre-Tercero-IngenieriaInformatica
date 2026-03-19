#include "./AES.h"

int main() {
  std::array<uint8_t, 16> key;
  std::array<uint8_t, 16> original_text;
  std::string str_key;
  std::string str_text;

  std::cout << "Introduzca una clave (16 bytes en hexadecimal): ";
  std::getline(std::cin, str_key);

  std::cout << "\nIntroduzca un bloque de texto original (16 bytes en hexadecimal): ";
  std::getline(std::cin, str_text);
  std::cout << std::endl;

  //Comprobamos que la clave y el texto original tengan el tamaño adecuado
  str_key.erase(std::remove(str_key.begin(), str_key.end(), ' '), str_key.end());
  str_text.erase(std::remove(str_text.begin(), str_text.end(), ' '), str_text.end());
  
  if (str_key.length() != 32) {
    std::cout << "Error: La clave introducida no tiene 16 bytes (32 caracteres)." << std::endl;
    return 1; 
  }
  if (str_text.length() != 32) {
    std::cout << "Error: El texto introducido no tiene 16 bytes (32 caracteres)." << std::endl;
    return 1; 
  }

  //Comprobamos que todos los caracteres sean válidos
  for (char c : str_key) {
    if (!std::isxdigit(c)) {
      std::cout << "Error: Caracter invalido detectado ('" << c << "'). Solo se permiten caracteres hexadecimales (0-9, A-F)." << std::endl;
      return 1; 
    }
  }
  for (char c : str_text) {
    if (!std::isxdigit(c)) {
      std::cout << "Error: Caracter invalido detectado ('" << c << "'). Solo se permiten caracteres hexadecimales (0-9, A-F)." << std::endl;
      return 1; 
    }
  }

  //Introducimos los datos en el tipo de dato correcto
  int i = 0;
  int j = 0;
  while (i < 16) {
    key[i] = static_cast<uint8_t>(std::stoi((str_key.substr(j, 2)), nullptr, 16));
    original_text[i] = static_cast<uint8_t>(std::stoi((str_text.substr(j, 2)), nullptr, 16));
    i++;
    j += 2;
  }

  AES rijndael(key, original_text);
  rijndael.encrypt();
  std::cout << "Bloque de texto cifrado: ";
  rijndael.printState();
  std::cout << std::endl;
  return 0;
}