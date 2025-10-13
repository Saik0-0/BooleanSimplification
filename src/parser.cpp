#include "parser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>


GateType str_to_gate(const std::string_view str)
{
    if (str == "INPUT")
        return GateType::INPUT;
    if (str == "OUTPUT") 
        return GateType::OUTPUT;
    if (str == "AND") 
        return GateType::AND;
    if (str == "OR") 
        return GateType::OR;
    if (str == "NOT") 
        return GateType::NOT;
    if (str == "XOR") 
        return GateType::XOR;
    throw std::invalid_argument("Unknown gate type: " + std::string(str));
}

void remove_spaces(const std::string_view str, std::string* str_without_spaces)
{
    str_without_spaces->clear();
    str_without_spaces->reserve(str.size());

    for (char c : str)
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            *str_without_spaces += c;
        }
    }
}

bool str_to_gate_operands(const std::string_view str, std::vector<std:: string_view>* inputs)
{
    if (str.empty())
    {
        return false;
    }

    std::string_view operand_name = "";
    int substr_index_start = 0;
    int substr_index_end = 0;
    for (char c : str)
    {
        if (c != ',')
        {
            ++substr_index_end;
        }
        else
        {
            operand_name = str.substr(substr_index_start, substr_index_start + substr_index_end);
            inputs->push_back(operand_name);
            operand_name = "";
            substr_index_start = ++substr_index_end;
        }
    }
    operand_name = str.substr(substr_index_start, substr_index_start + substr_index_end);
    if (operand_name != "")
    {
        inputs->push_back(operand_name);
    }

    return true;
}

bool line_parser(std::string_view line, Circuit* circuit)
{
    if (line.empty())
    {
        return true;
    }

    std::string line_without_spaces = "";
    remove_spaces(line, &line_without_spaces);
    line = line_without_spaces;

    if (line.find("INPUT") == 0)
    {
        size_t start_of_input_name = line.find("(");
        size_t end_of_input_name = line.find(")");
        if ((start_of_input_name + 1) != std::string::npos && end_of_input_name != std::string::npos)
        {
            std::string_view input_name = line.substr(start_of_input_name + 1, end_of_input_name - (start_of_input_name + 1));
            std::cout << "I read input name: " << input_name << std::endl;

            circuit->inputs.push_back(input_name);
        }
        else
        {
            std::cerr << "Error in Input" << std::endl;
        }
        return true;
    }

    if (line.find("OUTPUT") == 0)
    {
        size_t start_of_output_name = line.find("(");
        size_t end_of_output_name = line.find(")");
        if ((start_of_output_name + 1) != std::string::npos && end_of_output_name != std::string::npos)
        {
            std::string_view output_name = line.substr(start_of_output_name + 1, end_of_output_name - (start_of_output_name + 1));
            std::cout << "I read output name: " << output_name << std::endl;

            circuit->outputs.push_back(output_name);
        }
        else
        {
            std::cerr << "Error in Output" << std::endl;
        }
        return true;
    }

    size_t equation_position = line.find("=");
    if (equation_position != std::string::npos)
    {
        std::string_view gate_name = line.substr(0, equation_position);

        size_t start_of_gate_operands = line.find("(");
        size_t end_of_gate_operands = line.find(")");
        if (start_of_gate_operands != std::string::npos && end_of_gate_operands != std::string::npos)
        {
            std::string_view gate_type = line.substr(equation_position + 1, start_of_gate_operands - (equation_position + 1));
            std::cout << "I read gate name: " << gate_name << ", and gate type: " << gate_type << ". ";
            std::string_view str_of_gate_operands = line.substr(start_of_gate_operands + 1, end_of_gate_operands - (start_of_gate_operands + 1));
            
            std::vector<std::string_view> operands_gates;
            bool str_to_gate_operands_checker = str_to_gate_operands(str_of_gate_operands, &operands_gates);
            if (!str_to_gate_operands_checker)
            {
                std::cerr << "Can't read operands" << std::endl;
            }

            Gate gate(gate_name, str_to_gate(gate_type), operands_gates);

            circuit->gates.push_back(gate_name);

            std::cout << "Its operands are: ";
            for (int i = 0; i < operands_gates.size(); ++i)
            {
                std::cout << operands_gates[i] << " ";
            }

            std::cout << std::endl;

            return true;
        }
        else
        {
            std::cerr << "Error in operands" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error in gate description" << std::endl;
    }

    return false;
}

Circuit parse_bench_file(const std::string_view filename)
{
    Circuit circuit;
    std::fstream file(std::string{filename});
    if (!file.is_open())
    {
        std::cerr << "I can't open file T-T" <<std:: endl;
        return circuit;
    }

    std::string line;
    int line_iterator = 0;
    while (getline(file, line))
    {
        bool result_of_line_parsing = line_parser(line, &circuit);
        if (!result_of_line_parsing)
        {
            std::cerr << "Error in line " << line_iterator << std::endl;
            return circuit;
        }
        ++line_iterator;
    }

    file.close();
    return circuit;
}