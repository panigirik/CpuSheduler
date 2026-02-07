#pragma once

#include <filesystem>
#include <vector>

#include "../core/process.h"

class Parser
{
public:
    static std::vector<Process> parse_file(const std::filesystem::path& path);
};
