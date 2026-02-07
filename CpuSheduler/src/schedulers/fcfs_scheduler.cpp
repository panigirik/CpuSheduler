#include "fcfs_scheduler.h"

#include <algorithm>

FCFSScheduler::FCFSScheduler()
    : SchedulerBase("FCFS")
{
}

void FCFSScheduler::run(const std::vector<Process>& processes)
{
    reset();

    std::vector<Process> procs = processes;

    std::sort(procs.begin(), procs.end(),
              [](const Process& a, const Process& b)
              {
                  return a.arrival_time < b.arrival_time;
              });

    int current_time = 0;
    double total_wait = 0;
    double total_turnaround = 0;

    for (auto& p : procs)
    {
        if (current_time < p.arrival_time)
        {
            current_time = p.arrival_time;
        }

        int start_time = current_time;
        int finish_time = start_time + p.burst_time;

        int waiting_time = start_time - p.arrival_time;
        int turnaround_time = finish_time - p.arrival_time;

        total_wait += waiting_time;
        total_turnaround += turnaround_time;

        result_.gantt_chart.push_back(
            { start_time, finish_time, p.id }
        );

        current_time = finish_time;
    }

    const double count = static_cast<double>(procs.size());

    result_.avg_waiting_time = total_wait / count;
    result_.avg_turnaround_time = total_turnaround / count;
    result_.context_switches = 0;
}
