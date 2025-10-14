#include "parser.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

void read_gate(Gate* gate)
{
    std::cout << "Gate id: " << gate->id << ", gate type: " << gate->type << ", operands: ";
    for (size_t operand : gate->operands)
    {
        std::cout << operand << ", ";
    }
    std::cout << std::endl;
}

void read_circuit(Circuit* circuit)
{
    std::cout << "----------Circuit----------" << std::endl;

    for (size_t input_id : circuit->inputs)
    {
        std::cout << "Input: " << input_id << std::endl;
    }

    for (Gate gate : circuit->gates)
    {
        read_gate(&gate);
    }

    for (size_t output_id : circuit->outputs)
    {
        std::cout << "Output: " << output_id << std::endl;
    }

}