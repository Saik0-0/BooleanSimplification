#include "simplifying-algorithms.h"
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>
#include <unordered_set>


bool Gate::check_has_equal_operands() const
{
    if (this->operands.size() <= 1) 
    {
        return false;
    }

    for (size_t i = 0; i < this->operands.size() - 1; ++i)
    {
        if (this->operands[i] != this->operands[i+1])
        {
            return false;
        }
    }

    return true;
}

void replace_gate(Circuit* circuit, const Gate& gate_to_replace)
{
    size_t replasing_operand_id = gate_to_replace.operands[0];
    size_t old_gate_id = gate_to_replace.id;
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
}

void simplify_duplicate_operands(Circuit* circuit)
{
    std::vector<const Gate*> gates_to_replace;
    for (const Gate& gate : circuit->gates) 
    {
        if ((gate.type == GateType::AND || gate.type == GateType::OR) && gate.check_has_equal_operands())
        {
            gates_to_replace.push_back(&gate);
            std::cerr << "I need to replace gate: " << gate.id << std::endl;
        }
    }

    for (const Gate* gate : gates_to_replace)
    {
        std::cerr << "Simplifying gate " << gate->id 
                  << " (" << gate->type << ") with duplicate operands" << std::endl;
        replace_gate(circuit, *gate);
    }

    std::unordered_set<size_t> gate_ids_to_remove;
    for (const Gate* gate : gates_to_replace)
    {
        gate_ids_to_remove.insert(gate->id);
    }

    remove_gates(circuit, gate_ids_to_remove);
}


void remove_gates(Circuit* circuit, const std::unordered_set<size_t> gate_ids_to_remove)
{   
    size_t max_id = 0;
    
    for (size_t input_id : circuit->inputs) 
    {
        if (input_id > max_id) max_id = input_id;
    }
    for (size_t output_id : circuit->outputs) 
    {
        if (output_id > max_id) max_id = output_id;
    }
    for (const Gate& gate : circuit->gates) 
    {
        if (gate.id > max_id) max_id = gate.id;
    }

    std::unordered_map<size_t, size_t> id_map;
    std::vector<Gate> new_gates;
    size_t next_new_id = max_id + 1;
    
    for (const Gate& gate : circuit->gates) 
    {
        if (!gate_ids_to_remove.contains(gate.id)) 
        {
            size_t new_id = next_new_id++;
            id_map[gate.id] = new_id;
            new_gates.emplace_back(new_id, gate.type, gate.operands);
        }
    }
    
    circuit->gates = std::move(new_gates);
    circuit->gate_name_table.update_after_removal(id_map, circuit->inputs, circuit->outputs);
    update_references(circuit, id_map);
}

void update_references(Circuit* circuit, const std::unordered_map<size_t, size_t>& id_map)
{
    for (size_t& input_id : circuit->inputs) 
    {
        if (id_map.count(input_id)) 
        {
            input_id = id_map.at(input_id);
        }
    }
    for (size_t& output_id : circuit->outputs) 
    {
        if (id_map.count(output_id)) 
        {
            output_id = id_map.at(output_id);
        }
    }
    for (Gate& gate : circuit->gates) 
    {
        for (size_t& operand_id : gate.operands) 
        {
            if (id_map.count(operand_id)) 
            {
                operand_id = id_map.at(operand_id);
            }
        }
    }
}

bool check_output_gate(const std::vector<size_t>& outputs, size_t id)
{
    auto it = std::find(outputs.begin(), outputs.end(), id);
    if (it != outputs.end()) return true;

    return false;
}

std::unordered_set<size_t> find_pendant_vertices(const Circuit& circuit)
{
    std::unordered_set<size_t> pendant_vertices_ids;
    std::unordered_set<size_t> significant_gates = find_significant_gates_dfs(CircuitGraph(circuit), circuit.inputs, circuit.outputs);
    
    for (const Gate& gate : circuit.gates)
    {
        if (!significant_gates.contains(gate.id))
        {
            pendant_vertices_ids.insert(gate.id);
        }
    }

    return pendant_vertices_ids;
}

void remove_pendant_vertices(Circuit* circuit)
{
    std::unordered_set<size_t> pedant_vertices_ids = find_pendant_vertices(*circuit);
    remove_gates(circuit, pedant_vertices_ids);
}

bool dfs_find_path(const CircuitGraph& graph, size_t gate_id, 
                    const std::unordered_set<size_t>& outputs,
                    std::unordered_set<size_t>& visited,
                    std::unordered_set<size_t>& result)
{
    if (visited.contains(gate_id)) return result.contains(gate_id);

    bool lead_to_output = false;
    visited.insert(gate_id);

    if (outputs.contains(gate_id)) lead_to_output = true;

    std::vector<size_t> gate_children;
    if (graph.get_children(gate_id, &gate_children))
    {
        for (size_t child : gate_children)
        {
            if (dfs_find_path(graph, child, outputs, visited, result))
            {
                lead_to_output = true;
            }
        }
    }

    if (lead_to_output) result.insert(gate_id);

    return lead_to_output;
}

std::unordered_set<size_t> find_significant_gates_dfs(const CircuitGraph& graph, 
                                                    const std::vector<size_t>& inputs, 
                                                    const std::vector<size_t>& outputs)
{
    std::unordered_set<size_t> result;
    std::unordered_set<size_t> visited;
    std::unordered_set<size_t> outputs_set(outputs.begin(), outputs.end());

    for (size_t input_id: inputs)
    {
        if (graph.all_nodes.contains(input_id))
        {
            dfs_find_path(graph, input_id, outputs_set, visited, result);
        }
    }

    return result;
}