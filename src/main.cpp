#include <iostream>
#include "parser.h"
#include "circuit-writer.h"

int main()
{
    Circuit circuit;
    circuit = parse_bench_file("benchmarks/test.bench");

    write_circuit(circuit);
    circuit.gate_name_table.print();
    circuit.simplify_duplicate_operands();
    // write_circuit(circuit);
    // circuit.gate_name_table.print();
    // std::vector<size_t> pv = circuit.find_pedant_vertices();

    // for (size_t v : pv)
    // {
    //     std::cerr << "Pedant vertice: " << v << "\n";
    // }

    // std::cerr << std::endl;

    circuit.remove_pedant_vertices();
    write_circuit(circuit);
    circuit.gate_name_table.print();

    return 0;
}