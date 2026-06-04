#include <iostream>
#include <bitset>
#include <vector>
#include <string>

class Product {
 public:
  Product(bool flag);
  
  void operation(unsigned char, unsigned char);

  std::bitset<8> getResult() const { return result_; }
  std::bitset<8> getConstByte() const { return const_byte_; }
  std::bitset<8> getFirstByte() const { return first_byte_; }
  std::bitset<8> getSecondByte() const { return second_byte_; }

  private:
   int numJumps(std::bitset<8>);
   std::bitset<8> subOperation(std::bitset<8>, int);
   std::vector<std::bitset<8>> distributive(std::bitset<8>);
   void finalAdd(std::vector<std::bitset<8>>&);

   std::bitset<8> const_byte_;
   std::bitset<8> first_byte_;
   std::bitset<8> second_byte_;
   const std::bitset<8> AES_ = 00011011;
   const std::bitset<8> Snow3_ = 10101001;
   std::bitset<8> result_;
};