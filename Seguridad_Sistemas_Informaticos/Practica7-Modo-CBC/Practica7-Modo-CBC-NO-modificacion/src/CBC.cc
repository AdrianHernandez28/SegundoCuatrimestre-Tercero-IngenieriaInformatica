#include "CBC.h"

CBC::CBC(std::array<uint8_t, 16>& key, std::array<uint8_t, 16>& original_text) {
  int index = 0;
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      key_[j][i] = key[index];
      state_[j][i] = original_text[index];
      index++;
    }
  }
}

void CBC::encrypt() {
    keyExpansion();
    
    addRoundKey(0);
    printTrace(0); 
    
    for (int i = 1; i <= 9; i++) { 
        subBytes();
        shiftRows();
        mixColumns();
        addRoundKey(i);
        printTrace(i);
    }    
    subBytes();
    shiftRows();
    addRoundKey(10);
    printTrace(10);
}

void CBC::addRoundKey(int round) {
  // Calculamos en qué columna de w_ empieza la clave de esta ronda
  int c = round * 4; 
    
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      // state_ usa [fila][columna], mientras que w_ usa [columna][fila]
      state_[i][j] ^= w_[c + j][i]; 
    }
  }
}

void CBC::subBytes() {
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      uint8_t byte = state_[i][j];
      uint8_t row = byte >> 4;
      uint8_t col = byte & 0x0F;
      state_[i][j] = Sbox_[row][col];
    }
  } 
}

void CBC::shiftRows() {
  std::array<std::array<uint8_t, 4>, 4> copy = state_;

  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      size_t temp = (i + j) % 4;

      state_[i][j] = copy[i][temp];
    }
  }
}

void CBC::mixColumns() {
  // Recorremos cada columna (c) de la matriz de estado
  for (size_t c = 0; c < 4; c++) {
    std::array<uint8_t, 4> a;
    std::array<uint8_t, 4> b;

    //Rellenamoz a y b para la columna actual
    for (size_t r = 0; r < 4; r++) {
      a[r] = state_[r][c]; // a es simplemente el byte original (multiplicado por 1)
            
      // Calculamos b que es el byte multiplicado por 2 
      uint8_t h = state_[r][c] & 0x80; 
      b[r] = state_[r][c] << 1; 
            
      if (h == 0x80) {
          b[r] ^= 0x1B; 
      }
    }

    state_[0][c] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; 
    state_[1][c] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; 
    state_[2][c] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; 
    state_[3][c] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; 
  }
}

void CBC::keyExpansion() {
    //Las primeras 4 palabras son la clave original
    for (int i = 0; i < 4; i++) {
        w_[i][0] = key_[0][i]; 
        w_[i][1] = key_[1][i];
        w_[i][2] = key_[2][i];
        w_[i][3] = key_[3][i];
    }

    //Generamos las siguientes 40 palabras
    for (int i = 4; i < 44; i++) {
        uint8_t temp[4];
        
        // Copiamos la palabra anterior
        temp[0] = w_[i - 1][0];
        temp[1] = w_[i - 1][1];
        temp[2] = w_[i - 1][2];
        temp[3] = w_[i - 1][3];

        
        if (i % 4 == 0) {
            //RotWord: El primer byte pasa al final
            uint8_t t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            //SubWord: Sustituimos cada byte usando Sbox_ 
            temp[0] = Sbox_[temp[0] >> 4][temp[0] & 0x0F];
            temp[1] = Sbox_[temp[1] >> 4][temp[1] & 0x0F];
            temp[2] = Sbox_[temp[2] >> 4][temp[2] & 0x0F];
            temp[3] = Sbox_[temp[3] >> 4][temp[3] & 0x0F];

            //Rcon: Hacemos XOR del primer byte con la constante de la ronda
            temp[0] ^= Rcon_[i / 4];
        }

        w_[i][0] = w_[i - 4][0] ^ temp[0];
        w_[i][1] = w_[i - 4][1] ^ temp[1];
        w_[i][2] = w_[i - 4][2] ^ temp[2];
        w_[i][3] = w_[i - 4][3] ^ temp[3];
    }
}

void CBC::printTrace(int round) {
    std::cout << "R" << std::dec << round << " (Subclave = ";
    
    //Imprimimos los 16 bytes de la subclave de esta ronda
    int c = round * 4;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)w_[c + col][row];
        }
    }
    
    std::cout << ") = ";
    
    //Imprimimos los 16 bytes del estado actual
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)state_[row][col];
        }
    }
    
    std::cout << std::endl;
}

void CBC::printState() const {
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)state_[row][col];
    }
  }
}

std::array<uint8_t, 16> CBC::getResult() const {
    std::array<uint8_t, 16> result;
    int index = 0;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        result[index] = state_[j][i];
        index++;
      }
    }
    return result;
  }