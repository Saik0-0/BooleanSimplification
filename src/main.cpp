#include <iostream>
#include "parser.h"

int main()
{
    Circuit circuit;
    bool parsing_checker = bench_file_parser("benchmarks/test.bench", circuit);

    return 0;
}