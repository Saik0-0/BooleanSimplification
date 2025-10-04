#include "parser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

GateType str_to_gate(const std::string& str)
{
    GateType g_type = G_INPUT;
    if (str == "INPUT") 
        g_type = G_INPUT;
    if (str == "OUTPUT") 
        g_type = G_OUTPUT;
    if (str == "AND") 
        g_type = G_AND;
    if (str == "OR") 
        g_type = G_OR;
    if (str == "NOT") 
        g_type = G_NOT;
    if (str == "XOR") 
        g_type = G_XOR;
    return g_type;
}