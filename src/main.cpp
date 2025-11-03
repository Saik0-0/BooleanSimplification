#include <iostream>
#include "parser.h"
#include "circuit-writer.h"
#include "simplifying-algorithms.h"

int main()
{
    Circuit circuit;
    circuit = parse_bench_file("benchmarks/test.bench");

    write_circuit(circuit);
    circuit.gate_name_table.print();
    simplify_duplicate_operands(&circuit);
    // write_circuit(circuit);
    // circuit.gate_name_table.print();
    // std::vector<size_t> pv = circuit.find_pedant_vertices();

    // for (size_t v : pv)
    // {
    //     std::cerr << "Pedant vertice: " << v << "\n";
    // }

    // std::cerr << std::endl;

    remove_pendant_vertices(&circuit);
    write_circuit(circuit);
    circuit.gate_name_table.print();

    return 0;
}