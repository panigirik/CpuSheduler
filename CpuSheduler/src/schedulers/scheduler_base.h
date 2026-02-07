#pragma once

#include <vector>
#include <string>

#include "../core/process.h"
#include "../core/scheduler_result.h"

class SchedulerBase
{
public:
    explicit SchedulerBase(std::string name);
    virtual ~SchedulerBase() = default;

    virtual void run(const std::vector<Process>& processes) = 0;

    SchedulerResult get_result() const;

protected:
    void reset();

protected:
    std::string name_;
    SchedulerResult result_;
};
