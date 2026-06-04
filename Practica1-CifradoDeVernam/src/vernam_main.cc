#include "vernam.h"

int main() {
   std::string message;
   std::cout << "Introduce el mensaje real: ";
   std::cin >> message;
   Vernam obj(message); 
   std::cout << "Mensaje real en binario: " << obj.getBinaryMessage() << std::endl;
   std::cout << "Longitud del numero en binario: " << obj.getBinSize() << std::endl;
   std::cout << "¿Desea introducir la clave manualmente o una clave aleatoria?:" << std::endl;
   std::cout << "1. Manual." << std::endl;
   std::cout << "2. Aleatoria." << std::endl;
   int option;
   std::string key;
   std::cin >> option;
   switch (option) {
    case 1:
      obj.ToManualFlag();
      std::cout << "Introduzca una clave de " << obj.getBinSize() << " dígitos (0 ó 1)." << std::endl;
      std::cin >> key;
      obj.setRandomKey(key);
      break;
    case 2:
      break;
    default:
      std::cout << "Opcion introducida incorrecta." << std::endl;
      break;
   }
   obj.Code();
   if (obj.getFlag()) {
    std::cout << "Clave manual: " << obj.getRandomKey() << std::endl;
   } else {
    std::cout << "Clave aleatoria: " << obj.getRandomKey() << std::endl;
   }
   std::cout << "Mensaje cifrado en binario: " << obj.getBinaryKey() << std::endl;
   std::cout << "Mensaje cifrado: " << obj.getKey() << std::endl;   

   Vernam descifrado(obj.getKey());
   std::string same_key = obj.getRandomKey();
   descifrado.ToManualFlag();
   descifrado.setRandomKey(same_key);
   descifrado.Code();

   std::cout << "\nDescifrando " << obj.getKey() << " ..." << std::endl;
   std::cout << "Mensaje descifrado: " << descifrado.getKey() << std::endl;
  return 0;
}
