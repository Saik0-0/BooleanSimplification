#include "parser.h"
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>

bool equal_operands_checker(const Gate* gate)
{
    if (gate->operands.size() <= 1) 
    {
        return false;
    }

    for (size_t i = 0; i < gate->operands.size() - 1; ++i)
    {
        if (gate->operands[i] != gate->operands[i+1])
        {
            return false;
        }
    }

    return true;
}

void replace_gate(Circuit* circuit, const Gate* gate_to_replace)
{
    size_t replasing_operand_id = gate_to_replace->operands[0];
    size_t old_gate_id = gate_to_replace->id;
    for (Gate& gate : circuit->gates)
    {
        for (size_t& operand_id : gate.operands)
        {
            if (operand_id == old_gate_id)
            {
                operand_id = replasing_operand_id;
            }
        }
    }

    for (size_t& output_id : circuit->outputs)
    {
        if (output_id == old_gate_id)
        {
            output_id = replasing_operand_id;
        }
    }

    remove_gate(circuit, old_gate_id);
}

void simplify_duplicate_operands(Circuit* circuit)
{
    std::vector<const Gate*> gates_to_replace;
    for (const Gate& gate : circuit->gates)
    {
        if ((gate.type == GateType::AND || gate.type == GateType::OR) && equal_operands_checker(&gate))
        {
            gates_to_replace.push_back(&gate);
        }
    }

    for (const Gate* gate : gates_to_replace)
    {
        std::cout << "Simplifying gate " << gate->id 
                  << " (" << gate->type << ") with duplicate operands" << std::endl;
        replace_gate(circuit, gate);
    }
}

void remove_gate(Circuit* circuit, size_t gate_id_to_remove)
{
    auto pos = std::remove_if(circuit->gates.begin(), circuit->gates.end(), [gate_id_to_remove](const Gate& gate) 
                    {
                        return gate.id == gate_id_to_remove;
                    }
                );

    circuit->gates.erase(pos, circuit->gates.end());
}