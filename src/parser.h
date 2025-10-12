#pragma once
#include <string>
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
    std::string name;
    GateType g_type;
    std::vector<std::string> inputs;
};

struct Circuit
{
    std::vector<std::string> gates;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

bool bench_file_parser(const std::string& filename, Circuit& circuit);
bool line_parser(const std::string& line, Circuit& circuit);
GateType str_to_gate(const std::string& str);
bool str_to_gate_inputs(const std::string& str, std::vector<std:: string>& inputs);