#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <bitset>
#include <vector>

class Vernam {
 public:
  //Constructor
  Vernam(const std::string& message);

  //Getters
  std::string getOriginalMessage() const;
  std::string getBinaryMessage() const;
  std::string getRandomKey() const;
  std::string getBinaryKey() const;
  std::string getKey() const;
  bool getFlag() const;
  size_t getBinSize() const;

  //Setters
  void setRandomKey(std::string& k);

  std::string StringToBinary(const std::string& str);
  std::string GenerateRandomBinary();
  void Code();
  void ToManualFlag();

 private:
  std::string original_message_;
  std::string binary_message_;
  std::string random_key_;
  std::string binary_key_ = "";
  std::string key_ = "";
  size_t bin_size_;
  bool flag_ = false;
};