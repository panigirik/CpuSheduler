#pragma once

#include "scheduler_base.h"

class SJFScheduler final : public SchedulerBase
{
public:
    SJFScheduler();

    void run(const std::vector<Process>& processes) override;
};
