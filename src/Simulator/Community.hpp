#ifndef __COMMUNITY__
#define __COMMUNITY__

#include <vector>
#include <memory>
#include <cstdlib>
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

        std::vector<std::unique_ptr<Event>> step(time_t t_currentTime, time_t t_unitTime);

};

#endif
