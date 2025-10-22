#include "parser.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void write_gate(Gate& gate)
{
    std::cerr << "Gate id: " << gate.id << ", gate type: " << gate.type << ", operands: ";
    for (size_t operand : gate.operands)
    {
        std::cerr << operand << ", ";
    }
    std::cerr << std::endl;
}

void write_circuit(Circuit& circuit)
{
    std::cerr << "----------Circuit----------" << "\n";

    for (size_t input_id : circuit.inputs)
    {
        std::cerr << "Input: " << input_id << "\n";
    }

    for (Gate& gate : circuit.gates)
    {
        write_gate(gate);
    }

    for (size_t output_id : circuit.outputs)
    {
        std::cerr << "Output: " << output_id << "\n";
    }

    std::cerr << std::endl;

}