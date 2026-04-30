"""
UNIVERSIDAD DE LA LAGUNA
Grado en Ingeniería Informática
Asignatura: Seguridad en Sistemas Informáticos

PRÁCTICA: Protocolo BB84
-------------------------------------------------------------
Autor: Adrián David Hernández González
Fecha:  15-04-2026
Descripción: Simulación del protocolo de intercambio de claves cuánticas BB84 utilizando Qiskit.
"""
import numpy as np
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

n = 10 ** 3
qubit_index = 0
backend = AerSimulator()
message = [QuantumCircuit(1, 2) for _ in range(n)]

print(f"--- SIMULACIÓN BB84 (n={n} qubits) ---")


print("\nIntroduzca la probabilidad con la que Eve actuará (0, 1):")
p = float(input(...))


# ALICE
print("\n[1/5] Alice genera sus bits y elige sus bases de preparación...")
alice_bits = np.random.randint(2, size=n)
alice_bases = np.random.randint(2, size=n)

print(f"  -> Primeros 10 bits de Alice:  {alice_bits[:10]}")
print(f"  -> Primeras 10 bases de Alice: {alice_bases[:10]} (0: Comp, 1: Hadamard)")

for i, qc in enumerate(message):
    if alice_bits[i] == 1:
        qc.x(0)
    if alice_bases[i] == 1:
        qc.h(0)


# EVE INTERCEPTA
eve_bases = np.random.randint(2, size=n)
    
for i, qc in enumerate(message):
    if np.random.random() < p:
        if eve_bases[i] == 1:
            qc.h(0)
        # Medición
        qc.measure(qubit_index, 1)
        
        # Eve reenvía 
        if eve_bases[i] == 1:
            qc.h(0)

# BOB
print("\n[2/5] Bob elige aleatoriamente sus bases de medida...")
bob_bases = np.random.randint(2, size=n)
print(f"  -> Primeras 10 bases de Bob:   {bob_bases[:10]}")

for i, qc in enumerate(message):
    if bob_bases[i] == 1:
        qc.h(0)

classical_bit_index_for_bob_measurement = 0
for qc in message:
    qc.measure(qubit_index, classical_bit_index_for_bob_measurement)

cbit = classical_bit_index_for_bob_measurement
bob_measured_bits = []

# SIMULACIÓN
print("\n[3/5] Ejecutando los circuitos en el simulador cuántico...")
for qc in message:
    transpiled_qc = transpile(qc, backend)
    result = backend.run(transpiled_qc, shots=1).result()
    counts = result.get_counts()
    measured_bit = list(counts.keys())[0][::-1][cbit]
    bob_measured_bits.append(int(measured_bit))

print(f"  -> Primeros 10 bits medidos por Bob: {bob_measured_bits[:10]}")

# ALICE Y BOB HACEN COMPARACIÓN DE BASES
print("\n[4/5] Alice y Bob comparan sus bases públicamente...")
alice_key = []
bob_key = []

for i in range(n):
    if alice_bases[i] == bob_bases[i]:
        alice_key.append(int(alice_bits[i]))
        bob_key.append(int(bob_measured_bits[i]))

# RESULTADOS Y QBER
print("\n[5/5] Resultados Finales y Cálculo del QBER:")
errores = sum(1 for a, b in zip(alice_key, bob_key) if a != b)
qber = errores / len(alice_key) if len(alice_key) > 0 else 0

print(f"  -> Primeros 10 bits de la CLAVE FINAL: {alice_key[:10]}")
print(f"  -> Longitud de la clave descartada:    {n - len(alice_key)} bits")
print(f"  -> Longitud de la clave segura útil:   {len(alice_key)} bits")
print(f"  -> Tasa de Error Cuántico (QBER):      {qber * 100:.2f}%")

if qber < 0.11:
    print("  -> ESTADO: Éxito. Transmisión segura y sin ruido detectado.")
else:
    print("  -> ESTADO: Alerta. Ruido o espía detectado en el canal.")