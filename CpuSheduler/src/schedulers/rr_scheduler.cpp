#include "rr_scheduler.h"

#include <queue>
#include <algorithm>

RRScheduler::RRScheduler(int quantum)
    : SchedulerBase("RR"),
      quantum_(quantum)
{
}

void RRScheduler::run(const std::vector<Process>& processes)
{
    reset();

    std::vector<Process> procs = processes;

    std::sort(procs.begin(), procs.end(),
              [](const Process& a, const Process& b)
              {
                  return a.arrival_time < b.arrival_time;
              });

    std::queue<int> ready_queue;

    const int n = static_cast<int>(procs.size());

    std::vector<int> finish_times(n, 0);
    std::vector<bool> finished(n, false);

    int time = 0;
    int index = 0;
    int completed = 0;
    int last_process = -1;

    while (completed < n)
    {
        while (index < n && procs[index].arrival_time <= time)
        {
            ready_queue.push(index);
            index++;
        }

        if (ready_queue.empty())
        {
            time = procs[index].arrival_time;
            continue;
        }

        int i = ready_queue.front();
        ready_queue.pop();

        if (last_process != -1 && last_process != i)
        {
            result_.context_switches++;
        }

        last_process = i;

        int slice = std::min(quantum_, procs[i].remaining_time);

        result_.gantt_chart.push_back(
            { time, time + slice, procs[i].id }
        );

        time += slice;
        procs[i].remaining_time -= slice;

        while (index < n && procs[index].arrival_time <= time)
        {
            ready_queue.push(index);
            index++;
        }

        if (procs[i].remaining_time > 0)
        {
            ready_queue.push(i);
        }
        else
        {
            finished[i] = true;
            finish_times[i] = time;
            completed++;
        }
    }

    double total_wait = 0;
    double total_turnaround = 0;

    for (int i = 0; i < n; ++i)
    {
        int turnaround = finish_times[i] - procs[i].arrival_time;
        int waiting = turnaround - procs[i].burst_time;

        total_wait += waiting;
        total_turnaround += turnaround;
    }

    const double count = static_cast<double>(n);

    result_.avg_waiting_time = total_wait / count;
    result_.avg_turnaround_time = total_turnaround / count;
}
