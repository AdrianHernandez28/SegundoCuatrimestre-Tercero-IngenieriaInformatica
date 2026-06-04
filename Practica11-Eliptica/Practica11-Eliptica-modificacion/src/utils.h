#include <iostream>
#include <vector>
#include <cmath>

struct Punto {
    int x, y;
    bool infinito = false;
};

int modulo(int a, int p);
int modInverse(int a, int m);
Punto sumarPuntos(Punto P, Punto Q, int a, int p);
Punto multiplicarPunto(Punto G, int d, int a, int p);
Punto negarPunto(Punto P, int p);
Punto descifrado(Punto C1, Punto C2, int dB, int a, int p);