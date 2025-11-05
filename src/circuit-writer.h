#pragma once
#include <iostream>
#include "circuit.h"

void write_gate(const Gate& gate, std::ostream& os = std::cerr);
void write_circuit(const Circuit& circuit, std::ostream& os = std::cerr);