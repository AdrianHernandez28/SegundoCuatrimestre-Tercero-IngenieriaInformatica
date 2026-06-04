#include <iostream>
#include <cmath>
#include <random> 
#include <set>
#include <algorithm>

class DiffieHellman {
 public:
  DiffieHellman(long long, long long, long long, long long);
  void generateKey();
 private:
  long long binaryExponentiation(long long, long long);
  long long prime_;
  long long alpha_;
  long long secret_a_;
  long long secret_b_;
  long long key_;
};