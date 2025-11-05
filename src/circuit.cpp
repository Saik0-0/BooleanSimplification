#include "circuit.h"
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <optional>

std::ostream& operator<<(std::ostream& os, GateType type) {
    switch (type) 
    {
        case GateType::AND: return os << "AND";
        case GateType::OR: return os << "OR";
        case GateType::NOT: return os << "NOT";
        case GateType::INPUT: return os << "INPUT";
        case GateType::OUTPUT: return os << "OUTPUT";
        case GateType::XOR: return os << "XOR";
        case GateType::NAND: return os << "NAND";
        case GateType::NOR: return os << "NOR";
        case GateType::NXOR: return os << "NXOR";
        default: return os << "UNKNOWN";
    }
}

std::optional<size_t> GateNameTable::get_id(const std::string& name) const
{
    auto pos = str_to_id.find(name);
    if (pos != str_to_id.end())
    {
        return pos -> second;
    }

    return std::nullopt;
}

std::string_view GateNameTable::get_name(size_t id) const
{
    return id_to_str.at(id);
}

size_t GateNameTable::create_id(const std::string& name)
{
    size_t new_id = str_to_id.size();
    str_to_id[name] = new_id;
    id_to_str.push_back(name);
    return new_id;
}

size_t GateNameTable::get_max_id() const
{
    return id_to_str.size();
}

void GateNameTable::update_after_removal(const std::unordered_map<size_t, size_t>& id_map, 
                            const std::vector<size_t>& input_ids,
                            const std::vector<size_t>& output_ids) 
{
    std::unordered_set<size_t> protected_ids;
    for (size_t id : input_ids) 
    {
        protected_ids.insert(id);
    }
    for (size_t id : output_ids) 
    {
        protected_ids.insert(id);
    }

    for (const auto& [old_id, new_id] : id_map) 
    {
        if (old_id < id_to_str.size() && !id_to_str[old_id].empty()) 
        {
            std::string name = id_to_str[old_id];
            
            str_to_id.erase(name);
            
            if (new_id >= id_to_str.size()) 
            {
                id_to_str.resize(new_id + 1, "");
            }
            id_to_str[new_id] = name;
            
            str_to_id[name] = new_id;
            
            if (!protected_ids.count(old_id)) 
            {
                id_to_str[old_id] = "";
            }
        }
    }
}

void GateNameTable::print() const 
{
    std::cerr << "Gate Name Table: \n";
    std::cerr << "=================\n";
    
    for (size_t i = 0; i < id_to_str.size(); ++i) 
    {
        std::cerr << "ID " << i << " -> \"" << id_to_str[i] << "\"\n";
    }
    
    std::cerr << "Total entries: " << id_to_str.size() << "\n";
    std::cerr << "=================" << std::endl;
}

void CircuitGraph::add_node(size_t node)
{
    all_nodes.insert(node);
    if (!parent_children_dependences.contains(node)) parent_children_dependences[node] = {};
    if (!child_parents_dependences.contains(node)) child_parents_dependences[node] = {};
    if (!in_dependenses_amount.contains(node)) in_dependenses_amount[node] = 0;
}

CircuitGraph::CircuitGraph(const Circuit& circuit)
{
    parent_children_dependences.clear();
    child_parents_dependences.clear();
    in_dependenses_amount.clear();
    all_nodes.clear();

    for (size_t input_id : circuit.inputs)
    {
        add_node(input_id);
        in_dependenses_amount[input_id] = 0;
    }

    for (const Gate& gate : circuit.gates)
    {
        add_node(gate.id);
        for (size_t operand_id : gate.operands)
        {
            add_node(operand_id);
            parent_children_dependences[operand_id].push_back(gate.id);
            child_parents_dependences[gate.id].push_back(operand_id);
            in_dependenses_amount[gate.id]++;
        }
    }
}

bool CircuitGraph::get_children(size_t gate_id, std::vector<size_t>* children) const
{
    children->clear();
    auto pos = parent_children_dependences.find(gate_id);
    if (pos != parent_children_dependences.end())
    {
        *children = pos->second;
        return true;
    }
    return false;
}