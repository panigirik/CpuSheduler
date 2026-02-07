#include "gantt_generator.h"

#include <sstream>

std::string GanttGenerator::generate_text(const std::vector<GanttEntry>& entries)
{
    if (entries.empty())
    {
        return "Empty Gantt chart\n";
    }

    std::ostringstream out;

    out << "\nGantt Chart:\n";

    for (const auto& e : entries)
    {
        out << e.start_time
            << " [P" << e.process_id << "] "
            << e.end_time << " | ";
    }

    out << "\n";

    return out.str();
}
