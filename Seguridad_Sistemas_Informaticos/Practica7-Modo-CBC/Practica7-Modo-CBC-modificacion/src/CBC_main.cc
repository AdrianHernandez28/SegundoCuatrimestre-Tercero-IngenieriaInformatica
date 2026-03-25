#include "./CBC.h"

int main() {
  std::array<uint8_t, 16> key, iv, block1, block2;
  std::string str_key, str_iv, str_b1, str_b2;

  //Pedimos los datos
  std::cout << "Clave: ";
  std::getline(std::cin, str_key);

  std::cout << "IV: ";
  std::getline(std::cin, str_iv);

  std::cout << "Bloque 1 Original: ";
  std::getline(std::cin, str_b1);

  std::cout << "Bloque 2 Original: ";
  std::getline(std::cin, str_b2);

  //Quitamos espacios
  str_key.erase(std::remove(str_key.begin(), str_key.end(), ' '), str_key.end());
  str_iv.erase(std::remove(str_iv.begin(), str_iv.end(), ' '), str_iv.end());
  str_b1.erase(std::remove(str_b1.begin(), str_b1.end(), ' '), str_b1.end());
  str_b2.erase(std::remove(str_b2.begin(), str_b2.end(), ' '), str_b2.end());

  //Comprobamos longituf
  if (str_key.length() != 32) {
    std::cout << "Error: La clave no tiene 16 bytes (32 caracteres)." << std::endl;
    return 1; 
  }
  if (str_iv.length() != 32) {
    std::cout << "Error: El IV no tiene 16 bytes (32 caracteres)." << std::endl;
    return 1; 
  }
  if (str_b1.length() != 32) {
    std::cout << "Error: El Bloque 1 no tiene 16 bytes (32 caracteres)." << std::endl;
    return 1; 
  }
  if (str_b2.length() != 32) {
    std::cout << "Error: El Bloque 2 no tiene 16 bytes (32 caracteres)." << std::endl;
    return 1; 
  }

  //Conversion de tipos a array
  int i = 0, j = 0;
  while (i < 16) {
    key[i] = static_cast<uint8_t>(std::stoi((str_key.substr(j, 2)), nullptr, 16));
    iv[i] = static_cast<uint8_t>(std::stoi((str_iv.substr(j, 2)), nullptr, 16));
    block1[i] = static_cast<uint8_t>(std::stoi((str_b1.substr(j, 2)), nullptr, 16));
    block2[i] = static_cast<uint8_t>(std::stoi((str_b2.substr(j, 2)), nullptr, 16));
    i++;
    j += 2;
  }

  std::cout << "\n--- RESULTADOS ---" << std::endl;

  //Hacemos el XOR con el Bloque 1 y el IV
  for (int x = 0; x < 16; x++) {
    block1[x] ^= iv[x]; 
  }

  CBC cbc1(key, block1);
  cbc1.encrypt();
  
  std::cout << "Bloque 1 de Texto Cifrado: ";
  cbc1.printState();
  std::cout << std::endl;

  std::array<uint8_t, 16> cipher1 = cbc1.getResult();

  for (int x = 0; x < 16; x++) {
    block2[x] ^= cipher1[x]; 
  }

  CBC cbc2(key, block2);
  cbc2.encrypt();

  std::cout << "Bloque 2 de Texto Cifrado: ";
  cbc2.printState();
  std::cout << std::endl;

  return 0;
}