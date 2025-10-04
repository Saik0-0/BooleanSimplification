#include "parser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

bool line_parser(const std::string& line, Circuit& circuit)
{
    using namespace std;
    if (line.empty())
    {
        return true;
    }

    if (line.find("INPUT") == 0)
    {
        size_t start_of_gate_name = line.find("(") + 1;
        size_t end_of_gate_name = line.find(")");
        if (start_of_gate_name != string::npos && end_of_gate_name != string::npos)
        {
            string gate_name = line.substr(start_of_gate_name, end_of_gate_name - start_of_gate_name);
            cout << "I red gate name: " << gate_name << endl;
        }
    }
    return true;
}

bool bench_file_parser(const std::string& filename, Circuit& circuit)
{
    using namespace std;
    fstream file(filename);
    if (!file.is_open())
    {
        cout << "I can't open file T-T" << endl;
        return false;
    }

    string line;
    int line_iterator = 0;
    while (getline(file, line))
    {
        bool result_of_line_parsing = line_parser(line, circuit);
        if (!result_of_line_parsing)
        {
            cout << "Error in line " << line_iterator << endl;
        }
        line_iterator++;
    }

    file.close();
    return true;
}