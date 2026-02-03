#include "vernam.h"


Vernam::Vernam(const std::string& message) {
  original_message_ = message;
  binary_message_ = StringToBinary(message);
  bin_size_ = binary_message_.length();
}

std::string Vernam::getOriginalMessage() const { return original_message_; }
std::string Vernam::getBinaryMessage() const { return binary_message_; }
std::string Vernam::getRandomKey() const { return random_key_; }
std::string Vernam::getBinaryKey() const { return binary_key_; }
std::string Vernam::getKey() const { return key_; }
bool Vernam::getFlag() const { return flag_; }
size_t Vernam::getBinSize() const { return bin_size_; }

void Vernam::setRandomKey(std::string& k) {
  assert (k.length() == bin_size_);
  random_key_ = k;
}

std::string Vernam::StringToBinary(const std::string& str) {
  std::string result = "";
  for (unsigned char c : str) {
    std::bitset<8> bin(c);
    result += bin.to_string();
  }
  return result;
}

std::string Vernam::GenerateRandomBinary() {
  std::string bin = "";
  //Inicialización de aleatoriedad de numero aleatorio 0 o 1
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0,1);

  for (size_t i = 0; i < bin_size_; i++) {
    bin += std::to_string(dist(gen));
  }
  return bin;
}

void Vernam::Code() {
  binary_key_.clear();
  key_.clear();

  if (flag_ == false) {
    random_key_ = GenerateRandomBinary();
  }
  //Hacemos XOR
  for (size_t i = 0; i < bin_size_; i++) {
    if (binary_message_[i] == random_key_[i]) {
      binary_key_ += '0';
    } else {
      binary_key_ += '1';
    }
  }

  //num_bits siempre sera 8 porque cada caracter ASCII ocupa 8 bits
  int num_bits = 8;
  std::vector<std::string> bin_nums;

  //Hago saltos de num_bits para coger todos los bits bien divididos
  for (size_t j = 0; j < binary_key_.length(); j += num_bits) {
    bin_nums.push_back(binary_key_.substr(j, num_bits));
  }

  for (int k = 0; k < bin_nums.size(); k++) {
    const std::string& bin_str = bin_nums[k];
    std::bitset<8> b(bin_str);
    //Con esto paso el número binario directamente a decimal
    //y con static_cast paso el decimal a char
    char c = static_cast<char>(b.to_ulong());
    key_ += c;
  }
}

void Vernam::ToManualFlag() { flag_ = true; }
