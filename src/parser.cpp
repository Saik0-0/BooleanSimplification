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

bool str_to_gate_inputs(const std::string& str, std::vector<std:: string>& inputs)
{
    if (str.empty())
    {
        return false;
    }

    std::string input_name = "";
    for (char c : str)
    {
        // std::cout << "Now i reading char " << c << std::endl;
        if (c != ',')
        {
            input_name.push_back(c);
        }
        else
        {
            inputs.push_back(input_name);
            input_name = "";
        }
    }
    if (input_name != "")
    {
        inputs.push_back(input_name);
    }

    return true;
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
        size_t start_of_input_name = line.find("(");
        size_t end_of_input_name = line.find(")");
        if ((start_of_input_name + 1) != string::npos && end_of_input_name != string::npos)
        {
            string input_name = line.substr(start_of_input_name + 1, end_of_input_name - (start_of_input_name + 1));
            cout << "I read input name: " << input_name << endl;

            circuit.inputs.push_back(input_name);
        }
        return true;
    }

    if (line.find("OUTPUT") == 0)
    {
        size_t start_of_output_name = line.find("(");
        size_t end_of_output_name = line.find(")");
        if ((start_of_output_name + 1) != string::npos && end_of_output_name != string::npos)
        {
            string output_name = line.substr(start_of_output_name + 1, end_of_output_name - (start_of_output_name + 1));
            cout << "I read output name: " << output_name << endl;

            circuit.outputs.push_back(output_name);
        }
        return true;
    }

    size_t equation_position = line.find("=");
    if (equation_position != string::npos)
    {
        string gate_name = line.substr(0, equation_position - 1);

        size_t start_of_gate_inputs = line.find("(");
        size_t end_of_gate_inputs = line.find(")");
        if (start_of_gate_inputs != string::npos && end_of_gate_inputs != string::npos)
        {
            string gate_type = line.substr(equation_position + 1, start_of_gate_inputs - (equation_position + 1));
            cout << "I read gate name: " << gate_name << ", and gate type: " << gate_type << ". ";
            string str_of_gate_inputs = line.substr(start_of_gate_inputs + 1, end_of_gate_inputs - (start_of_gate_inputs + 1));
            
            vector<string> input_gates;
            bool str_to_gate_inputs_checker = str_to_gate_inputs(str_of_gate_inputs, input_gates);

            Gate gate;
            gate.name = gate_name;
            gate.g_type = str_to_gate(gate_type);
            gate.inputs = input_gates;

            circuit.gates.push_back(gate_name);

            cout << "Its inputs are: ";
            for (int i = 0; i < input_gates.size(); ++i)
            {
                cout << input_gates[i] << " ";
            }

            cout << endl;
            
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