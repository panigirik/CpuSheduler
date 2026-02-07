#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "core/simulator.h"
#include "utils/parser.h"
#include "utils/gantt_generator.h"
#include "utils/csv_writer.h"
#include "schedulers/fcfs_scheduler.h"
#include "schedulers/rr_scheduler.h"
#include "schedulers/sjf_scheduler.h"

static void print_usage()
{
    std::cout <<
        "Usage:\n"
        "  cpu_scheduler -i <input_file> [-q quantum] [-o output_dir] [-g] [-p]\n\n"
        "Options:\n"
        "  -i <file>    Input file with processes (required)\n"
        "  -q <value>   Quantum for Round Robin (default: 2)\n"
        "  -o <dir>     Output directory (default: ./results)\n"
        "  -g           Print Gantt charts\n"
        "  -p           Generate plots using Python script\n";
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        print_usage();
        return 1;
    }

    SimulationConfig config;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-i" && i + 1 < argc)
        {
            config.input_file = argv[++i];
        }
        else if (arg == "-q" && i + 1 < argc)
        {
            config.quantum = std::stoi(argv[++i]);
        }
        else if (arg == "-o" && i + 1 < argc)
        {
            config.output_dir = argv[++i];
        }
        else if (arg == "-g")
        {
            config.print_gantt = true;
        }
        else if (arg == "-p")
        {
            config.generate_plots = true;
        }
        else
        {
            print_usage();
            return 1;
        }
    }

    if (config.input_file.empty())
    {
        std::cerr << "Error: input file is required (-i)\n";
        return 1;
    }

    try
    {
        std::filesystem::create_directories(config.output_dir);

        auto processes = Parser::parse_file(config.input_file);

        Simulator simulator(config);

        simulator.set_processes(processes);

        simulator.add_scheduler(std::make_unique<FCFSScheduler>());
        simulator.add_scheduler(std::make_unique<RRScheduler>(config.quantum));
        simulator.add_scheduler(std::make_unique<SJFScheduler>());

        simulator.run();

        const auto& results = simulator.results();

        const auto csv_path = config.output_dir / "results.csv";
        CSVWriter::write(csv_path, results);

        std::cout << "CSV exported to: " << csv_path << "\n";

        if (config.print_gantt)
        {
            for (const auto& r : results)
            {
                std::cout << "\n=== " << r.algorithm_name << " ===\n";
                std::cout << GanttGenerator::generate_text(r.gantt_chart);
            }
        }

        if (config.generate_plots)
        {
            const std::string command =
                "python scripts/plot_results.py \"" +
                csv_path.string() + "\" \"" +
                config.output_dir.string() + "\"";

            std::cout << "Running: " << command << "\n";
            std::system(command.c_str());
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
