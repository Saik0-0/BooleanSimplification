#pragma once
#include <string>
#include <vector>

enum GateType
{
    G_INPUT,
    G_OUTPUT,
    G_AND,
    G_OR,
    G_NOT,
    G_XOR
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