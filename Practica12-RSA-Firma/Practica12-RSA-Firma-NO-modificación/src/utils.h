#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <random>
#include <algorithm>

bool testLehmanPeralta(long long p);
long long euclidesExtend(long long d, long long phi);
std::vector<long long> textToBlocks(std::string& text, int value);
std::string blocksToText(std::vector<long long>& blocks, int block_size);
long long modExp(long long base, long long exp, long long mod);
long long firmaConDigest(std::vector<long long> lista_bloques_decimales, long long d, long long n);