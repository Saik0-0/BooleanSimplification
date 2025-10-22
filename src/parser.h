#pragma once
#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <cstdint>
#include <unordered_map>

enum class GateType: uint8_t
{
    INPUT,
    OUTPUT,
    AND,
    OR,
    NOT,
    XOR,
    NAND,
    NOR,
    NXOR
};

inline std::ostream& operator<<(std::ostream& os, GateType type) {
    switch (type) {
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

class GateNameTable {

private:
    std::unordered_map<std::string, std::size_t> str_to_id;
    std::vector<std::string> id_to_str;

public:
    size_t get_id(const std::string& name)
    {
        auto pos = str_to_id.find(name);
        if (pos != str_to_id.end())
        {
            return pos -> second;
        }

        //If map don't contain name
        size_t new_id = str_to_id.size();
        str_to_id[name] = new_id;
        id_to_str.push_back(name);
        return new_id;
    }

    std::string get_name(size_t id)
    {
        return id_to_str.at(id);
    }
};

struct Gate
{
    size_t id;
    GateType type;
    std::vector<size_t> operands;

    Gate(size_t gate_id, GateType g_type, std::vector<size_t> gate_operands = {})
    : id(gate_id), type(g_type), operands(std::move(gate_operands))
    {}
};


struct Circuit
{
    GateNameTable gate_name_table;
    std::vector<Gate> gates;
    std::vector<size_t> inputs;
    std::vector<size_t> outputs;
};

Circuit parse_bench_file(const std::string_view filename);
bool line_parser(std::string_view line, Circuit* circuit);
GateType str_to_gate(const std::string_view str);
bool str_to_gate_operands(const std::string_view str, std::vector<size_t>* inputs, Circuit* circuit);

void replace_gate(Circuit* circuit, const Gate& gate_with_dublicate_operаnd);
bool check_has_equal_operands(const Gate& gate);
void simplify_duplicate_operands(Circuit* circuit);
void remove_gate(Circuit* circuit, size_t gate_id_to_remove);
void remove_pendant_vertices(Circuit* circuit, const std::vector<const Gate*> gates_to_replace);

void write_circuit(Circuit& circuit);