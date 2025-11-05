#include <iostream>
#include "parser.h"
#include "circuit-writer.h"
#include "simplifying-algorithms.h"
#include "metrics-calculation.h"

int main()
{
    Circuit circuit;
    Circuit circuit_optimized;
    circuit = parse_bench_file("benchmarks/test.bench");
    circuit_optimized = parse_bench_file("benchmarks/test.bench");

    simplify_duplicate_operands(&circuit_optimized);
    remove_pendant_vertices(&circuit_optimized);

    std::cerr << "Circuit improvement = " << gate_count_impovement(circuit, circuit_optimized) << "%" << std::endl;

    return 0;
}