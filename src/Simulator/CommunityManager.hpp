#ifndef __COMMUNITY_MANAGER__
#define __COMMUNITY_MANAGER__

#include <unordered_map>
#include <vector>
#include <cassert>
#include <chrono>
#include <memory>
#include <cstdlib>
#include "Agent/Agent.hpp"
#include "Community.hpp"
#include "common/Event.hpp"
#include "Log/Log.hpp"
#include "EventManager/EventManager.hpp"
#include "Scheduler/SimpleScheduler/SimpleScheduler.hpp"
#include "common/Workload.hpp"
#include "SimulatorWorkerManager/SimulatorWorkerManager.hpp"

class CommunityManager {
    private:
        std::unordered_map<uint64_t, std::unique_ptr<Community>> m_community;

        time_t m_startTime;

        time_t m_endTime;

        time_t m_unitTime;

        std::unordered_map<uint64_t, size_t> m_communityPendingSimulation;

        // Private member function
        bool communityExist(uint64_t t_tag);

        std::vector<uint64_t> schedule();

        void waitSimulatorWorkerManager();

    public:
        CommunityManager() = default;

        ~CommunityManager() = default;

        void addAgent(Agent const * t_agent);

        void simulate(time_t t_startTime, time_t t_endTime, time_t t_unitTime);
};


#endif
