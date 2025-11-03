#pragma once
#include "circuit.h"
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>
#include <unordered_set>

void replace_gate(Circuit* circuit, const Gate& gate_to_replace);
void simplify_duplicate_operands(Circuit* circuit);
void remove_gates(Circuit* circuit, const std::vector<size_t> gate_ids_to_remove);
void update_references(Circuit* circuit, const std::unordered_map<size_t, size_t>& id_map);
std::vector<size_t> find_pendant_vertices(const Circuit& circuit);
void remove_pendant_vertices(Circuit* circuit);