#ifndef __COMMUNITY__
#define __COMMUNITY__

#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <math.h>  
#include <dirent.h>
#include <cstdlib>
#include <algorithm>
#include "Agent/Agent.hpp"
#include "common/Event.hpp"

class Community {
    private:

        std::vector<Agent const *> m_community;

        uint64_t m_communityTag;

    public:
        Community(uint64_t t_communityTag);

        ~Community() = default;

        size_t size();

        uint64_t getCommunityTag();

        void add(Agent const * t_agent);

        std::vector<std::unique_ptr<Event>> step(std::vector<std::string> cc_list, std::vector<float> temp_pref_data, time_t t_currentTime, time_t t_unitTime);

        std::vector<std::unique_ptr<Event>> simulate(time_t t_startTime, time_t t_endTime);
};

#endif
