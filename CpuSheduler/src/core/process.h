#pragma once

#include <cstdint>

struct Process
{
    int id{};
    int arrival_time{};
    int burst_time{};
    int priority{};
    int remaining_time{};

    Process() = default;

    Process(int id_, int arrival_, int burst_, int priority_)
        : id(id_),
          arrival_time(arrival_),
          burst_time(burst_),
          priority(priority_),
          remaining_time(burst_)
    {
    }

    void reset()
    {
        remaining_time = burst_time;
    }
};
