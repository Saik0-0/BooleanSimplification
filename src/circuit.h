#pragma once
#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>


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

std::ostream& operator<<(std::ostream& os, GateType type);


class GateNameTable 
{
private:
    std::unordered_map<std::string, std::size_t> str_to_id;
    std::vector<std::string> id_to_str;

public:
    size_t get_id(const std::string& name);
    std::string get_name(size_t id);

    void update_after_removal(const std::unordered_map<size_t, size_t>& id_map, 
                             const std::vector<size_t>& input_ids,
                             const std::vector<size_t>& output_ids);

    void print() const;
};

struct Gate
{
    size_t id;
    GateType type;
    std::vector<size_t> operands;

    Gate(size_t gate_id, GateType g_type, std::vector<size_t> gate_operands = {})
    : id(gate_id), type(g_type), operands(std::move(gate_operands))
    {}

    bool check_has_equal_operands() const;
};


struct Circuit
{
    GateNameTable gate_name_table;
    std::vector<Gate> gates;
    std::vector<size_t> inputs;
    std::vector<size_t> outputs;

    void replace_gate(const Gate& gate_with_dublicate_operаnd);
    void simplify_duplicate_operands();
    void remove_gates(const std::vector<size_t> gate_ids_to_remove);
    void update_references(const std::unordered_map<size_t, size_t>& id_map);
    std::vector<size_t> find_pendant_vertices();
    void remove_pendant_vertices();
};