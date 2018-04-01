#ifndef __SIMULATOR_PROFILE_HPP__
#define __SIMULATOR_PROFILE_HPP__

#include <chrono>
#include <cstdlib>
#include "Log/Log.hpp"

class SimulatorProfiler {
    private:
        
        // Private member variable
        std::chrono::time_point<std::chrono::steady_clock> m_chronoStart;

        std::chrono::time_point<std::chrono::steady_clock> m_chronoEnd;

        std::chrono::duration<double> m_duration;

        uint64_t m_eventCount {0};

    public:
        SimulatorProfiler() = default;

        ~SimulatorProfiler() = default;

        void timeStart();

        void timeEnd();

        void showProfile();

        void setEventCount(uint64_t t_cnt);
};

#endif
