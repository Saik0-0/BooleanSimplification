#include <iostream>
#include "parser.h"

int main()
{
    Circuit circuit;
    circuit = parse_bench_file("benchmarks/test.bench");

    write_circuit(circuit);
    simplify_duplicate_operands(&circuit);
    write_circuit(circuit);

    

    // Gate gate("A", GateType::AND, {"y"});

    // bool a = equal_operands_checker(&gate);

    // std::cout << "Equal operands? (0 - no, 1 - yes): " << a << std::endl;

    return 0;
}