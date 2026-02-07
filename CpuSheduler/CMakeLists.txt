cmake_minimum_required(VERSION 4.1)
project(CpuSheduler)

set(CMAKE_CXX_STANDARD 20)

add_executable(CpuSheduler src/main.cpp
        src/core/process.h
        src/core/process.cpp
        src/core/scheduler_result.h
        src/core/scheduler_result.cpp
        src/core/simulator.cpp
        src/core/simulator.h
        src/schedulers/scheduler_base.cpp
        src/schedulers/scheduler_base.h
        src/schedulers/fcfs_scheduler.cpp
        src/schedulers/fcfs_scheduler.h
        src/schedulers/rr_scheduler.h
        src/schedulers/rr_scheduler.cpp
        src/utils/parser.h
        src/utils/parser.cpp
        src/utils/gantt_generator.cpp
        src/utils/gantt_generator.h
        src/utils/csv_writer.cpp
        src/utils/csv_writer.h
)
