#include "scheduler_base.h"

SchedulerBase::SchedulerBase(std::string name)
    : name_(std::move(name))
{
    result_.algorithm_name = name_;
}

void SchedulerBase::reset()
{
    result_ = {};
    result_.algorithm_name = name_;
}

SchedulerResult SchedulerBase::get_result() const
{
    return result_;
}
