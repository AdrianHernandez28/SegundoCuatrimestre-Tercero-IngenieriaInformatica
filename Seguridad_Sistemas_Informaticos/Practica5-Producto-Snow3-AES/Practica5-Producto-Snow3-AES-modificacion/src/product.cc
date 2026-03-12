#include "./product.h"

Product::Product(bool flag) {
  const_byte_ = flag ? 0b00011011 : 0b10101001;
}

void Product::operation(unsigned char first_byte, unsigned char second_byte) {
  std::bitset<8> binary_byte1(first_byte);
  std::bitset<8> binary_byte2(second_byte);
  first_byte_ = binary_byte1;
  second_byte_ = binary_byte2;

  std::vector<std::bitset<8>> bytes = distributive(binary_byte2);
  std::vector<std::bitset<8>> results = {};
  std::cout << "Traza:" << std::endl;
  for (int i = 0; i < bytes.size(); i++) {
    int jumps = numJumps(bytes[i]);
    results.push_back(subOperation(first_byte, jumps));
    std::cout << first_byte_ << " * " << bytes[i] << ": " << results[results.size() - 1] << ", en hexadecimal: " <<  std::hex << first_byte_.to_ulong() << " * " << bytes[i].to_ulong() << ": " << results[results.size() - 1].to_ulong() << std::endl;
  }
  finalAdd(results);
}

std::vector<std::bitset<8>> Product::distributive(std::bitset<8> binary_byte) {
  std::vector<std::bitset<8>> results = {};
  for (int i = 0; i < 8; i++) {
    if (binary_byte[i]) {
      //Por cada bit activo creo un byte binario con solo ese bit
      std::bitset<8> bin;
      bin.set(i);
      results.push_back(bin);
    }
  }
  return results;
}

int Product::numJumps(std::bitset<8> byte) {
  for (int i = 0; i < 8; i++) {
    if (byte[i]) return i; // El índice del bit es el número de desplazamientos
  }
  return 0;
}

std::bitset<8> Product::subOperation(std::bitset<8> byte, int jumps) {
  std::bitset<8> result = byte;

  for (int i = 0; i < jumps; i++) {
    bool bit = result[7];
    result <<= 1;
    if (bit) {
      result = result ^ const_byte_; 
    } 
  }
  return result;
}

void printBinary(std::vector<std::bitset<8>>& results) {
  std::bitset<8> result;
  for (size_t i = 0; i < results.size(); i++) {
    result ^= results[i];
    std::cout << results[i];
    if (results.size() -1 != i) {
      std::cout << " ^ ";
    }
  }
  std::cout << ": " << result << std::endl << std::endl;
}

void Product::finalAdd(std::vector<std::bitset<8>>& results) {
  result_.reset();
  for (int i = 0; i < results.size(); i++) {
    result_ ^= results[i];
    std::cout << std::hex << results[i].to_ulong();
    if (results.size() -1 != i) {
      std::cout << " ^ ";
    }
  }
  std::cout << ": " << result_.to_ulong() << std::endl << std::endl;
  std::cout << "En binario: " << std::endl;
  printBinary(results);
}

