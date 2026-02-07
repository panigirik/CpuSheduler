#pragma once

#include <memory>
#include <vector>

#include "process.h"
#include "scheduler_result.h"
#include "simulation_config.h"

class SchedulerBase;

class Simulator
{
public:
    explicit Simulator(SimulationConfig config);

    void set_processes(const std::vector<Process>& processes);

    void add_scheduler(std::unique_ptr<SchedulerBase> scheduler);

    void run();

    const std::vector<SchedulerResult>& results() const;

private:
    void print_console_report() const;

private:
    SimulationConfig config_;
    std::vector<Process> processes_;
    std::vector<std::unique_ptr<SchedulerBase>> schedulers_;
    std::vector<SchedulerResult> results_;
};
