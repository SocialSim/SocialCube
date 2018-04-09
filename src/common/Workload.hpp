#ifndef __WORKLOAD__
#define __WORKLOAD__

#include <vector>
#include <memory>

#include "Simulator/Community.hpp"

class Workload {
    private:
        std::vector<std::unique_ptr<Community>> m_community;

        time_t m_startTime;

        time_t m_endTime;

        time_t m_unitTime;

    public:
        Workload();

        Workload(time_t t_startTime, time_t t_endTime, time_t t_unitTime);

        ~Workload() = default;

        Workload& operator=(const Workload&) = delete;

        Workload(const Workload&) = delete;

        Workload (Workload&&) = default;

        Workload& operator=(Workload&&) = default;

        void addCommunity(std::unique_ptr<Community>&& t_community);

        std::vector<std::unique_ptr<Community>> transferWorkload();

        time_t getStartTime();

        time_t getEndTime();

        time_t getUnitTime();
        
};

#endif
