#include "simulator.h"

#include <iostream>
#include <iomanip>

#include "../schedulers/scheduler_base.h"

Simulator::Simulator(SimulationConfig config)
    : config_(std::move(config))
{
}

void Simulator::set_processes(const std::vector<Process>& processes)
{
    processes_ = processes;
}

void Simulator::add_scheduler(std::unique_ptr<SchedulerBase> scheduler)
{
    schedulers_.push_back(std::move(scheduler));
}

void Simulator::run()
{
    results_.clear();

    for (auto& scheduler : schedulers_)
    {
        scheduler->run(processes_);
        results_.push_back(scheduler->get_result());
    }

    print_console_report();
}

const std::vector<SchedulerResult>& Simulator::results() const
{
    return results_;
}

void Simulator::print_console_report() const
{
    std::cout << "\n=== CPU Scheduling Simulation Results ===\n\n";

    std::cout
        << std::left << std::setw(12) << "Algorithm"
        << std::setw(20) << "Avg Waiting Time"
        << std::setw(24) << "Avg Turnaround Time"
        << std::setw(18) << "Context Switches"
        << "\n";

    std::cout << std::string(74, '-') << "\n";

    for (const auto& r : results_)
    {
        std::cout
            << std::left << std::setw(12) << r.algorithm_name
            << std::setw(20) << std::fixed << std::setprecision(2) << r.avg_waiting_time
            << std::setw(24) << std::fixed << std::setprecision(2) << r.avg_turnaround_time
            << std::setw(18) << r.context_switches
            << "\n";
    }

    std::cout << "\n";
}
