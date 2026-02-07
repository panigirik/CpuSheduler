#include "sjf_scheduler.h"

#include <algorithm>
#include <queue>

SJFScheduler::SJFScheduler()
    : SchedulerBase("SJF")
{
}

void SJFScheduler::run(const std::vector<Process>& processes)
{
    reset();

    std::vector<Process> procs = processes;

    std::sort(procs.begin(), procs.end(),
              [](const Process& a, const Process& b)
              {
                  return a.arrival_time < b.arrival_time;
              });

    auto cmp = [](const Process* a, const Process* b)
    {
        return a->burst_time > b->burst_time;
    };

    std::priority_queue<Process*, std::vector<Process*>, decltype(cmp)> pq(cmp);

    int time = 0;
    int index = 0;
    int completed = 0;
    const int n = static_cast<int>(procs.size());

    double total_wait = 0;
    double total_turnaround = 0;

    while (completed < n)
    {
        while (index < n && procs[index].arrival_time <= time)
        {
            pq.push(&procs[index]);
            index++;
        }

        if (pq.empty())
        {
            time = procs[index].arrival_time;
            continue;
        }

        Process* p = pq.top();
        pq.pop();

        int start_time = time;
        int finish_time = start_time + p->burst_time;

        int waiting_time = start_time - p->arrival_time;
        int turnaround_time = finish_time - p->arrival_time;

        total_wait += waiting_time;
        total_turnaround += turnaround_time;

        result_.gantt_chart.push_back(
            { start_time, finish_time, p->id }
        );

        time = finish_time;
        completed++;
    }

    const double count = static_cast<double>(n);

    result_.avg_waiting_time = total_wait / count;
    result_.avg_turnaround_time = total_turnaround / count;
    result_.context_switches = 0;
}
