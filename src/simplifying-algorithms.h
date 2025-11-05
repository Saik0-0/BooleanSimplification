#pragma once
#include "circuit.h"
#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>
#include <unordered_set>

void replace_gate_with_operand(Circuit* circuit, const Gate& gate_to_replace);
void simplify_duplicate_operands(Circuit* circuit);
void remove_gates(Circuit* circuit, const std::unordered_set<size_t>& gate_ids_to_remove);
void update_references(Circuit* circuit, const std::unordered_map<size_t, size_t>& id_map);
std::unordered_set<size_t> find_pendant_vertices(const Circuit& circuit);
void remove_pendant_vertices(Circuit* circuit);
std::unordered_set<size_t> find_significant_gates_dfs(const CircuitGraph& graph, 
                                                    const std::vector<size_t>& inputs, 
                                                    const std::vector<size_t>& outputs);
bool dfs_find_path(const CircuitGraph& graph, size_t gate_id, 
                    const std::unordered_set<size_t>& outputs,
                    std::unordered_set<size_t>& visited,
                    std::unordered_set<size_t>& result);