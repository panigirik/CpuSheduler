#include "parser.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Process> Parser::parse_file(const std::filesystem::path& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open input file: " + path.string());
    }

    std::vector<Process> processes;
    std::string line;
    int id = 1;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::istringstream iss(line);

        int arrival = 0;
        int burst = 0;
        int priority = 0;

        if (!(iss >> arrival >> burst >> priority))
        {
            throw std::runtime_error("Invalid input format in line: " + line);
        }

        if (arrival < 0 || burst <= 0 || priority < 1 || priority > 5)
        {
            throw std::runtime_error("Invalid values in line: " + line);
        }

        processes.emplace_back(id++, arrival, burst, priority);
    }

    if (processes.empty())
    {
        throw std::runtime_error("Input file contains no valid processes");
    }

    return processes;
}
