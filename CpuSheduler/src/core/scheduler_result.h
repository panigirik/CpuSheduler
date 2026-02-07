#pragma once

#include <string>
#include <vector>

struct GanttEntry
{
    int start_time{};
    int end_time{};
    int process_id{};
};

struct SchedulerResult
{
    std::string algorithm_name;

    double avg_waiting_time{};
    double avg_turnaround_time{};
    int context_switches{};

    std::vector<GanttEntry> gantt_chart;
};
