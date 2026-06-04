#include "vigenere.h"

Vigenere::Vigenere(const std::string& original_text, const std::string& key) {
  text_key_.clear();
  text_ = original_text;
  key_ = key;

  replaceTildes(text_);
  replaceTildes(key_);

  //Transformamos todas las letras a mayúscula
  for (char& c : key_) {
      c = std::toupper(static_cast<unsigned char>(c));
  }
  //Eliminamos todos los espacios del mensaje original
  text_.erase(std::remove(text_.begin(), text_.end(), ' '), text_.end());

  for (char& c : text_) {
      c = std::toupper(static_cast<unsigned char>(c));
  }

  //Creamos la cadena de la misma clave repetida
  while (text_key_.size() < text_.size()) {
    text_key_ += key_;
  }
  while (text_key_.size() > text_.size()) {
    text_key_.pop_back();
  }
}

void Vigenere::Code() {
  cipher_text_.clear();
  for (size_t i = 0; i < text_.size(); i++) {
    cipher_text_ += static_cast<unsigned char>(((text_[i] - 'A' + text_key_[i] - 'A' ) % 26) + 'A'); 
  }
}

void Vigenere::Decode() {
  cipher_text_.clear();
  for (size_t i = 0; i < text_.size(); i++) {
    int num = static_cast<int>((((text_[i] - 'A') - (text_key_[i] - 'A')))); 
    if (num < 0) num += 26;
    cipher_text_ += static_cast<unsigned char>(num + 'A');
  }
}

std::string Vigenere::getText() const { return text_; }
std::string Vigenere::getTextKey() const { return text_key_; }
std::string Vigenere::getCipherText() const { return cipher_text_; }
size_t Vigenere::getSizeKey() const { return key_.size(); }


void replaceTildes(std::string& s) {
    const std::pair<std::string, std::string> map[] = {
        {"á", "A"}, {"é", "E"}, {"í", "I"}, {"ó", "O"}, {"ú", "U"},
        {"Á", "A"}, {"É", "E"}, {"Í", "I"}, {"Ó", "O"}, {"Ú", "U"}
    };
    
    for (const auto& [from, to] : map) {
        size_t pos;
        while ((pos = s.find(from)) != std::string::npos) {
            s.replace(pos, from.length(), to);
        }
    }
}
