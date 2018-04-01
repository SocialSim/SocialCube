#ifndef __SIMULATOR_PROFILE_HPP__
#define __SIMULATOR_PROFILE_HPP__

#include <chrono>
#include "Log/Log.hpp"

class SimulatorProfiler {
    private:
        
        // Private member variable
        std::chrono::time_point<std::chrono::steady_clock> m_chronoStart;

        std::chrono::time_point<std::chrono::steady_clock> m_chronoEnd;

        std::chrono::duration<double> m_duration;

    public:
        SimulatorProfiler() = default;

        ~SimulatorProfiler() = default;

        void timeStart();

        void timeEnd();

        void showProfile();
};

#endif
