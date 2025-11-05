#include "circuit-writer.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void write_gate(const Gate& gate, std::ostream& os = std::cerr)
{
    os << "Gate id: " << gate.id << ", gate type: " << gate.type << ", operands: ";
    for (size_t operand : gate.operands)
    {
        os << operand << ", ";
    }
    os << std::endl;
}

void write_circuit(const Circuit& circuit, std::ostream& os = std::cerr)
{
    os << "----------Circuit----------" << "\n";

    for (size_t input_id : circuit.inputs)
    {
        os << "Input: " << input_id << "\n";
    }

    for (const Gate& gate : circuit.gates)
    {
        write_gate(gate, os);
    }

    for (size_t output_id : circuit.outputs)
    {
        os << "Output: " << output_id << "\n";
    }

    os << std::flush;

}