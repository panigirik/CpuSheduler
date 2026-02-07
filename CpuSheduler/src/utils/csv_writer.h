#pragma once

#include <filesystem>
#include <vector>

#include "../core/scheduler_result.h"

class CSVWriter
{
public:
    static void write(
        const std::filesystem::path& path,
        const std::vector<SchedulerResult>& results
    );
};
