#pragma once

#include <filesystem>

struct SimulationConfig
{
    std::filesystem::path input_file;
    std::filesystem::path output_dir{"results"};

    int quantum{2};

    bool print_gantt{false};
    bool generate_plots{false};
};
