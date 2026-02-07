#pragma once

#include <vector>
#include <string>

#include "../core/scheduler_result.h"

class GanttGenerator
{
public:
    static std::string generate_text(const std::vector<GanttEntry>& entries);
};
