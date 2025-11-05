#pragma once
#include "circuit.h"
#include <string>
#include <string_view>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

Circuit parse_bench_file(const std::string_view filename);
bool line_parser(std::string_view line, Circuit* circuit);
GateType str_to_gate(const std::string_view str);
bool str_to_gate_operands(const std::string_view str, std::vector<size_t>* inputs, Circuit* circuit);