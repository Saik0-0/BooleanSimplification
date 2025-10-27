#include "circuit.h"
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>
#include <unordered_set>

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

size_t GateNameTable::get_id(const std::string& name)
{
    auto pos = str_to_id.find(name);
    if (pos != str_to_id.end())
    {
        return pos -> second;
    }

    size_t new_id = str_to_id.size();
    str_to_id[name] = new_id;
    id_to_str.push_back(name);
    return new_id;
}

std::string GateNameTable::get_name(size_t id)
{
    return id_to_str.at(id);
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

