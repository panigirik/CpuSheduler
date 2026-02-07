#include "csv_writer.h"

#include <fstream>
#include <stdexcept>

void CSVWriter::write(
    const std::filesystem::path& path,
    const std::vector<SchedulerResult>& results
)
{
    std::ofstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open CSV output file: " + path.string());
    }

    file << "Algorithm,AvgWaitingTime,AvgTurnaroundTime,ContextSwitches\n";

    for (const auto& r : results)
    {
        file
            << r.algorithm_name << ","
            << r.avg_waiting_time << ","
            << r.avg_turnaround_time << ","
            << r.context_switches << "\n";
    }
}
