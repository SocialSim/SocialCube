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

        uint64_t m_eventCount;

        bool m_profileOn;

        // Private member function

        void showProfile();

        SimulatorProfiler();

    public:
        static SimulatorProfiler& getInstance();

        ~SimulatorProfiler();

        void timeStart();

        void timeEnd();

        void setEventCount(uint64_t t_cnt);

        void setProfileShow(bool t_profileOn);
};

#endif
