#include <iostream>
#include "parser.h"

int main()
{
    Circuit circuit;
    bool parsing_checker = parse_bench_file("benchmarks/logVn_2.bench", &circuit);

    return 0;
}