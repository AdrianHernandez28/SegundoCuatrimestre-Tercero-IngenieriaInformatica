#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Vigenere {
 public:
  Vigenere(const std::string& original_text, const std::string& key);
  void Code();
  void Decode();

  std::string getText() const;
  std::string getTextKey() const;
  std::string getCipherText() const;
  size_t getSizeKey() const;


 private:
  std::string text_;
  std::string text_key_;
  std::string key_;
  std::string cipher_text_;
};