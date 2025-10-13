#include <iostream>
#include "parser.h"

int main()
{
    Circuit circuit;
    circuit = parse_bench_file("benchmarks/logVn_2.bench");

    return 0;
}