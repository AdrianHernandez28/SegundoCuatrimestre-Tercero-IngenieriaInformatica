# Seguridad y Criptografía - Algoritmos y Protocolos

![C++](https://img.shields.io/badge/Language-C++-blue.svg) ![Status](https://img.shields.io/badge/Status-Completado-brightgreen)
![Universidad](https://img.shields.io/badge/Universidad-ULL-purple)

## Descripción general
Este repositorio contiene una colección completa de algoritmos criptográficos, protocolos de intercambio de claves y sistemas de firma digital desarrollados durante el Grado en Ingeniería Informática. 

El objetivo de estos proyectos es comprender desde la base matemática hasta la implementación práctica cómo se protege la información en los sistemas actuales (desde cifrados clásicos hasta conceptos de criptografía cuántica).

## Prácticas y Algoritmos Implementados

El repositorio está estructurado en diferentes módulos según el tipo de criptografía:

### Cifrados Clásicos y de Flujo
* **[Practica1-CifradoDeVernam](./Practica1-CifradoDeVernam):** Implementación del cifrado de Vernam (One-Time Pad), el único cifrado teóricamente inquebrantable.
* **[Practica2-CifradoVigenere](./Practica2-CifradoVigenere):** Cifrado por sustitución polialfabética clásico.
* **[Practica3-CifradoChacha20](./Practica3-CifradoChacha20):** Implementación del moderno cifrado de flujo ChaCha20.
* **[Practica4-GeneradorCA](./Practica4-GeneradorCA):** Generador Congruencial Aleatorio para la creación de secuencias pseudoaleatorias.

### Cifrados de Bloque y Estándares Modernos
* **[Practica5-Producto-Snow3-AES](./Practica5-Producto-Snow3-AES):** Implementación de operaciones en cuerpos de Galois (GF) utilizadas en Snow3G y AES.
* **[Practica6-AES](./Practica6-AES):** Implementación del Advanced Encryption Standard (AES), el estándar actual de cifrado simétrico.
* **[Practica7-Modo-CBC](./Practica7-Modo-CBC):** Modos de operación de cifrado de bloque (Cipher Block Chaining).

### Criptografía Asimétrica (Clave Pública)
* **[Practica8-Diffie-Hellman](./Practica8-Diffie-Hellman):** Protocolo de intercambio de claves seguras a través de un canal inseguro.
* **[Practica10-RSA](./Practica10-RSA):** Sistema criptográfico de clave pública RSA (generación de claves, cifrado y descifrado).
* **[Practica11-Eliptica](./Practica11-Eliptica):** Criptografía de Curva Elíptica (ECC), la alternativa moderna y eficiente a RSA.
* **[Practica12-RSA-Firma](./Practica12-RSA-Firma):** Implementación de firmas digitales utilizando RSA para garantizar autenticidad.

### Criptografía Cuántica
* **[Practica9-BB84](./Practica9-BB84):** Simulación del protocolo de distribución cuántica de claves BB84.

## Tecnologías Utilizadas
* **Lenguaje principal:** [Python / C++]

## Cómo ejecutar los proyectos
Cada carpeta contiene su propio código fuente. Para ejecutar un algoritmo en concreto, navega al directorio correspondiente y ejecuta el archivo principal.

Por ejemplo, para probar el cifrado AES:
```bash
cd Practica6-AES
# Ejemplo si es Python:
python main.py
# Ejemplo si es C++:
# make && ./aes
