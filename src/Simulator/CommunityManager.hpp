#ifndef __COMMUNITY_MANAGER__
#define __COMMUNITY_MANAGER__

#include <unordered_map>
#include <vector>
#include <cassert>
#include <memory>
#include <cstdlib>
#include "Agent/Agent.hpp"
#include "Community.hpp"
#include "common/Event.hpp"
#include "Log/Log.hpp"
#include "EventManager/EventManager.hpp"

class CommunityManager {
    private:
        std::unordered_map<uint64_t, std::unique_ptr<Community>> m_community;

        uint64_t m_startTime;

        uint64_t m_endTime;

        uint64_t m_unitTime;

        // Private member function
        bool communityExist(uint64_t t_tag);

    public:
        CommunityManager() = default;

        ~CommunityManager() = default;

        void addAgent(Agent const * t_agent);

        void simulate(uint64_t t_startTime, uint64_t t_endTime, uint64_t t_unitTime);
};


#endif
