#include "./generator.h"


void CA::rotate(std::vector<int>& arr, int bit) {
  std::vector<int> copy_array = arr;
  for (int i = 1; i < 10; i++) {
    arr[i] = copy_array[i - 1];
  }
  arr[0] = bit;
}

std::string CA::outText(std::vector<int>& G, int bit) {
  std::string result = "";
  for (size_t i = 0; i < G.size(); i++) {
    result += std::to_string(G[i]);
  }
  result += "-->                 " + std::to_string(bit);
  return result;
}

void CA::generate(int id, int size) {
  std::string text = "";
  std::vector<int> G1 = {};
  std::vector<int> G2 = {};

  G1.resize(10, 1);
  G2.resize(10, 1);
  
  //Pareja de celdas que corresponden al identificador introducido por argumento
  const std::pair<int, int> taps = satellites_[id -1]; 
 
  for (int i = 0; i < size; i++) {
    int retroalimentation_G1 = G1[2] ^ G1[9];
    int retroalimentation_G2 = G2[1] ^ G2[2] ^ G2[5] ^ G2[7] ^ G2[8] ^ G2[9];

    int outG2 = G2[taps.first - 1] ^ G2[taps.second - 1];
    
    int ca_bit = outG2 ^ G1[9];

    text += outText(G1, retroalimentation_G1);
    //Desplazamiento del registro G1
    rotate(G1, retroalimentation_G1);

    text += " | " + outText(G2, retroalimentation_G2);
    //Desplazamiento del registro G2
    rotate(G2, retroalimentation_G2);

    std::cout << text + " | " + std::to_string(ca_bit) << std::endl;
    text = "";
  }
}
