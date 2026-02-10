#include "vigenere.h"

int main() {
  std::string key;
  char x;
  std::string word;
  int option;

  std::cout << "¿Que desea hacer?:" << std::endl;
  std::cout << "1. cifrar." << std::endl;
  std::cout << "2. descifrar." << std::endl;
  std::cin >> option;
  std::cout << "Introduzca una palabra clave: ";
  std::cin >> key;

  switch (option) {
    case 1:     
      std::cout << "\nIntroduzca el texto que quiere cifrar: ";
    break;
    case 2:
      std::cout << "\nIntroduzca el texto que quiere descifrar: ";
    break;
    default:
      std::cerr << "Ha introducido una opción incorrecta" << std::endl;
    return -1;
  }
  std::cin >> word;
  std::cout << std::endl;
  while ((x = std::cin.get()) != '\n') {
    word += x; 
  }

  Vigenere cipher(word, key);
  if (option == 1) cipher.Code();
  if (option == 2) cipher.Decode();

  size_t counter = 0;
  std::cout << "Mensaje original:    ";
  for (const char& c : cipher.getText()) {
    if (counter == cipher.getSizeKey()) {
      std::cout << " ";
      counter = 0;
    }
    std::cout << c;
    counter++;
  }
  counter = 0;

  std::cout << "\nClave:               ";
  for (const char& c : cipher.getTextKey()) {
    if (counter == cipher.getSizeKey()) {
      std::cout << " ";
      counter = 0;
    }
    std::cout << c;
    counter++;
  }
  counter = 0;
  if (option == 1) {
    std::cout << "\nMensaje cifrado:     ";
    for (const char& c : cipher.getCipherText()) {
      if (counter == cipher.getSizeKey()) {
        std::cout << " ";
        counter = 0;
      }
      std::cout << c;
      counter++;
    }
  } else {
    std::cout << "\nMensaje descifrado:  ";
    for (const char& c : cipher.getCipherText()) {
      if (counter == cipher.getSizeKey()) {
        std::cout << " ";
        counter = 0;
      }
      std::cout << c;
      counter++;
    }
  }
  std::cout << std::endl;

  return 0;
}