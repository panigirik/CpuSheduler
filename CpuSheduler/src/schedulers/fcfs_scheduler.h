#pragma once

#include "scheduler_base.h"

class FCFSScheduler final : public SchedulerBase
{
public:
    FCFSScheduler();

    void run(const std::vector<Process>& processes) override;
};
