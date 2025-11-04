#include "metrics-calculation.h"

double gate_count_impovement(const Circuit& original, const Circuit& optimized)
{
    size_t gate_count_original = original.gates.size();
    size_t gate_count_optimized = optimized.gates.size();
    return 100.0 * (1.0 - (double) gate_count_optimized / gate_count_original);
}