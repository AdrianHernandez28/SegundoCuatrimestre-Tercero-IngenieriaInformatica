#include <iostream>
#include <cstdint>
#include <iomanip>
#include <random>
#include <vector>

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define ROUNDS 20


void QR(u_int32_t& a, u_int32_t& b, u_int32_t& c, u_int32_t& d) {
  a += b, d ^= a, d = ROTL(d, 16);
  c += d, b ^= c, b = ROTL(b, 12);
  a += b, d ^= a, d = ROTL(d, 8);
  c += d, b ^= c, b = ROTL(b, 7);
}

void print_matrix(u_int32_t x[16]) {
  int counter = 0;
  for (int i = 0; i < 16; i++) {
    if (counter == 4) {
      std::cout << std::endl;
      counter = 0;
    }
    std::cout << std::hex << std::setw(8) << std::setfill('0') << x[i] << " ";
    counter++;
  }
  std::cout << std::endl;
}

void chacha_block(u_int32_t out[16], u_int32_t const in[16]) {
  int i;
  u_int32_t x[16];

  for (int i = 0; i < 16; i++) x[i] = in[i];
    
  //20 ROUNDS
  for (int j = 0; j < ROUNDS; j += 2) {
    QR(x[0], x[4], x[8], x[12]); // column 0
    QR(x[1], x[5], x[9], x[13]); // column 1
    QR(x[2], x[6], x[10], x[14]); // column 2
    QR(x[3], x[7], x[11], x[15]); // column 3

    QR(x[0], x[5], x[10], x[15]); // diagonal 1
    QR(x[1], x[6], x[11], x[12]); // diagonal 2
    QR(x[2], x[7], x[8], x[13]); // diagonal 3
    QR(x[3], x[4], x[9], x[14]); // diagonal 4
  }
  std::cout << "\nEstado final tras las 20 iteraciones:" << std::endl;
  print_matrix(x);

  for (int k = 0; k < 16; k++) out[k] = x[k] + in[k];
}



int main() {
  u_int32_t out[16];

  u_int32_t ini[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
                     0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
                     0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
                     0x00000001, 0x09000000, 0x4a000000, 0x00000000};

  std::cout << "Estado inicial: " << std::endl;
  print_matrix(ini);
  chacha_block(out, ini);

  std::cout << "\nEstado de salida del generador:" << std::endl;
  print_matrix(out);

  return 0;
}