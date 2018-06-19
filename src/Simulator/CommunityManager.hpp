#ifndef __COMMUNITY_MANAGER__
#define __COMMUNITY_MANAGER__

#include <unordered_map>
#include <vector>
#include <cassert>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Agent/Agent.hpp"
#include "Community.hpp"
#include "common/Event.hpp"
#include "Log/Log.hpp"
#include "EventManager/EventManager.hpp"

class CommunityManager {
    private:
        std::unordered_map<uint64_t, std::unique_ptr<Community>> m_community;

        time_t m_startTime;

        time_t m_endTime;

        time_t m_unitTime;

        // Private member function
        bool communityExist(uint64_t t_tag);

    public:
        CommunityManager() = default;

        ~CommunityManager() = default;

        void addAgent(Agent const * t_agent);

        void simulate(std::vector<std::string> cc_list, std::vector<std::vector<float>> temp_pref_data, time_t t_startTime, time_t t_endTime, time_t t_unitTime);

        void eventBasedSimulate(std::vector<std::string> cc_list, std::vector<std::vector<float>> temp_pref_data, time_t t_startTime, time_t t_endTime);

        int currentDow(time_t now);
};


#endif
