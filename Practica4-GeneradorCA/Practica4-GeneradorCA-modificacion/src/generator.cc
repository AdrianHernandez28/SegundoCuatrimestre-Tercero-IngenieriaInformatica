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

std::vector<int> CA::generateRandomTaps() {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::vector<int> posibilities = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> taps;

  std::sample(posibilities.begin(), posibilities.end(),
              std::back_inserter(taps), 2, gen);
  return taps;
}

int CA::randomID(int tap1, int tap2) {
  int result = -1;
  for (int i = 0; i < satellites_.size(); i++) {
    if (satellites_[i].first == tap1 && satellites_[i].second == tap2) {
      result = i;
      break;
    }
  }
  return result;
}

void CA::generate(int size) {
  std::string text = "";
  std::vector<int> G1 = {};
  std::vector<int> G2 = {};

  G1.resize(10, 1);
  G2.resize(10, 1);
  
  //Pareja de celdas que corresponden al identificador introducido por argumento
  const std::vector<int> taps = generateRandomTaps();

  std::cout << "Taps aleatorios seleccionados: " << taps[0] << " y " << taps[1] << std::endl;
  int id = randomID(taps[0], taps[1]);
  if (id == -1) {
    std::cout << "Los taps no corresponden a ningun satelite" << std::endl;
  } else {
    std::cout << "ID del saltelite: " << randomID(taps[0], taps[1]) + 1  << std::endl;
  }
   

  for (int i = 0; i < size; i++) {
    int retroalimentation_G1 = G1[2] ^ G1[9];
    int retroalimentation_G2 = G2[1] ^ G2[2] ^ G2[5] ^ G2[7] ^ G2[8] ^ G2[9];

    int outG2 = G2[taps[0] - 1] ^ G2[taps[1] - 1];
    
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
