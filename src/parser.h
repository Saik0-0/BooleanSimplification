#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

enum class GateType: uint8_t
{
    INPUT,
    OUTPUT,
    AND,
    OR,
    NOT,
    XOR
};

struct Gate
{

// Точно ли надо делать private? 
// Будем же упрощать схему, понадобится менять гейты в схеме (или будем просто добавлять/удалять?)
private:   
    std::string_view name;
    GateType type;
    std::vector<std::string_view> operands;
public:
    Gate(std::string_view gate_name, GateType g_type, std::vector<std::string_view> gate_operands = {})
    : name(gate_name), type(g_type), operands(std::move(gate_operands))
    {}
};

struct Circuit
{
    std::vector<std::string_view> gates;
    std::vector<std::string_view> inputs;
    std::vector<std::string_view> outputs;
};

Circuit parse_bench_file(const std::string_view filename);
bool line_parser(std::string_view line, Circuit* circuit);
GateType str_to_gate(const std::string_view str);
bool str_to_gate_operands(const std::string_view str, std::vector<std:: string>* inputs);